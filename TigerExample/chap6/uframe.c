#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "temp.h"
#include "frame.h"

const int F_WORD_SIZE = 4; /* 4 byte */
static const int F_MAX_REG = 6;  /* paras in regs number */ 

struct F_frame_ {
	Temp_label name;
	F_accessList formals;
	int local_count;/*local-var numb*/
	/*TODO "view shift"*/
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
/* 1. what params look like
 * 2. what orders view shift
 */
F_frame F_newFrame(Temp_label name, U_boolList formals) {
	F_frame f = checked_malloc(sizeof(*f));
	f->name = name;
	f->formals = makeFormalAccessList(f, formals);
	f->local_count = 0;
	return f;
}

F_access F_allocLocal(F_frame f, bool escape) {
	f->local_count++;
	if (escape) return InFrame(-1 * F_WORD_SIZE * f->local_count);
	return InReg(Temp_newtemp());
}

F_accessList F_formals(F_frame f) {
	return f->formals;
}

static F_accessList makeFormalAccessList(F_frame f, U_boolList formals) {
	U_boolList fmls = formals;
	F_accessList head = NULL, tail = NULL;
	int i = 0;
	for (; fmls; fmls = fmls->tail, i++) {
		F_access ac = NULL;
		if (i < F_MAX_REG && !fmls->head) {
			ac = InReg(Temp_newtemp());
		} else {
			/* may return */
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
