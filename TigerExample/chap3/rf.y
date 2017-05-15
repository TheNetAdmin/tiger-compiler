%{
#include <stdio.h>
#include "util.h"
#include "errormsg.h"

#define YYDEBUG 1
#define F(s) printf("%s\n", s) 

int yylex(void); /* function prototype */

void yyerror(char *s)
{
  EM_error(EM_tokPos, "%s\n", s);
}
%}

%union {
	int pos;
	int ival;
	string sval;
}

%token <sval> ID STRING
%token <ival> INT

%right ASSIGN
%left AND OR
%nonassoc EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%right DO OF ELSE /*optional*/
%right UMINUS

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE
  TEST

%start program

%%

program:  exp

exp: lvalue
   | funcall /*{F("exp->funcall");}*/
   | lvalue ASSIGN exp {F("exp->lval := exp");}
   | NIL
   | seq
   | INT
   | STRING
   | LET decs IN explist END
   | exp PLUS exp {F("plus");}
   | exp MINUS exp {F("minus");}
   | exp TIMES exp {F("exp * exp");}
   | exp DIVIDE exp {F("exp / exp");}
   | exp EQ exp
   | MINUS exp %prec UMINUS {F("u-mius");}
   | exp NEQ exp
   | exp GT exp
   | exp LT exp
   | exp GE exp
   | exp LE exp
   | exp AND exp
   | exp OR exp
   | record
   | array
   | IF exp THEN exp ELSE exp {F("if-then-else sentence");}
   | WHILE exp DO exp {F("while-do sentence");}
   | FOR id ASSIGN exp TO exp DO exp {F("for sentence");}
   | BREAK {F("break");}
   /*| LPAREN exp RPAREN*/

seq: LPAREN explist RPAREN {F("seq-exp");}

record: id LBRACE refields RBRACE

refields: id EQ exp COMMA refields
        | id EQ exp
        |

array: id LBRACK exp RBRACK OF exp {F("array create");}


decs: dec decs
    | 

dec: tydec
   | vardec
   | fundec

   
tydec: TYPE id EQ ty

ty:	id
  | LBRACE typefields RBRACE {F("ty->{tyfs}");}
  | ARRAY OF id {F("ty->array of ty-id");}

typefields: id COLON id COMMA typefields
          | id COLON id
		  | 

vardec: VAR id ASSIGN exp {F("vardec->var id := exp");}
      | VAR id COLON id ASSIGN exp {F("vardec->var id: ty := exp");}

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp

explist: exp SEMICOLON explist
	   | exp
	   |

lvalue: id /*{F("");}*/
      | lvalue DOT id {F("lval->lval.id");}
	  | lvalue LBRACK exp RBRACK {F("lval->[exp]");}

funcall: id LPAREN args RPAREN {F("funcall->foo([a,b,c...])");}

args: exp COMMA args
    | exp
	|

id: ID {printf("\n%s\n", $1);}
