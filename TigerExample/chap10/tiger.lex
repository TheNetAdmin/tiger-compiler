/* C declarations */
%{
#include <string.h>
#include "util.h"
#include "symbol.h"
#include "absyn.h"
#include "y.tab.h"
#include "errormsg.h"

/*#define MAX_LENGTH 512*/

int charPos = 1;

/* when deal-finish open-file call this func (lex default def) (user can def cover lex's) */
int yywrap(void)
{
	charPos=1;
    return 1;
}

void adjust(void)
{
	EM_tokPos=charPos;
    charPos+=yyleng;
}

/* user */
static char * str_ptr;
static char str[MAX_LENGTH]; /* save string like "..." */
static char ch;              /* save trans-meaning char */
static int remain;
static int comment_nest = 0;

void init_string() {
	remain = MAX_LENGTH - 1;
	str_ptr = str;
}

#define	OVER_MEM_ERR printf("%s (max_length: %d)", "usage: string out of memrory!", MAX_LENGTH);\
					 exit(1)

void append_char_to_string(int ch) {
	if (!remain) {
		OVER_MEM_ERR;
	}
	*str_ptr++ = ch;
	remain--;
}

void append_str_to_string(char * s) {
	int t = strlen(s);
	if (remain < t) {
		OVER_MEM_ERR;
	}
	while((*str_ptr++ = *s++, *s));
	remain -= t;
}

void end_string() {
	if (!remain) {
		OVER_MEM_ERR;
	}
	*str_ptr++ = '\0';
}

%}

%x comment
%x string
%s nocomment
id [A-Za-z][_A-Za-z0-9]*
digits [0-9]+
double [0-9]+\.[0-9]+
ws [ \t]+
 
%%
{ws}	 {adjust(); continue;}
\n	     {adjust(); /*printf("fuck\n");*/ EM_newline(); continue;}
","	     {adjust(); return COMMA;}
":="     {adjust(); return ASSIGN;}
":"      {adjust(); return COLON;}
";"      {adjust(); return SEMICOLON;}
"("      {adjust(); return LPAREN;}
")"	     {adjust(); return RPAREN;}
"{"      {adjust(); return LBRACE;}
"}"      {adjust(); return RBRACE;}
"["      {adjust(); return LBRACK;}
"]"      {adjust(); return RBRACK;}
"."	     {adjust(); return DOT;}
"+"      {adjust(); return PLUS;}
"-"		 {adjust(); return MINUS;}
"*"	     {adjust(); return TIMES;}
"/"	     {adjust(); return DIVIDE;}
"="	     {adjust(); return EQ;}
"<>"	 {adjust(); return NEQ;}
"<="     {adjust(); return LE;}
"<"      {adjust(); return LT;}
">="	 {adjust(); return GE;}
">"	     {adjust(); return GT;}
"&"      {adjust(); return AND;}
"|"      {adjust(); return OR;}
array    {adjust(); return ARRAY;}
break    {adjust(); return BREAK;}
do		 {adjust(); return DO;}
end      {adjust(); return END;}
else     {adjust(); return ELSE;}
function {adjust(); return FUNCTION;}
for      {adjust(); return FOR;}
if		 {adjust(); return IF;}
in	     {adjust(); return IN;}
let      {adjust(); return LET;}
of       {adjust(); return OF;}
nil      {adjust(); return NIL;}
then     {adjust(); return THEN;}
to		 {adjust(); return TO;}
type	 {adjust(); return TYPE;}
var		 {adjust(); return VAR;}
while    {adjust(); return WHILE;}
{id}	 {adjust(); yylval.sval = yytext; return ID;}	
{digits} {adjust(); yylval.ival=atoi(yytext); return INT;}
{double} {adjust(); yylval.dval=atof(yytext); return DOUBLE;}
"/*"                 {adjust(); comment_nest++; BEGIN comment;}
<comment>"/*"        {adjust(); comment_nest++; BEGIN comment;}
<comment>"*/"        {adjust(); comment_nest--; if (!comment_nest) BEGIN nocomment;}
<comment>\n			 {adjust(); EM_newline();}	
<comment>(.)         {adjust(); continue;}

\"      {adjust(); init_string(); BEGIN string;}
<string>{
\\				{adjust(); append_char_to_string(0x5c);}
"\\\""			{adjust(); append_char_to_string(0x22);}
\\n				{adjust(); append_char_to_string(0x0A);}
\\t				{adjust(); append_char_to_string(0x09);}
		
\\[0-9]{3}		{adjust(); append_char_to_string(atoi(yytext));}
\"				{adjust(); end_string(); /*printf("%s fuck off", str);*/ yylval.sval = strdup(str); BEGIN (0); return STRING;}
\n				{adjust(); /*printf("fuck");*/}
{ws}	        {adjust(); append_str_to_string(yytext);}	
[^\\" \t\n]+    {adjust(); /*printf("fuck (.)* %s \n", yytext);*/ append_str_to_string(yytext);}
}

.	     {adjust(); EM_error(EM_tokPos,"illegal token");}
%%
