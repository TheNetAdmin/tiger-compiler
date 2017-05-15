/* 27.11.14 by Mkth
 * Lexical engine
 * input is file of tig
 * output is TOKEN
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "errormsg.h"
#include "tokens.h"

YYSTYPE yylval; /* the yylval ... record current token some info */

int yylex(void); /* prototype for the lexing function */

string toknames[] = {
	"ID", "STRING", "INT", "COMMA", "COLON", "SEMICOLON", "LPAREN",
	"RPAREN", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "DOT", "PLUS",
	"MINUS", "TIMES", "DIVIDE", "EQ", "NEQ", "LT", "LE", "GT", "GE",
	"AND", "OR", "ASSIGN", "ARRAY", "IF", "THEN", "ELSE", "WHILE", "FOR",
	"TO", "DO", "LET", "IN", "END", "OF", "BREAK", "NIL", "FUNCTION",
	"VAR", "TYPE"
};

/* get token-name */
string tokname(tok) {return tok < 257 || tok > 299 ? "BAD_TOKEN" : toknames[tok-257];}

int main(int argc, char **argv) {
	string fname; int tok;
	if (argc!=2) {
		fprintf(stderr,"usage: a.out filename\n"); 
		exit(1);
	}
	fname=argv[1];
	EM_reset(fname);
	for(;;) {
		tok=yylex();
		if (tok==0) break;
		
		if(strcmp("BAD_TOKEN", tokname(tok)) == 0) assert("Invalid Token");
		 
		// here is unit-test i'm lazy --
		if(strcmp("WHILE", tokname(tok)) != 0) assert("Program failed");
		
		switch (tok) {
		case ID: case STRING:
			printf("%10s %4d %s\n",tokname(tok),EM_tokPos,yylval.sval);
			break;
		case INT:
			printf("%10s %4d %d\n",tokname(tok),EM_tokPos,yylval.ival);
			break;
		default:
			printf("%10s %4d\n",tokname(tok),EM_tokPos);
		}
	}
	return 0;
}

