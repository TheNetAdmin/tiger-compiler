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
    #include "absyntree.h"
    namespace Tiger{
        class Driver;
        class Scanner;
    }
}

%param{Tiger::Driver & driver}

%code
{
    #include "absyntree.h"
    #include "driver.h"
    using namespace AST;
    shared_ptr<AST::Exp> absyn_root;
}

%token ENDFILE 0 "END OF FILE"
%token <string> ID
%token <string> STRING
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

%type <shared_ptr<AST::Exp>> exp program funcall seq record array
%type <shared_ptr<AST::Var>> lvalue
%type <shared_ptr<AST::DecList>> decs
%type <shared_ptr<AST::Dec>> dec tydecs fundecs vardec
%type <shared_ptr<AST::FunDec>> fundec
%type <shared_ptr<AST::TypeTy>> tydec
%type <shared_ptr<AST::ExpList>> explist args
%type <string> id
%type <shared_ptr<AST::EFieldList>> refields
%type <shared_ptr<AST::Ty>> ty
%type <shared_ptr<AST::FieldList>> typefields
/* et cetera */

%start program

%%

program:  exp {absyn_root = $1; driver.result = absyn_root;}

exp: lvalue {$$ = MakeVarExp(@$, $1);}
   | funcall {$$ = $1;}
   | lvalue ASSIGN exp {$$ = MakeAssignExp(@$, $1, $3);}
   | NIL {$$ = MakeNilExp(@$);}
   | seq {$$ = $1;}
   | INT {$$ = MakeIntExp(@$, $1);}
   | STRING {$$ = MakeStringExp(@$, $1);}
   | LET decs IN explist END {$$ = MakeLetExp(@$, $2, MakeSeqExp(@$, $4));}
   | IF exp THEN exp ELSE exp {$$ = MakeIfExp(@$, $2, $4, $6);}
   | IF exp THEN exp {$$ = MakeIfExp(@$, $2, $4, nullptr);}
   | exp PLUS exp {$$ = MakeOpExp(@$, PLUS, $1, $3);}
   | exp MINUS exp {$$ = MakeOpExp(@$, MINUS, $1, $3);}
   | exp TIMES exp {$$ = MakeOpExp(@$, TIMES, $1, $3);}
   | exp DIVIDE exp {$$ = MakeOpExp(@$, DIVIDE, $1, $3);}
   | exp EQ exp {$$ = MakeOpExp(@$, EQ, $1, $3);}
   | MINUS exp %prec UMINUS {$$ = MakeOpExp(@$, MINUS, MakeIntExp(@$, 0), $2);}
   | exp NEQ exp {$$ = MakeOpExp(@$, NEQ, $1, $3);}
   | exp GT exp {$$ = MakeOpExp(@$, GT, $1, $3);}
   | exp LT exp {$$ = MakeOpExp(@$, LT, $1, $3);}
   | exp GE exp {$$ = MakeOpExp(@$, GE, $1, $3);}
   | exp LE exp {$$ = MakeOpExp(@$, LE, $1, $3);}
   | exp AND exp {$$ = MakeIfExp(@$, $1, $3, MakeIntExp(@$, 0));}
   | exp OR exp {$$ = MakeIfExp(@$, $1, MakeIntExp(@$,1), $3);}
   | record {$$ = $1;}
   | array {$$ = $1;}
   | WHILE exp DO exp {$$ = MakeWhileExp(@$, $2, $4);}
   | FOR id ASSIGN exp TO exp DO exp {$$ = MakeForExp(@$, $2, $4, $6, $8);}
   | BREAK {$$ = MakeBreakExp(@$);}

seq: LPAREN explist RPAREN {$$ = MakeSeqExp(@$, $2);}

record: id LBRACE refields RBRACE {$$ = MakeRecordExp(@$, $1, $3);}

refields: id EQ exp COMMA refields {$$ = MakeEFieldList(MakeEField($1, $3), $5);}
        | id EQ exp {$$ = MakeEFieldList(MakeEField($1, $3), nullptr);}
        | {$$ = nullptr;}

array: id LBRACK exp RBRACK OF exp {$$ = MakeArrayExp(@$, $1, $3, $6);}


decs: dec decs {$$ = MakeDecList($1, $2);}
    | {$$ = nullptr;} 

dec: tydecs {$$ = $1;}
   | vardec {$$ = $1;}
   | fundecs {$$ = $1;}

tydecs: tydec tydecs {$$ = MakeTypeDec(@$, MakeTypeTyList($1, dynamic_pointer_cast<TypeDec>($2)->getType()));}
      | tydec {$$ = MakeTypeDec(@$, MakeTypeTyList($1, nullptr));}
   
tydec: TYPE id EQ ty {$$ = MakeTypeTy($2, $4);}

ty:	id {$$ = MakeNameTy(@$, $1);}
  | LBRACE typefields RBRACE {$$ = MakeRecordTy(@$, $2);}
  | ARRAY OF id {$$ = MakeArrayTy(@$, $3);}

typefields: id COLON id COMMA typefields {$$ = MakeFieldList(MakeField(@$, $1, $3), $5);}
          | id COLON id {$$ = MakeFieldList(MakeField(@$, $1, $3), nullptr);}
		  | {$$ = nullptr;}

vardec: VAR id ASSIGN exp {string s = ""; $$ = MakeVarDec(@$, $2, s, $4);}
      | VAR id COLON id ASSIGN exp {$$ = MakeVarDec(@$, $2, $4, $6);}

fundecs: fundec fundecs {$$ = MakeFunctionDec(@$, MakeFunDecList($1, dynamic_pointer_cast<FunctionDec>($2)->getFunction()));}
	   | fundec {$$ = MakeFunctionDec(@$, MakeFunDecList($1, nullptr));}

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp {string v = "void"; $$ = MakeFunDec(@$, $2, v, $4, $7);}
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp {$$ = MakeFunDec(@$, $2, $7, $4, $9);}

explist: exp SEMICOLON explist {$$ = MakeExpList($1, $3);}
	   | exp {$$ = MakeExpList($1, nullptr);}
	   | {$$ = nullptr;}

lvalue: id {$$ = MakeSimpleVar(@$, $1);}	
      | lvalue DOT id {$$ = MakeFieldVar(@$, $1, $3);}
	  | id LBRACK exp RBRACK {$$ = MakeSubscriptVar(@$, MakeSimpleVar(@$, $1), $3);}
	  | lvalue LBRACK exp RBRACK {$$ = MakeSubscriptVar(@$, $1, $3);}

funcall: id LPAREN args RPAREN {$$ = MakeCallExp(@$, $1, $3);}

args: exp COMMA args {$$ = MakeExpList($1, $3);}
    | exp {$$ = MakeExpList($1, nullptr);}
	| {$$ = nullptr;}

id: ID {$$ =$1;}

%%
void Tiger::Parser::error (const location_type & l, const string & m)
{
    driver.error(l, m);
}