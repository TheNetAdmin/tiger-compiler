#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "assem.h"
#include "printtree.h"

extern Temp_map F_tempMap;
static F_frame  Co_frame = NULL; /* current function frame */

static void emit(AS_instr);
static Temp_temp munchExp(T_exp);
static void munchStm(T_stm);
static Temp_tempList munchArgs(int, T_expList);

#define MATCH_OP(I, Op, Sign) \
	switch (I) { \
		case T_plus: Op = "add"; Sign = "+"; break; \
		case T_minus: Op = "sub"; Sign = "-"; break; \
		case T_mul: Op = "mul"; Sign = "*"; break; \
		case T_div: Op = "div"; Sign = "/"; break; \
		default : assert( 0 && "invalid Oper"); \
	} "for short ';'" 

#define WRITE_ASM_STR(Str, Arg) \
	sprintf(assem_string, Str, Arg); \
p2asm_str = String(assem_string)

#define WRITE_ASM_STR2(Str, A1, A2) \
	sprintf(assem_string, Str, A1, A2); \
p2asm_str = String(assem_string)

#define WRITE_ASM_STR3(Str, A1, A2, A3) \
	sprintf(assem_string, Str, A1, A2, A3); \
p2asm_str = String(assem_string)

static Temp_temp munchExp(T_exp e)
{
	char assem_string[100];
	string p2asm_str;
	Temp_temp r = Temp_newtemp(); /* return value */

    switch (e->kind) {
        case T_BINOP: 
        {
            char * op = NULL, * sign = NULL;
            T_exp left = e->u.BINOP.left, right = e->u.BINOP.right;
            MATCH_OP(e->u.BINOP.op, op, sign);
			
			if (left->kind == T_CONST) { /* BINOP(op, CONST, e) */
				WRITE_ASM_STR2("%s $%x, `d0", op, left->u.CONST);	
                emit(AS_Oper(p2asm_str, TL(r = munchExp(right), NULL), NULL, NULL));
            } else if (e->u.BINOP.right->kind == T_CONST) { /* BINOP(op, e, CONST) */
                WRITE_ASM_STR2("%s $%x, `d0", op, right->u.CONST);	
                emit(AS_Oper(p2asm_str, TL(r = munchExp(left), NULL), NULL, NULL));
            } else { /* BINOP(op, e, e) */
                WRITE_ASM_STR("%s `s0, `d0", op);
                emit(AS_Oper(p2asm_str, TL(r = munchExp(right), NULL), TL(munchExp(left), NULL), NULL));
            }
            return r;
		}
		case T_MEM: 
        {
            T_exp mem = e->u.MEM;
            if (mem->kind == T_BINOP && mem->u.BINOP.op == T_plus) {
                T_exp left = mem->u.BINOP.left, right = mem->u.BINOP.right;
                if (left->kind == T_CONST) { /* MEM(BINOP(+, CONST, e)) */
                    WRITE_ASM_STR("mov %d(`s0), `d0", left->u.CONST);
                    emit(AS_Move(p2asm_str, TL(r, NULL), TL(munchExp(right), NULL)));
                } else if (right->kind == T_CONST) { /**/
                    WRITE_ASM_STR("mov %d(`s0), `d0", right->u.CONST);
                    emit(AS_Move(p2asm_str, TL(r, NULL), TL(munchExp(left), NULL)));
                } else assert(0 && "invalid MEM-BINOP"); /*??? this shouldnot occur */
            } else if (mem->kind == T_CONST) { /* MEM(CONST) */
                WRITE_ASM_STR("mov ($0x%x), `d0", mem->u.CONST);
                emit(AS_Move(p2asm_str, TL(r, NULL), NULL));
            } else { /* MEM(e) */
                emit(AS_Move(String("mov (`s0), `d0"), TL(r, NULL), TL(munchExp(mem->u.MEM), NULL)));
            }
            return r;
        }
        case T_TEMP: return e->u.TEMP;
		case T_ESEQ: munchStm(e->u.ESEQ.stm); return munchExp(e->u.ESEQ.exp);
		case T_NAME: Temp_enter(F_TEMPMAP, r, Temp_labelstring(e->u.NAME)); return r;
		case T_CONST: 
        {
            WRITE_ASM_STR("mov $0x%x, `d0", e->u.CONST);
            emit(AS_Move(p2asm_str, TL(r, NULL), NULL));
            return r;
        }
        case T_CALL: 
        {
            r = munchExp(e->u.CALL.fun);
            emit(AS_Oper(String("call `s0"), F_calldefs(), TL(r, munchArgs(0, e->u.CALL.args)), NULL));
			return r; /* return value unsure */
        }
		default: assert(0 && "invalid T_exp");
	}
}


#define ASSEM_MOVE_MEM_PLUS(Dst, Src, Constt) \
	T_exp e1 = Dst, e2 = Src; \
    int constt = Constt; \
    sprintf(assem_string, "mov `s1, %d(`s0)", constt); \
    p2asm_str = String(assem_string); \
    emit(AS_Move(p2asm_str, NULL, TL(munchExp(e1), TL(munchExp(e2), NULL))))

