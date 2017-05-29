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
    int EM_tokPos = 0;
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

program:  exp {absyn_root = $1;}

exp: lvalue {$$ = MakeVarExpAST(EM_tokPos, $1);}
   | funcall {$$ = $1;}
   | lvalue ASSIGN exp {$$ = MakeAssignExpAST(EM_tokPos, $1, $3);} 
   | NIL {$$ = MakeNilExpAST(EM_tokPos);}
   | seq {$$ = $1;}
   | INT {$$ = MakeIntExpAST(EM_tokPos, $1);}
   | STRING {$$ = MakeStringExpAST(EM_tokPos, $1);}
   | LET decs IN explist END {$$ = MakeLetExpAST(EM_tokPos, $2, MakeSeqExpAST(EM_tokPos, $4));}
   | IF exp THEN exp ELSE exp {$$ = MakeIfExpAST(EM_tokPos, $2, $4, $6);}
   | IF exp THEN exp {$$ = MakeIfExpAST(EM_tokPos, $2, $4, nullptr);}
   | exp PLUS exp {$$ = MakeOpExpAST(EM_tokPos, PLUSOP, $1, $3);} 
   | exp MINUS exp {$$ = MakeOpExpAST(EM_tokPos, MINUSOP, $1, $3);} 
   | exp TIMES exp {$$ = MakeOpExpAST(EM_tokPos, TIMESOP, $1, $3);}
   | exp DIVIDE exp {$$ = MakeOpExpAST(EM_tokPos, DIVIDEOP, $1, $3);}
   | exp EQ exp {$$ = MakeOpExpAST(EM_tokPos, EQOP, $1, $3);}
   | MINUS exp %prec UMINUS {$$ = MakeOpExpAST(EM_tokPos, MINUSOP, MakeIntExpAST(EM_tokPos, 0), $2);}
   | exp NEQ exp {$$ = MakeOpExpAST(EM_tokPos, NEQOP, $1, $3);}
   | exp GT exp {$$ = MakeOpExpAST(EM_tokPos, GTOP, $1, $3);}
   | exp LT exp {$$ = MakeOpExpAST(EM_tokPos, LTOP, $1, $3);}
   | exp GE exp {$$ = MakeOpExpAST(EM_tokPos, GEOP, $1, $3);}
   | exp LE exp {$$ = MakeOpExpAST(EM_tokPos, LEOP, $1, $3);}
   | exp AND exp {$$ = MakeIfExpAST(EM_tokPos, $1, $3, MakeIntExpAST(EM_tokPos, 0));}
   | exp OR exp {$$ = MakeIfExpAST(EM_tokPos, $1, MakeIntExpAST(EM_tokPos,1), $3);}
   | record {$$ = $1;}
   | array {$$ = $1;}
   | WHILE exp DO exp {$$ = MakeWhileExpAST(EM_tokPos, $2, $4);} 
   | FOR id ASSIGN exp TO exp DO exp {$$ = MakeForExpAST(EM_tokPos, $2, $4, $6, $8);}
   | BREAK {$$ = MakeBreakExpAST(EM_tokPos);} 

seq: LPAREN explist RPAREN {$$ = MakeSeqExpAST(EM_tokPos, $2);} 

record: id LBRACE refields RBRACE {$$ = MakeRecordExpAST(EM_tokPos, $1, $3);}

refields: id EQ exp COMMA refields {$$ = MakeEFieldListAST(MakeEFieldAST($1, $3), $5);}
        | id EQ exp {$$ = MakeEFieldListAST(MakeEFieldAST($1, $3), nullptr);}
        | {$$ = nullptr;}

array: id LBRACK exp RBRACK OF exp {$$ = MakeArrayExpAST(EM_tokPos, $1, $3, $6);} 


decs: dec decs {$$ = MakeDecListAST($1, $2);}
    | {$$ = nullptr;} 

dec: tydecs {$$ = $1;}
   | vardec {$$ = $1;}
   | fundecs {$$ = $1;}

tydecs: tydec tydecs {$$ = MakeTypeDecAST(EM_tokPos, MakeTypeTyListAST($1, dynamic_pointer_cast<TypeDecAST>($2)->getType()));}
      | tydec {$$ = MakeTypeDecAST(EM_tokPos, MakeTypeTyListAST($1, nullptr));}
   
tydec: TYPE id EQ ty {$$ = MakeTypeTyAST($2, $4);}

ty:	id {$$ = MakeNameTyAST(EM_tokPos, $1);} 
  | LBRACE typefields RBRACE {$$ = MakeRecordTyAST(EM_tokPos, $2);}
  | ARRAY OF id {$$ = MakeArrayTyAST(EM_tokPos, $3);}

typefields: id COLON id COMMA typefields {$$ = MakeFieldListAST(MakeFieldAST(EM_tokPos, $1, $3), $5);}
          | id COLON id {$$ = MakeFieldListAST(MakeFieldAST(EM_tokPos, $1, $3), nullptr);}
		  | {$$ = nullptr;}

vardec: VAR id ASSIGN exp {string s = "DEBUG"; $$ = MakeVarDecAST(EM_tokPos, $2, s, $4);} 
      | VAR id COLON id ASSIGN exp {$$ = MakeVarDecAST(EM_tokPos, $2, $4, $6);}

fundecs: fundec fundecs {$$ = MakeFunctionDecAST(EM_tokPos, MakeFunDecListAST($1, dynamic_pointer_cast<FunctionDecAST>($2)->getFunction()));}
	   | fundec {$$ = MakeFunctionDecAST(EM_tokPos, MakeFunDecListAST($1, nullptr));}

fundec: FUNCTION id LPAREN typefields RPAREN EQ exp {string v = "void"; $$ = MakeFunDecAST(EM_tokPos, $2, v, $4, $7);}
      | FUNCTION id LPAREN typefields RPAREN COLON id EQ exp {$$ = MakeFunDecAST(EM_tokPos, $2, $7, $4, $9);}

explist: exp SEMICOLON explist {$$ = MakeExpListAST($1, $3);}
	   | exp {$$ = MakeExpListAST($1, nullptr);}
	   | {$$ = nullptr;}

lvalue: id {$$ = MakeSimpleVarAST(EM_tokPos, $1);}	
      | lvalue DOT id {$$ = MakeFieldVarAST(EM_tokPos, $1, $3);}
	  | id LBRACK exp RBRACK {$$ = MakeSubscriptVarAST(EM_tokPos, MakeSimpleVarAST(EM_tokPos, $1), $3);}
	  | lvalue LBRACK exp RBRACK {$$ = MakeSubscriptVarAST(EM_tokPos, $1, $3);}

funcall: id LPAREN args RPAREN {$$ = MakeCallExpAST(EM_tokPos, $1, $3);} 

args: exp COMMA args {$$ = MakeExpListAST($1, $3);}
    | exp {$$ = MakeExpListAST($1, nullptr);}
	| {$$ = nullptr;}

id: ID {$$ =$1;}

%%
void Tiger::Parser::error (const location_type & l, const string & m)
{
    driver.error(l, m);
}