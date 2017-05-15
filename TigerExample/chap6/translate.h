typedef struct Tr_access_ * Tr_access;
typedef struct Tr_level_ * Tr_level;

typedef struct Tr_accessList_ * Tr_accessList;
struct Tr_accessList_ {
	Tr_access head;
	Tr_accessList tail;
};

Tr_accessList Tr_AccessList(Tr_access h, Tr_accessList t);
Tr_level Tr_outermost(void);
Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals);
Tr_accessList Tr_formals(Tr_level level);
Tr_access Tr_allocLocal(Tr_level l, bool e);
/**************************************/
typedef void * Tr_exp;
