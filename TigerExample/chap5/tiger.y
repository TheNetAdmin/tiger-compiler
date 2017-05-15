%{

#include <stdio.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "errormsg.h"

int yylex(void); /* function prototype */

A_exp absyn_root;

void yyerror(char *s)
{
	EM_error(EM_tokPos, "%s", s);
}

%}


%union {
	int pos;
	int ival;
	double dval;
	string sval;
	S_symbol sym;
	A_var var;
	A_exp exp;
    A_dec dec;
	A_decList declist;
	A_expList explist;
	A_efieldList efieldlist;
	A_ty ty;
	A_fieldList fieldlist;
	A_fundec fundec;
	A_namety namety;
	/* et cetera */
}

%token <sval> ID STRING
%token <ival> INT
%token <dval> DOUBLE

/*%nonassoc LOW*/
%right ASSIGN
%left AND OR
%nonassoc EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
/*%right DO OF ELSE optional*/
%left UMINUS

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE 

%type <exp> exp program funcall seq record array
%type <var> lvalue
%type <declist> decs
%type <dec> dec tydecs fundecs vardec
%type <fundec> fundec
%type <namety> tydec
%type <explist> explist args
%type <sym> id
%type <efieldlist> refields
%type <ty> ty
%type <fieldlist> typefields
/* et cetera */

%start program

%%

program:  exp {absyn_root=$1;}

exp: lvalue {$$ = A_VarExp(EM_tokPos, $1);}
   | funcall {$$ = $1;}
   | lvalue ASSIGN exp {$$ = A_AssignExp(EM_tokPos, $1, $3);} 
   | NIL {$$ = A_NilExp(EM_tokPos);}
   | seq {$$ = $1;}
   | INT {$$ = A_IntExp(EM_tokPos, $1);}
   | DOUBLE {$$ = A_DoubleExp(EM_tokPos, $1);}
   | STRING {$$ = A_StringExp(EM_tokPos, $1);}
   | LET decs IN explist END {$$ = A_LetExp(EM_tokPos, $2, A_SeqExp(EM_tokPos, $4));}
   | IF exp THEN exp ELSE exp {$$ = A_IfExp(EM_tokPos, $2, $4, $6);}
   | IF exp THEN exp {$$ = A_IfExp(EM_tokPos, $2, $4, NULL);}
   | exp PLUS exp {$$ = A_OpExp(EM_tokPos, A_plusOp, $1, $3);} 
   | exp MINUS exp {$$ = A_OpExp(EM_tokPos, A_minusOp, $1, $3);} 
   | exp TIMES exp {$$ = A_OpExp(EM_tokPos, A_timesOp, $1, $3);}
   | exp DIVIDE exp {$$ = A_OpExp(EM_tokPos, A_divideOp, $1, $3);}
   | exp EQ exp {$$ = A_OpExp(EM_tokPos, A_eqOp, $1, $3);}
   | MINUS exp %prec UMINUS {$$ = A_OpExp(EM_tokPos, A_minusOp, A_IntExp(EM_tokPos, 0), $2);}
   | exp NEQ exp {$$ = A_OpExp(EM_tokPos, A_neqOp, $1, $3);}
   | exp GT exp {$$ = A_OpExp(EM_tokPos, A_gtOp, $1, $3);}
   | exp LT exp {$$ = A_OpExp(EM_tokPos, A_ltOp, $1, $3);}
   | exp GE exp {$$ = A_OpExp(EM_tokPos, A_geOp, $1, $3);}
   | exp LE exp {$$ = A_OpExp(EM_tokPos, A_leOp, $1, $3);}
   | exp AND exp {$$ = A_IfExp(EM_tokPos, $1, $3, A_IntExp(EM_tokPos, 0));}
   | exp OR exp {$$ = A_IfExp(EM_tokPos, $1, A_IntExp(EM_tokPos,1), $3);}
   | record {$$ = $1;}
   | array {$$ = $1;}
   | WHILE exp DO exp {$$ = A_WhileExp(EM_tokPos, $2, $4);} 
   | FOR id ASSIGN exp TO exp DO exp {$$ = A_ForExp(EM_tokPos, $2, $4, $6, $8);}
   | BREAK {$$ = A_BreakExp(EM_tokPos);} 

