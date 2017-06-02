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
    #include "driver.h"
    shared_ptr<ExpAST> absyn_root;
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

%type <shared_ptr<ExpAST>> exp program funcall seq record array
%type <shared_ptr<VarAST>> lvalue
%type <shared_ptr<DecListAST>> decs
%type <shared_ptr<DecAST>> dec tydecs fundecs vardec
%type <shared_ptr<FunDecAST>> fundec
%type <shared_ptr<TypeTyAST>> tydec
%type <shared_ptr<ExpListAST>> explist args
%type <string> id
%type <shared_ptr<EFieldListAST>> refields
%type <shared_ptr<TyAST>> ty
%type <shared_ptr<FieldListAST>> typefields
/* et cetera */

%start program

%%

program:  exp {absyn_root = $1; driver.result = absyn_root;}

exp: lvalue {$$ = MakeVarExpAST(@$, $1);}
   | funcall {$$ = $1;}
   | lvalue ASSIGN exp {$$ = MakeAssignExpAST(@$, $1, $3);} 
   | NIL {$$ = MakeNilExpAST(@$);}
   | seq {$$ = $1;}
   | INT {$$ = MakeIntExpAST(@$, $1);}
   | STRING {$$ = MakeStringExpAST(@$, $1);}
   | LET decs IN explist END {$$ = MakeLetExpAST(@$, $2, MakeSeqExpAST(@$, $4));}
   | IF exp THEN exp ELSE exp {$$ = MakeIfExpAST(@$, $2, $4, $6);}
   | IF exp THEN exp {$$ = MakeIfExpAST(@$, $2, $4, nullptr);}
   | exp PLUS exp {$$ = MakeOpExpAST(@$, PLUSOP, $1, $3);} 
   | exp MINUS exp {$$ = MakeOpExpAST(@$, MINUSOP, $1, $3);} 
   | exp TIMES exp {$$ = MakeOpExpAST(@$, TIMESOP, $1, $3);}
   | exp DIVIDE exp {$$ = MakeOpExpAST(@$, DIVIDEOP, $1, $3);}
   | exp EQ exp {$$ = MakeOpExpAST(@$, EQOP, $1, $3);}
   | MINUS exp %prec UMINUS {$$ = MakeOpExpAST(@$, MINUSOP, MakeIntExpAST(@$, 0), $2);}
   | exp NEQ exp {$$ = MakeOpExpAST(@$, NEQOP, $1, $3);}
   | exp GT exp {$$ = MakeOpExpAST(@$, GTOP, $1, $3);}
   | exp LT exp {$$ = MakeOpExpAST(@$, LTOP, $1, $3);}
   | exp GE exp {$$ = MakeOpExpAST(@$, GEOP, $1, $3);}
   | exp LE exp {$$ = MakeOpExpAST(@$, LEOP, $1, $3);}
   | exp AND exp {$$ = MakeIfExpAST(@$, $1, $3, MakeIntExpAST(@$, 0));}
   | exp OR exp {$$ = MakeIfExpAST(@$, $1, MakeIntExpAST(@$,1), $3);}
   | record {$$ = $1;}
   | array {$$ = $1;}
   | WHILE exp DO exp {$$ = MakeWhileExpAST(@$, $2, $4);} 
   | FOR id ASSIGN exp TO exp DO exp {$$ = MakeForExpAST(@$, $2, $4, $6, $8);}
   | BREAK {$$ = MakeBreakExpAST(@$);} 

seq: LPAREN explist RPAREN {$$ = MakeSeqExpAST(@$, $2);} 

record: id LBRACE refields RBRACE {$$ = MakeRecordExpAST(@$, $1, $3);}

refields: id EQ exp COMMA refields {$$ = MakeEFieldListAST(MakeEFieldAST($1, $3), $5);}
        | id EQ exp {$$ = MakeEFieldListAST(MakeEFieldAST($1, $3), nullptr);}
        | {$$ = nullptr;}

array: id LBRACK exp RBRACK OF exp {$$ = MakeArrayExpAST(@$, $1, $3, $6);} 


decs: dec decs {$$ = MakeDecListAST($1, $2);}
    | {$$ = nullptr;} 

dec: tydecs {$$ = $1;}
   | vardec {$$ = $1;}
   | fundecs {$$ = $1;}

tydecs: tydec tydecs {$$ = MakeTypeDecAST(@$, MakeTypeTyListAST($1, dynamic_pointer_cast<TypeDecAST>($2)->getType()));}
      | tydec {$$ = MakeTypeDecAST(@$, MakeTypeTyListAST($1, nullptr));}
   
tydec: TYPE id EQ ty {$$ = MakeTypeTyAST($2, $4);}

ty:	id {$$ = MakeNameTyAST(@$, $1);} 
  | LBRACE typefields RBRACE {$$ = MakeRecordTyAST(@$, $2);}
  | ARRAY OF id {$$ = MakeArrayTyAST(@$, $3);}

typefields: id COLON id COMMA typefields {$$ = MakeFieldListAST(MakeFieldAST(@$, $1, $3), $5);}
          | id COLON id {$$ = MakeFieldListAST(MakeFieldAST(@$, $1, $3), nullptr);}
		  | {$$ = nullptr;}

vardec: VAR id ASSIGN exp {string s = "DEBUG"; $$ = MakeVarDecAST(@$, $2, s, $4);} 
      | VAR id COLON id ASSIGN exp {$$ = MakeVarDecAST(@$, $2, $4, $6);}

fundecs: fundec fundecs {$$ = MakeFunctionDecAST(@$, MakeFunDecListAST($1, dynamic_pointer_cast<FunctionDecAST>($2)->getFunction()));}
	   | fundec {$$ = MakeFunctionDecAST(@$, MakeFunDecListAST($1, nullptr));}

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp {string v = "void"; $$ = MakeFunDecAST(@$, $2, v, $4, $7);}
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp {$$ = MakeFunDecAST(@$, $2, $7, $4, $9);}

explist: exp SEMICOLON explist {$$ = MakeExpListAST($1, $3);}
	   | exp {$$ = MakeExpListAST($1, nullptr);}
	   | {$$ = nullptr;}

lvalue: id {$$ = MakeSimpleVarAST(@$, $1);}	
      | lvalue DOT id {$$ = MakeFieldVarAST(@$, $1, $3);}
	  | id LBRACK exp RBRACK {$$ = MakeSubscriptVarAST(@$, MakeSimpleVarAST(@$, $1), $3);}
	  | lvalue LBRACK exp RBRACK {$$ = MakeSubscriptVarAST(@$, $1, $3);}

funcall: id LPAREN args RPAREN {$$ = MakeCallExpAST(@$, $1, $3);} 

args: exp COMMA args {$$ = MakeExpListAST($1, $3);}
    | exp {$$ = MakeExpListAST($1, nullptr);}
	| {$$ = nullptr;}

id: ID {$$ =$1;}

%%
void Tiger::Parser::error (const location_type & l, const string & m)
{
    driver.error(l, m);
}