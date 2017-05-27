%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define api.namespace {Tiger}
%define parser_class_name {Parser}
%define api.value.type variant
%define parse.assert
%locations

%code requires{
    namespace Tiger{
        class Driver;
        class Scanner;
    }
}

%parse-param {Driver & driver}


%{
#include <iostream>
#include <string>
#include "error.h"
#include "driver.h"

ParserError PE;
void yyerror(char *s)
{
    PE.print({s});
}

%}

%token <std::string> ID
%token <std::string> STRING
%token <int> INT

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

%type <A_exp> exp program funcall seq record array
%type <A_var> lvalue
%type <A_decList> decs
%type <A_dec> dec tydecs fundecs vardec
%type <A_fundec> fundec
%type <A_namety> tydec
%type <A_expList> explist args
%type <S_symbol> id
%type <A_efieldList> refields
%type <A_ty> ty
%type <A_fieldList> typefields
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

%%
