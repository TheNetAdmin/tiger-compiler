/*
** 1.
** 2. Tree node is typedef (a typedef map a grammer)
** 3. only use point to struct not use struct-self
** 4. struct hava 2 member {kind, u}
** 7. only construct call malloc
** 8. every model has its ex-
** 9. type def use low-char, construct func use up-char, member use low-char 
*/
typedef struct A_stm_ * A_stm; /*struct pointer*/
typedef struct A_exp_ * A_exp;
typedef struct A_expList_ * A_expList;
typedef enum {A_plus,A_minus,A_times,A_div} A_binop;

enum A_grammerEle
     {
		 A_compoundStm, A_assignStm, A_printStm,
		 A_idExp, A_numExp, A_opExp, A_eseqExp,
		 A_pairExpList, A_lastExpList
     };

struct A_stm_ {
    enum A_grammerEle kind; /* stm-grammer constructor */
    union {
	    struct {A_stm stm1, stm2;} compound;
        struct {string id; A_exp exp;} assign;
        struct {A_expList exps;} print;
    } u;
};

A_stm A_CompoundStm(A_stm stm1, A_stm stm2);
A_stm A_AssignStm(string id, A_exp exp);
A_stm A_PrintStm(A_expList exps);

struct A_exp_ {
	enum A_grammerEle kind;
    union {
		string id;
        int num;
        struct {A_exp left; A_binop oper; A_exp right;} op;
        struct {A_stm stm; A_exp exp;} eseq;
    } u;
};

A_exp A_IdExp(string id);
A_exp A_NumExp(int num);
A_exp A_OpExp(A_exp left, A_binop oper, A_exp right);
A_exp A_EseqExp(A_stm stm, A_exp exp);

struct A_expList_ {
	enum A_grammerEle kind;
    union {
		struct {A_exp head; A_expList tail;} pair;
        A_exp last;
    } u;
};

A_expList A_PairExpList(A_exp head, A_expList tail);
A_expList A_LastExpList(A_exp last);
/*
** alter the enum for diff each grammer ...
*/