seq: LPAREN explist RPAREN {$$ = A_SeqExp(EM_tokPos, $2);} 

record: id LBRACE refields RBRACE {$$ = A_RecordExp(EM_tokPos, $1, $3);}

refields: id EQ exp COMMA refields {$$ = A_EfieldList(A_Efield($1, $3), $5);}
        | id EQ exp {$$ = A_EfieldList(A_Efield($1, $3), NULL);}
        | {$$ = NULL;}

array: id LBRACK exp RBRACK OF exp {$$ = A_ArrayExp(EM_tokPos, $1, $3, $6);} 


decs: dec decs {$$ = A_DecList($1, $2);}
    | {$$ = NULL;} 

dec: tydecs {$$ = $1;}
   | vardec {$$ = $1;}
   | fundecs {$$ = $1;}

tydecs: tydec tydecs {$$ = A_TypeDec(EM_tokPos, A_NametyList($1, $2->u.type));}
      | tydec {$$ = A_TypeDec(EM_tokPos, A_NametyList($1, NULL));}
   
tydec: TYPE id EQ ty {$$ = A_Namety($2, $4);}

ty:	id {$$ = A_NameTy(EM_tokPos, $1);} 
  | LBRACE typefields RBRACE {$$ = A_RecordTy(EM_tokPos, $2);}
  | ARRAY OF id {$$ = A_ArrayTy(EM_tokPos, $3);}

typefields: id COLON id COMMA typefields {$$ = A_FieldList(A_Field(EM_tokPos, $1, $3), $5);}
          | id COLON id {$$ = A_FieldList(A_Field(EM_tokPos, $1, $3), NULL);}
		  | {$$ = NULL;}

vardec: VAR id ASSIGN exp {/*printf("\n$%s$\n", $2);*/ $$ = A_VarDec(EM_tokPos, $2, NULL, $4);} 
      | VAR id COLON id ASSIGN exp {$$ = A_VarDec(EM_tokPos, $2, $4, $6);}

fundecs: fundec fundecs {$$ = A_FunctionDec(EM_tokPos, A_FundecList($1, $2->u.function));}
	   | fundec {$$ = A_FunctionDec(EM_tokPos, A_FundecList($1, NULL));}

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp {$$ = A_Fundec(EM_tokPos, $2, $4, NULL, $7);}
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp {$$ = A_Fundec(EM_tokPos, $2, $4, $7, $9);}

explist: exp SEMICOLON explist {$$ = A_ExpList($1, $3);}
	   | exp {$$ = A_ExpList($1, NULL);}
	   | {$$ = NULL;}

lvalue: id {/*printf("\nf$%s$f\n", S_name($1));*/ $$ = A_SimpleVar(EM_tokPos, $1);}	
      | lvalue DOT id {$$ = A_FieldVar(EM_tokPos, $1, $3);}
	  | id LBRACK exp RBRACK {$$ = A_SubscriptVar(EM_tokPos, A_SimpleVar(EM_tokPos, $1), $3);}
	  | lvalue LBRACK exp RBRACK {$$ = A_SubscriptVar(EM_tokPos, $1, $3);}

funcall: id LPAREN args RPAREN {$$ = A_CallExp(EM_tokPos, $1, $3);} 

args: exp COMMA args {$$ = A_ExpList($1, $3);}
    | exp {$$ = A_ExpList($1, NULL);}
	| {$$ = NULL;}

id: ID {/*printf("\n$%s$\n",$1);*/$$ = S_Symbol($1); /*printf("\nt$%s$t\n", S_name($$));*/}
