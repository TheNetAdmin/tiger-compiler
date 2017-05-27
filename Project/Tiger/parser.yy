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

program:  exp

exp: lvalue
   | funcall
   | lvalue ASSIGN exp 
   | NIL
   | seq
   | INT
   | DOUBLE
   | STRING
   | LET decs IN explist END
   | IF exp THEN exp ELSE exp
   | IF exp THEN exp
   | exp PLUS exp 
   | exp MINUS exp 
   | exp TIMES exp
   | exp DIVIDE exp
   | exp EQ exp
   | MINUS exp %prec UMINUS
   | exp NEQ exp
   | exp GT exp
   | exp LT exp
   | exp GE exp
   | exp LE exp
   | exp AND exp
   | exp OR exp
   | record
   | array
   | WHILE exp DO exp 
   | FOR id ASSIGN exp TO exp DO exp
   | BREAK 

seq: LPAREN explist RPAREN 

record: id LBRACE refields RBRACE

refields: id EQ exp COMMA refields
        | id EQ exp
        |

array: id LBRACK exp RBRACK OF exp 


decs: dec decs
    | 

dec: tydecs
   | vardec
   | fundecs

tydecs: tydec tydecs
      | tydec
   
tydec: TYPE id EQ ty

ty:	id 
  | LBRACE typefields RBRACE
  | ARRAY OF id

typefields: id COLON id COMMA typefields
          | id COLON id
		  |

vardec: VAR id ASSIGN exp 
      | VAR id COLON id ASSIGN exp

fundecs: fundec fundecs
	   | fundec

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp

explist: exp SEMICOLON explist
	   | exp
	   |

lvalue: id	
      | lvalue DOT id
	  | id LBRACK exp RBRACK
	  | lvalue LBRACK exp RBRACK

funcall: id LPAREN args RPAREN 

args: exp COMMA args
    | exp
	|

id: ID
