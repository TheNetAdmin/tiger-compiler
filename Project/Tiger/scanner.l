%option debug
%option nodefault
%option yyclass="Tiger::Scanner"
%option c++
%{
#include <string>
#include "error.h"
using namespace std;

ParserError PE;

int yywrap(void)
{
    return 1;
}

void adjust(void)
{
    PE.adjustTokenPos(yyleng);
}

static int comment_level = 0;
string current_string;

}

%}

%x IN_COMMENT
%x IN_STRING
id [A-Za-z][_A-Za-z0-9]*
digits [0-9]+
white_space [ \t]+
 
%%
{white_space}	{adjust(); continue;}
\n	            {adjust(); PE.newline(); continue;}
","	            {adjust(); return COMMA;}
":="            {adjust(); return ASSIGN;}
":"             {adjust(); return COLON;}
";"             {adjust(); return SEMICOLON;}
"("             {adjust(); return LPAREN;}
")"	            {adjust(); return RPAREN;}
"{"             {adjust(); return LBRACE;}
"}"             {adjust(); return RBRACE;}
"["             {adjust(); return LBRACK;}
"]"             {adjust(); return RBRACK;}
"."	            {adjust(); return DOT;}
"+"             {adjust(); return PLUS;}
"-"		        {adjust(); return MINUS;}
"*"	            {adjust(); return TIMES;}
"/"	            {adjust(); return DIVIDE;}
"="	            {adjust(); return EQ;}
"<>"	        {adjust(); return NEQ;}
"<="            {adjust(); return LE;}
"<"             {adjust(); return LT;}
">="	        {adjust(); return GE;}
">"	            {adjust(); return GT;}
"&"             {adjust(); return AND;}
"|"             {adjust(); return OR;}
array           {adjust(); return ARRAY;}
break           {adjust(); return BREAK;}
do		        {adjust(); return DO;}
end             {adjust(); return END;}
else            {adjust(); return ELSE;}
function        {adjust(); return FUNCTION;}
for             {adjust(); return FOR;}
if		        {adjust(); return IF;}
in	            {adjust(); return IN;}
let             {adjust(); return LET;}
of              {adjust(); return OF;}
nil             {adjust(); return NIL;}
then            {adjust(); return THEN;}
to		        {adjust(); return TO;}
type	        {adjust(); return TYPE;}
var		        {adjust(); return VAR;}
while           {adjust(); return WHILE;}
{id}	        {adjust(); yylval.sval = yytext; return ID;}	
{digits}        {adjust(); yylval.ival=atoi(yytext); return INT;}

"/*"                        {adjust(); comment_level++; BEGIN IN_COMMENT;}
<IN_COMMENT>"/*"            {adjust(); comment_level++; BEGIN IN_COMMENT;}
<IN_COMMENT>"*/"            {adjust(); comment_level--; if (!comment_level) BEGIN (0);}
<IN_COMMENT>\n			    {adjust(); PE.newline();}	
<IN_COMMENT>(.)             {adjust(); continue;}

\"                          {adjust(); BEGIN IN_STRING;}
<IN_STRING>\\				{adjust(); current_string += 0x5c;}
<IN_STRING>"\\\""			{adjust(); current_string += 0x22;}
<IN_STRING>\\n				{adjust(); current_string += 0x0A;}
<IN_STRING>\\t				{adjust(); current_string += 0x09;}
<IN_STRING>\\[0-9]{3}		{adjust(); current_string += atoi(yytext);}
<IN_STRING>\"				{adjust(); yylval.sval = current_string; BEGIN (0); return STRING;}
<IN_STRING>\n				{adjust(); PE.newline();}
<IN_STRING>{white_space}	{adjust(); current_string += yytext;}	
<IN_STRING>[^\\" \t\n]+     {adjust(); current_string += yytext;}


.	                        {adjust(); PE.print({"Illegal token!"});}
%%
