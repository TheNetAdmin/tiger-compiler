/*
 * parse.c - Parse source file.
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
#include "printtree.h"
#include "canon.h"
#include "assem.h"
#include "codegen.h"

extern anyErrors;
extern int yyparse(void);
extern A_exp absyn_root;
extern Temp_map F_tempMap;

/* parse source file fname; 
   return abstract syntax data structure */

A_exp parse(string fname) 
{
	EM_reset(fname);
    if (yyparse() == 0) 
		return absyn_root;
	else 
		printf("fuck! not pass syntax!\n");
		return NULL;
}

static void doProc(FILE *out, F_frame frame, T_stm body)
{
 //printStm(body);
 AS_proc proc;
 //struct RA_result allocation;
 T_stmList stmList;
 AS_instrList iList;

 stmList = C_linearize(body);
 //printStmList(stdout, stmList);
 stmList = C_traceSchedule(C_basicBlocks(stmList));
 /* printStmList(stdout, stmList); */
 iList  = codegen(frame, stmList); /* 9 */
 //printStmList(stdout, stmList);
 fprintf(out, "BEGIN %s\n", Temp_labelstring(F_name(frame)));
 AS_printInstrList (out, iList, Temp_layerMap(F_tempMap,Temp_name()));
 fprintf(out, "END %s\n\n", Temp_labelstring(F_name(frame)));
}

int main(int argc, string *argv)
{
 A_exp absyn_root;
 S_table base_env, base_tenv;
 F_fragList frags;
 char outfile[100];
 FILE *out = stdout;

 if (argc==2) {
   absyn_root = parse(argv[1]);
   if (!absyn_root) return 1;
   #if 0 
   pr_exp(out, absyn_root, 0); /* print absyn data structure */
   fprintf(out, "\n");
   #endif

   frags = SEM_transProg(absyn_root);
   if (anyErrors) return 1; /* don't continue */

   /* convert the filename */
   sprintf(outfile, "%s.s", argv[1]);
   out = fopen(outfile, "w");

   for (;frags;frags=frags->tail) {
        if (frags->head->kind == F_procFrag) {
            //printStm(frags->head->u.proc.body);
            doProc(out, frags->head->u.proc.frame, frags->head->u.proc.body);
        }
        else if (frags->head->kind == F_stringFrag) {
            fprintf(out, "%s: %s\n",Temp_labelstring(frags->head->u.stringg.label), frags->head->u.stringg.str);
        }
        else assert(0);
   }
   fclose(out);
   return 0;
 }
 EM_error(0,"usage: tiger file.tig");
 return 1;
}
