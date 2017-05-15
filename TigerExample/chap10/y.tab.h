/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     INT = 260,
     DOUBLE = 261,
     ASSIGN = 262,
     OR = 263,
     AND = 264,
     GE = 265,
     GT = 266,
     LE = 267,
     LT = 268,
     NEQ = 269,
     EQ = 270,
     MINUS = 271,
     PLUS = 272,
     DIVIDE = 273,
     TIMES = 274,
     UMINUS = 275,
     COMMA = 276,
     COLON = 277,
     SEMICOLON = 278,
     LPAREN = 279,
     RPAREN = 280,
     LBRACK = 281,
     RBRACK = 282,
     LBRACE = 283,
     RBRACE = 284,
     DOT = 285,
     ARRAY = 286,
     IF = 287,
     THEN = 288,
     ELSE = 289,
     WHILE = 290,
     FOR = 291,
     TO = 292,
     DO = 293,
     LET = 294,
     IN = 295,
     END = 296,
     OF = 297,
     BREAK = 298,
     NIL = 299,
     FUNCTION = 300,
     VAR = 301,
     TYPE = 302
   };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INT 260
#define DOUBLE 261
#define ASSIGN 262
#define OR 263
#define AND 264
#define GE 265
#define GT 266
#define LE 267
#define LT 268
#define NEQ 269
#define EQ 270
#define MINUS 271
#define PLUS 272
#define DIVIDE 273
#define TIMES 274
#define UMINUS 275
#define COMMA 276
#define COLON 277
#define SEMICOLON 278
#define LPAREN 279
#define RPAREN 280
#define LBRACK 281
#define RBRACK 282
#define LBRACE 283
#define RBRACE 284
#define DOT 285
#define ARRAY 286
#define IF 287
#define THEN 288
#define ELSE 289
#define WHILE 290
#define FOR 291
#define TO 292
#define DO 293
#define LET 294
#define IN 295
#define END 296
#define OF 297
#define BREAK 298
#define NIL 299
#define FUNCTION 300
#define VAR 301
#define TYPE 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 21 "tiger.y"

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



/* Line 2068 of yacc.c  */
#line 165 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


