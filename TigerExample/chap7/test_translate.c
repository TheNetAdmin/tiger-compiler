//@@@
void test_Tr_expList_prepend(Tr_expList l) {
	while(l) {
		printf("Tr_exp->type: %d\n", l->head->kind);
		l = l->tail;
	}
}
//@@@
void test_T_expList(T_expList l) {
	while(l) {
		printf("T_exp->type: %d\n", l->head->kind);
		l = l->tail;
	}
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

T_exp public_unEx(Tr_exp e) {
	return unEx(e);
}
T_stm public_unNx(Tr_exp e) {
	return unNx(e);
}
//@@@ print Tr_exp
void print(Tr_exp et, FILE * out) {
    if (et->kind == Tr_ex) printExp(unEx(et), out);
	if (et->kind == Tr_nx) printStm(unNx(et), out);
	if (et->kind == Tr_cx) printStm(unCx(et).stm, out);
} 

void print_frag(F_fragList fl, FILE * out) {
	if (!fl) {
		puts("fragList is NULL");
		return;
	}
	while (fl) {
		F_frag f = fl->head;
		switch(f->kind) {
		case F_stringFrag:
			print(Tr_Ex(T_Name(f->u.stringg.label)), out);
			fprintf(out, "\n");
			break;
		case F_procFrag:
			print(Tr_Nx(f->u.proc.body), out);
			break;
		default: assert(0 && "frag-kind is error");
		}
		fl = fl->tail;
	}
}