#define MATCH_CMP(I, Op) \
	switch (I) { \
		case T_eq: Op = "je"; break; \
		case T_ne: Op = "jne"; break; \
		case T_lt: Op = "jl"; break; \
		case T_gt: Op = "jg"; break; \
		case T_le: Op = "jle"; break; \
		case T_ge: Op = "jge"; break; \
		default: assert(0 && "Invalid CMP SIGN"); \
	} \
"for short ';'"

static void munchStm(T_stm s)
{
	char assem_string[100];
	string p2asm_str;

	switch (s->kind) {
		case T_MOVE:
        {
            T_exp dst = s->u.MOVE.dst, src = s->u.MOVE.src;
            if (dst->kind == T_MEM) {
                if (dst->u.MEM->kind == T_BINOP && dst->u.MEM->u.BINOP.op == T_plus) {
                    if (dst->u.MEM->u.BINOP.right->kind == T_CONST) { /* MOVE (MEM(BINOP(+, e, CONST)), e) */
                        ASSEM_MOVE_MEM_PLUS(dst->u.MEM->u.BINOP.left, src, dst->u.MEM->u.BINOP.right->u.CONST);	
                    } 
                    if (dst->u.MEM->u.BINOP.left->kind == T_CONST) { /* MOVE (MEM(BINOP(+, CONST, e)), e) */
                        ASSEM_MOVE_MEM_PLUS(dst->u.MEM->u.BINOP.right, src, dst->u.MEM->u.BINOP.left->u.CONST);			
                    }
                } else if (dst->u.MEM->kind == T_CONST) { /* MOVE(MEM(CONST), e) */
                    WRITE_ASM_STR("mov `s0, (%d)", dst->u.MEM->u.CONST);
                    emit(AS_Move(p2asm_str, NULL, TL(munchExp(src), NULL)));
                } else if (src->kind == T_MEM) { /* MOVE(MEM(e), MEM(e)) */
                    emit(AS_Move("mov `s1, (`s0)", NULL, TL(munchExp(dst->u.MEM), TL(munchExp(src->u.MEM), NULL))));
                } else { /* MOVE(MEM(e), e) */
                    emit(AS_Move(String("mov `s1, (`s0)"), NULL, TL(munchExp(dst->u.MEM), TL(munchExp(src), NULL))));
                }	
            } else if(dst->kind == T_TEMP) { /* MOVE(TEMP(e), e) */
                emit(AS_Move(String("mov `s0, `d0"), TL(munchExp(dst), NULL), TL(munchExp(src), NULL)));	
            } else assert(0 && "MOVE dst error");
            break;
        }
		case T_SEQ: munchStm(s->u.SEQ.left); munchStm(s->u.SEQ.right); break;
		case T_LABEL: 
        {
            WRITE_ASM_STR("%s", Temp_labelstring(s->u.LABEL));
            emit(AS_Label(p2asm_str, s->u.LABEL)); 
            break;
        }
		case T_JUMP: 
        {
            Temp_temp r = munchExp(s->u.JUMP.exp);
            emit(AS_Oper(String("jmp `d0"), TL(r, NULL), NULL, AS_Targets(s->u.JUMP.jumps)));
            break;
        }
		case T_CJUMP: 
        {
            char * cmp;
            Temp_temp left = munchExp(s->u.CJUMP.left), right = munchExp(s->u.CJUMP.right);
            emit(AS_Oper(String("cmp `s0, `s1"), NULL, TL(left, TL(right, NULL)), NULL));
            MATCH_CMP(s->u.CJUMP.op, cmp);	
            WRITE_ASM_STR("%s `j0", cmp);
            emit(AS_Oper(p2asm_str, NULL, NULL, AS_Targets(Temp_LabelList(s->u.CJUMP.true, NULL))));
            break;	
        }
		case T_EXP: munchExp(s->u.EXP); break;
		default: assert("Invalid T_stm" && 0);
	}
}

static string reg_names[] = {"eax", "ebx", "ecx", "edx", "edi", "esi"}; 
static int    reg_count = 0;
static Temp_tempList munchArgs(int i, T_expList args/*, F_accessList formals*/) 
{
	/* pass params to function
	 * actually use all push stack, no reg pass paras
	 */

	/* get args register-list */
	if (!args) return NULL;

	Temp_tempList tlist = munchArgs(i + 1, args->tail);
	Temp_temp rarg = munchExp(args->head);
	char assem_string[100];
	string p2asm_str;

	emit(AS_Oper(String("push `s0"), NULL, TL(rarg, NULL), NULL));	
	return (rarg, tlist);
}

static AS_instrList instrList = NULL, last = NULL;
static void emit (AS_instr instr) {
	if (!instrList) {
		instrList = AS_InstrList(instr, NULL);
		last = instrList;
	} else {
		last->tail = AS_InstrList(instr, NULL);
		last = last->tail;
	}
}

AS_instrList codegen(F_frame f, T_stmList s)
{
    /* interface */
    AS_instrList al = NULL;
    T_stmList sl    = s;
    Co_frame = f;
    for (; sl; sl = sl->tail) {
        munchStm(sl->head);
    }
    al = instrList;
    instrList = last = NULL;
    return al;
}
