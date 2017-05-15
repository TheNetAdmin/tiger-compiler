/* 27.11.14 by Mkth
 * Abstract Struct Tree engine
 * input is file of tig
 * output is A_exp Tree
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "parse.h"
#include "prabsyn.h"
#include "semant.h"

extern int yyparse(void);
extern A_exp absyn_root;

/* parse source file fname; 
   return abstract syntax data structure */
A_exp parse(string fname) 
{
	EM_reset(fname);
    if (yyparse() == 0) /* parsing worked */
		return absyn_root;
	else 
		printf("fuck! not pass syntax!\n");
		return NULL;
}

A_exp newATree();

int main(int argc, char **argv) {
    if (argc != 2){
		fprintf(stderr, "usage: a.out filename\n");
		exit(1);
	}
	A_exp temp = parse(argv[1]);
	FILE * f1 = fopen("1.txt", "r+");
	FILE * f2 = fopen("2.txt", "r+");
	assert(f1 && f2 && "file open failed");
	if (temp) {
		pr_exp(/*stdout*/f1, temp, 4);
	}
	pr_exp(f2, newATree(), 4);
	fclose(f1);
	fclose(f2);
	return 0;
}

A_exp newATree() {
	/* while exp 
	 * while 1 do 1
	 */
	A_exp e = A_WhileExp((A_pos)0, A_IntExp((A_pos)0, 1), A_IntExp((A_pos)0, 1));
	return e;

}
