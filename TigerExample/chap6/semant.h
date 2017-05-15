#ifndef SEM_H
#define SEM_H
typedef void * Tr_exp;
struct expty {Tr_exp exp; Ty_ty ty;};
void SEM_transProg(A_exp exp);
#endif
