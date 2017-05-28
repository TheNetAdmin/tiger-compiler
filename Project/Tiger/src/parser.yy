%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define api.namespace {Tiger}
%define parser_class_name {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define parse.trace
%define parse.error verbose
%locations
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.filename;
}

%code requires{
    namespace Tiger{
        class Driver;
        class Scanner;
    }
}

%param{Tiger::Driver & driver}

%code
{
    #include "driver.h"
    #include "absyntree.h"
}

%token ENDFILE 0 "END OF FILE"
%token <std::string> ID
%token <std::string> STRING
%token <int> INT

/*%nonassoc LOW*/
%right ASSIGN
%left AND OR
%nonassoc EQ NEQ LT LE GT GE
%left PLUS MINUS
%left TIMES DIVIDE
%right DO OF ELSE
%left UMINUS

%token 
  COMMA COLON SEMICOLON LPAREN RPAREN LBRACK RBRACK 
  LBRACE RBRACE DOT 
  PLUS MINUS TIMES DIVIDE EQ NEQ LT LE GT GE
  AND OR ASSIGN
  ARRAY IF THEN ELSE WHILE FOR TO DO LET IN END OF 
  BREAK NIL
  FUNCTION VAR TYPE 

%type <shared_ptr<ExpAST>> exp program funcall seq record array
%type <shared_ptr<VarAST>> lvalue
%type <shared_ptr<DecListAST>> decs
%type <shared_ptr<DecAST>> dec tydecs fundecs vardec
%type <shared_ptr<FundecAST>> fundec
%type <shared_ptr<TypeTyAST>> tydec
%type <shared_ptr<ExpListAST>> explist args
%type <string> id
%type <shared_ptr<EfieldListAST>> refields
%type <shared_ptr<TyAST>> ty
%type <shared_ptr<FieldListAST>> typefields
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
   | STRING
   | LET decs IN explist END
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
   | IF exp THEN exp ELSE exp
   | IF exp THEN exp
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

dec: tydec
   | vardec
   | fundec

   
tydec: TYPE id EQ ty

ty:	id
  | LBRACE typefields RBRACE
  | ARRAY OF id

typefields: id COLON id COMMA typefields
          | id COLON id
		  | 

vardec: VAR id ASSIGN exp
      | VAR id COLON id ASSIGN exp

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
void Tiger::Parser::error (const location_type & l, const std::string & m)
{
    driver.error(l, m);
}