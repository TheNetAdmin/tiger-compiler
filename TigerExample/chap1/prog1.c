#include "util.h"
#include "slp.h"
#include "prog1.h"
#define ADD_QUE(ind, kindval, pty, pval) queue[ind].kind = kindval;\
										 queue[ind].p.pty = pval;  \
										 ind++
/*
** s: a := 5+3; b := print (a, (a-1), 10*a); print (b)
 */
A_stm prog(void) 
{
    return 
    A_CompoundStm(
	    A_AssignStm("a",A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),   
		A_CompoundStm(
			A_AssignStm(
				"b",
				A_EseqExp(
					A_PrintStm(
						A_PairExpList(
							A_IdExp("a"),
							A_LastExpList(A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1)))
						)
					),
					A_OpExp(A_NumExp(10), A_times, A_IdExp("a"))
			    )
			),
			A_PrintStm(A_LastExpList(A_IdExp("b")))
		)
   );
}
/* print (3,4,5,4) */
A_stm prog1(void) 
{
	return 
	A_PrintStm(
		A_PairExpList(
			A_NumExp(3),
			A_PairExpList(
				A_NumExp(4),
				A_PairExpList(
					A_NumExp(5),
					A_LastExpList(A_NumExp(4))
				)
			)
		)
	);
}
/* print (1,2,3,(print(1,2,3,4), 6)) */
A_stm prog2(void)
{
	return
	A_PrintStm(
		A_PairExpList(
			A_NumExp(1),
			A_PairExpList(
				A_NumExp(2),
				A_PairExpList(
					A_NumExp(3),
					A_LastExpList(
						A_EseqExp(
							A_PrintStm(
								A_PairExpList(
									A_NumExp(1),
									A_PairExpList(
										A_NumExp(2),
										A_PairExpList(
											A_NumExp(3),
											A_LastExpList(A_NumExp(4))
										)
									)
								)
							),
							A_NumExp(6)
						)
					)
				)
			)
		)
	);
}
int maxargs(A_stm s)
{
	/*init*/
	int temp_max = 0; 
	int max = 0;
	int i; /*current position*/
	int j; /*queue position*/
	struct queone queue[MAX_QUEUE];
	for (i = 0; i < MAX_QUEUE; i++) {
		queue[i].kind = A_null;
	}
    j = 0;

	/* add init data to queue */
	ADD_QUE(j, A_stm_e, stm, s);
	/*  */
	for (i = 0; (queue[i].kind != A_null); i++) {
		if (queue[i].kind == A_stm_e) {
			switch (queue[i].p.stm->kind){
			case A_printStm:
				temp_max = 0;
				/* add pair-exp to queue */
				A_expList temp = queue[i].p.stm->u.print.exps;
				ADD_QUE(j, A_expList_e, explist, temp);
				/* bad code ex: !!! equals ADD_QUE(ind, ...)
				queue[j].kind = A_expList_e;
				queue[j].p.explist = queue[i].p.stm->u.print.exps;
				j++;
				*/

				/* count print args */
                while (temp->kind != A_lastExpList)	{
					temp_max++;
					temp = temp->u.pair.tail;
				}
				if ((++temp_max) > max) {
					max = temp_max;
				}
				/*bingo*/
				break;
			case A_compoundStm:
				ADD_QUE(j, A_stm_e, stm, queue[i].p.stm->u.compound.stm1);
				ADD_QUE(j, A_stm_e, stm, queue[i].p.stm->u.compound.stm2);
				break;
			case A_assignStm:
				ADD_QUE(j, A_exp_e, exp, queue[i].p.stm->u.assign.exp);
				break;
			}
		}
		if (queue[i].kind == A_exp_e) {
			switch (queue[i].p.exp->kind){
			case A_opExp:
				ADD_QUE(j, A_exp_e, exp, queue[i].p.exp->u.op.left);
				ADD_QUE(j, A_exp_e, exp, queue[i].p.exp->u.op.right);
				break;
			case A_eseqExp:
				ADD_QUE(j, A_stm_e, stm, queue[i].p.exp->u.eseq.stm);
				ADD_QUE(j, A_exp_e, exp, queue[i].p.exp->u.eseq.exp);
				break;
			}
		}
		if (queue[i].kind == A_expList_e) {
			switch (queue[i].p.explist->kind){
			case A_pairExpList:
				ADD_QUE(j, A_exp_e, exp, queue[i].p.explist->u.pair.head);
				ADD_QUE(j, A_expList_e, explist, queue[i].p.explist->u.pair.tail);
				break;
			case A_lastExpList:
				ADD_QUE(j, A_exp_e, exp, queue[i].p.explist->u.last);
				break;
			default:
				/* do something */
				break;
			}
		}
	}
	/* look a queue ele kind */
	/*
	for (i = 0; i < MAX_QUEUE && (queue[i].kind != A_null); i++) {
			printf("%d\n", queue[i].kind);
	}
	*/
	return max;
}

Table AssignTable(string id, int value, Table tail)
{
	Table t = checked_malloc(sizeof(*t));
	t->id = id;
	t->value = value;
	t->tail = tail;
	return t;
}

int lookup(Table t, string key)
{
	Table temp = t;
	while (temp) {
		if (key == temp->id) {
			return temp->value;
		}
		temp = temp->tail;
	}
	assert("fuck undef iditify");
}

Table update(Table t, string id,int value)
{
	Table temp = checked_malloc(sizeof(*temp));
	temp->id = id;
	temp->value = value;
	temp->tail = t;
	return temp;
}


Table interpStm(A_stm s, Table t)
{   
	Table t1,t2;
	struct ExpResl er1; 
	A_expList e1;
	
	switch (s->kind) {
	case A_compoundStm:
		t1 = interpStm(s->u.compound.stm1, t);
		t2 = interpStm(s->u.compound.stm2, t1);
		return t2;
	case A_assignStm:
		er1 = interpExp(s->u.assign.exp, t);
		t1 = update(er1.t, s->u.assign.id, er1.i);
		return t1;
	case A_printStm:
		e1 = s->u.print.exps;
		t1 = t;
		while (e1->kind == A_pairExpList) {
			er1 = interpExp(e1->u.pair.head, t1);
			printf("%d ", er1.i);
			t1 = er1.t;
			e1 = e1->u.pair.tail;
		}
		if (e1->kind == A_lastExpList) {
			er1 = interpExp(e1->u.last, t1);
			printf("%d ", er1.i);
		}
		return er1.t;
	}
	return 0;
}

struct ExpResl interpExp(A_exp e, Table t)
{
	Table t1;
	struct ExpResl er1, er2;
	switch (e->kind) {
	case A_numExp:
		er1.i = e->u.num;
		er1.t = t;
		return er1;
	case A_idExp:
		er1.i = lookup(t, e->u.id);
		er1.t = t;
		return er1;
	case A_opExp:
		er1 = interpExp(e->u.op.left, t);
		er2 = interpExp(e->u.op.right, er1.t);
        switch (e->u.op.oper) {
		case A_plus:
			return (er2.i = er1.i + er2.i, er2);
		case A_minus:
			return (er2.i = er1.i - er2.i, er2);
		case A_times:
			return (er2.i = er1.i * er2.i, er2);
		case A_div:
			return (er2.i = er1.i / er2.i, er2);
		}		
	case A_eseqExp:
		t1 = interpStm(e->u.eseq.stm, t);
		er1 = interpExp(e->u.eseq.exp, t1);
		return er1;
	}
}

void interp(A_stm s) {
	Table t = 0;
	Table resl;
	resl = interpStm(s, t);
	printf("\n");
}


