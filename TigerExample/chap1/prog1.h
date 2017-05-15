#define MAX_QUEUE 500

typedef struct table * Table;

struct table {
    string id; 
	int value; 
	Table tail;
};

struct ExpResl{
	int i;
	Table t;
};

struct queone {
	enum {A_stm_e, A_exp_e, A_expList_e, A_null} kind; 
	union {
		A_stm stm;
		A_exp exp;
		A_expList explist;
	} p;
};

A_stm prog(void);
A_stm prog1(void);
A_stm prog2(void);
int maxargs(A_stm s);
struct ExpResl interpExp(A_exp e, Table t);

void interp(A_stm s);
