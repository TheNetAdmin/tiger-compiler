/* 29.11.14 by Mkth
 * translate to Tree IR
 * input A_exp AST
 * output function Fragment
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"
#include "parse.h"
#include "prabsyn.h"
#include "types.h"
#include "temp.h"
#include "tree.h"
#include "frame.h"
#include "translate.h"
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

int main(int argc, char **argv) {
    if (argc != 2){
		fprintf(stderr, "usage: a.out filename\n");
		exit(1);
	}
	A_exp temp = parse(argv[1]);
	FILE * f1 = fopen("1.txt", "w");
	FILE * f2 = fopen("2.txt", "w");
	if (temp) {
		F_fragList fl = SEM_transProg(temp);
		print_frag(fl, f1);
	}
	fclose(f1);
	fclose(f2);
	return 0;
}

F_fragList newAFragment()
{
	F_fragList fl = 0;
	return 	fl;
}
