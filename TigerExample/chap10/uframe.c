#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "assem.h"
#include "frame.h"

const int F_WORD_SIZE = 4; /* 4 byte */
static const int F_MAX_REG = 6;  /* paras in regs number */ 
Temp_map F_tempMap = NULL;

struct F_frame_ {
	Temp_label name;
	F_accessList formals;
	int local_count;/*local-var numb*/
	/*??? "view shift"*/
};

struct F_access_ {
	enum {inFrame, inReg} kind;
	union {
		int offs;
		Temp_temp reg;
	} u;
};/* describe area-var and reg */

static F_access InFrame(int offs);
static F_access InReg(Temp_temp reg);
static F_accessList makeFormalAccessList(F_frame, U_boolList);
static F_accessList F_AccessList(F_access, F_accessList);

F_frame F_newFrame(Temp_label name, U_boolList formals) {
	F_frame f = checked_malloc(sizeof(*f));
	f->name = name;
	f->formals = makeFormalAccessList(f, formals);
	f->local_count = 0;
	return f;
}

F_access F_allocLocal(F_frame f, bool escape) {
	/* give a not-paras-var alloc space just is in let-in-end-exp decl a var */
	f->local_count++;
	if (escape) {
		return InFrame(-1 * F_WORD_SIZE * f->local_count);
	}
	return InReg(Temp_newtemp());
}

F_accessList F_formals(F_frame f) { return f->formals; }

Temp_label F_name(F_frame f) { return f->name; }

bool F_isEscape(F_access a) { return (a && a->kind == inFrame); }

static F_accessList makeFormalAccessList(F_frame f, U_boolList formals) {
	U_boolList fmls = formals;
	F_accessList head = NULL, tail = NULL;
	int i = 0;
	for (; fmls; fmls = fmls->tail, i++) {
		F_access ac = NULL;
		if (i < F_MAX_REG && !fmls->head) {
			ac = InReg(Temp_newtemp());
		} else {
			ac = InFrame((i) * F_WORD_SIZE);
		}
		if (head) {
			tail->tail = F_AccessList(ac, NULL);
			tail = tail->tail;
		} else {
			head = F_AccessList(ac, NULL);
			tail = head;
		}
	}
	return head;
}

static F_accessList F_AccessList(F_access head, F_accessList tail) {
	F_accessList l = checked_malloc(sizeof(*l));
	l->head = head;
	l->tail = tail;
	return l;
}

static F_access InFrame(int offs) {
	F_access a = checked_malloc(sizeof(*a));
	a->kind = inFrame;
	a->u.offs = offs;
	return a;
}

static F_access InReg(Temp_temp t) {
	F_access a = checked_malloc(sizeof(*a));
	a->kind = inReg;
	a->u.reg = t;
	return a;
}

/*******IR*******/
F_frag F_StringFrag(Temp_label label, string str) {
	F_frag strfrag = checked_malloc(sizeof(*strfrag));
	strfrag->kind = F_stringFrag;
	strfrag->u.stringg.label = label;
	strfrag->u.stringg.str = str;
	return strfrag;
}

F_frag F_ProcFrag(T_stm body, F_frame frame) {
	F_frag pfrag = checked_malloc(sizeof(*pfrag));
	pfrag->kind = F_procFrag;
	pfrag->u.proc.body = body;
	pfrag->u.proc.frame = frame;
	return pfrag;
}

F_fragList F_FragList(F_frag head, F_fragList tail) {
	F_fragList fl = checked_malloc(sizeof(*fl));
	fl->head = head;
	fl->tail = tail;
	return fl;
}

#define INIT_REG(Reg, Name) (Reg ? Reg : (Reg = Temp_newtemp(), Temp_enter(F_TEMPMAP, Reg, Name), Reg))

/* kinds special register */
static Temp_temp fp = NULL;
Temp_temp F_FP() { return INIT_REG(fp, "ebp"); } 

static Temp_temp sp = NULL;
Temp_temp F_SP() { return INIT_REG(fp, "esp"); }

static Temp_temp rv = NULL; 
Temp_temp F_RV() { return INIT_REG(rv, "eax"); }

static Temp_temp ra = NULL; /* may addr in memory may no use */
Temp_temp F_RA() { return INIT_REG(ra, "---"); }

static Temp_tempList callersaves() 
{
	/* assist-function of calldefs() 
	 * kinds of usual register
	 */
	
	Temp_temp ebx = Temp_newtemp(),
			  ecx = Temp_newtemp(),
			  edx = Temp_newtemp(),
			  edi = Temp_newtemp(),
			  esi = Temp_newtemp();
	Temp_enter(F_TEMPMAP, ebx, "ebx");
	Temp_enter(F_TEMPMAP, ecx, "ecx");
	Temp_enter(F_TEMPMAP, edx, "edx");
	Temp_enter(F_TEMPMAP, edi, "edi");
	Temp_enter(F_TEMPMAP, esi, "esi");
	return TL(F_RV(), TL(ebx, TL(ecx, TL(edx, TL(edi, TL(esi, NULL))))));
}

static Temp_tempList sepecialregs()
{
    static Temp_tempList spcregs = NULL;
    if (!spcregs) spcregs = TL(F_SP(), TL(F_FP(), TL(F_RV(), NULL)));
    return spcregs;
}

/* no regs pass arg, because pass arg only by stack */

static Temp_tempList calleesaves() 
{   
    /* callee protect sp, fp */
    static Temp_tempList calleeregs = NULL;
    if (!calleeregs) {
        calleeregs = TL(F_SP(), TL(F_FP(), NULL));
    }
    return calleeregs;
}


Temp_tempList F_calldefs() 
{
	/* some registers that may raise side-effect (caller procted, return-val-reg, return-addr-reg) */
	static Temp_tempList protected_regs = NULL;
	return protected_regs ? protected_regs : (protected_regs = TL(F_RV(), callersaves()));
}

T_exp F_Exp(F_access access, T_exp framePtr){ /* visit frame-offs addr & get content */
	if (access->kind == inFrame) {
		return T_Mem(T_Binop(T_plus, framePtr, T_Const(access->u.offs)));
	} else {
		return T_Temp(access->u.reg);
	}
}

T_exp F_externalCall(string str, T_expList args) {
	return T_Call(T_Name(Temp_namedlabel(str)), args);
}

T_stm F_procEntryExit1(F_frame frame, T_stm stm) {
	return stm;
}

static Temp_tempList returnSink = NULL;
AS_instrList  F_procEntryExit2(AS_instrList body)
{
	/* tell reg-alloc-engine which regs are lives in proc-Exit
	 */
	if (!returnSink) returnSink = calleesaves();
	return AS_splice(body, AS_InstrList(AS_Oper("", NULL, returnSink, NULL), NULL));
}

AS_proc F_procEntryExit3(F_frame frame, AS_instrList body)
{
	char buf[100];
	sprintf(buf, "PROC %s\n", Temp_labelstring(frame->name));
	return AS_Proc(String(buf), body, "END\n");
}

/*******DEBUG_INFO********/
void display_f(F_frame f) {
	printf("label: %s\n", Temp_labelstring(f->name));	
	printf("local: %d\n", f->local_count);
	F_accessList l = f->formals->tail;
	for (; l; l = l->tail) {
		dis_ac(l->head);	
	}
}

void dis_ac(F_access a) {
	switch (a->kind) {
		case inFrame:
			printf("stack: %i\n", a->u.offs);
			break;
		case inReg:
			break;
			printf("reg  : %d\n", Temp_tempint(a->u.reg));
		default:
			assert(0);
		}
}
