#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "types.h"
#include "temp.h"
#include "frame.h"
#include "translate.h"

struct Tr_level_ {
	Tr_level parent;
	Temp_label name;
	F_frame frame;
	Tr_accessList formals;
};

struct Tr_access_ {
	Tr_level level;
	F_access access;
};

static Tr_accessList makeFormalAccessList(Tr_level);
static Tr_access Tr_Access(Tr_level, F_access);
/**debug info**/
static void display_l(Tr_level);
static void display_ac(Tr_access);

Tr_level Tr_newLevel(Tr_level p, Temp_label n, U_boolList f) {
	
	Tr_level l = checked_malloc(sizeof(*l));
	l->parent = p;
	l->name = n;
	l->frame = F_newFrame(n, U_BoolList(TRUE, f));
	l->formals = makeFormalAccessList(l);
	#ifdef F_P
	display_l(l);
	#endif
	return l;
}

Tr_access Tr_allocLocal(Tr_level l, bool escape) {
	Tr_access a = checked_malloc(sizeof(*a));
	a->level = l;
	a->access = F_allocLocal(l->frame, escape);
	#ifdef F_P
	display_ac(a);
	#endif	
	return a;
}

Tr_accessList Tr_AccessList(Tr_access h, Tr_accessList t) {
	Tr_accessList al = checked_malloc(sizeof(*al));
	al->head = h;
	al->tail = t;
	return al;
} 

Tr_accessList Tr_formals(Tr_level l) {
	return l->formals;
}

/*
 * get the access-list from frame (ingnore the first one)
 */
static Tr_accessList makeFormalAccessList(Tr_level l) {
	Tr_accessList head = NULL, tail = NULL;
	F_accessList  acsl = F_formals(l->frame)->tail; /*ignore the first one for static-link*/
	for (; acsl; acsl = acsl->tail) {
		Tr_access ac = Tr_Access(l, acsl->head);
		if (head) {
			tail->tail = Tr_AccessList(ac, NULL);
			tail = tail->tail;
		} else {
			head = Tr_AccessList(ac, NULL);
			tail = head;
		}
	}
	return head;
}

static Tr_level outer = NULL;
Tr_level Tr_outermost(void) {
	if (!outer) outer = Tr_newLevel(NULL, Temp_newlabel(), NULL);
	return outer;
}

static Tr_access Tr_Access(Tr_level l, F_access a) {
	Tr_access T_a = checked_malloc(sizeof(*T_a));
	T_a->level  = l;
	T_a->access = a;
	return T_a;
}

static void display_l(Tr_level l) {
	static int lnum;
	if (l->parent) {
		printf("parent: %s\n", Temp_labelstring(l->parent->name));
	} else {
		printf("parent: root\n");
	}
	printf("addr: %s\n", Temp_labelstring(l->name));
	display_f(l->frame);
}

static void display_ac(Tr_access ac) {
	printf("level: %s\n", Temp_labelstring(ac->level->name));	
	dis_ac(ac->access);
}

