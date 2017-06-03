%option noyywrap nounput batch debug noinput
%option nounistd never-interactive
%{
    #include <string>
    #include "driver.h"
    #include "parser.h"
    #include "location.hh"
    using namespace std;


    #undef yywrap
    #define yywrap() 1
    #define YY_NUMMPTR nullptr

    static int comment_level = 0;
    string current_string;
    Tiger::location loc;
%}

%x IN_COMMENT
%x IN_STRING
id [A-Za-z][_A-Za-z0-9]*
digits [0-9]+
white_space [ \t\r]+
 
%{
    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
    // loc.step();
%}

{white_space}	{loc.step(); continue;}
\n	            {loc.step(); loc.lines(yyleng); continue;}
","	            {return Tiger::Parser::make_COMMA(loc);}
":="            {return Tiger::Parser::make_ASSIGN(loc);}
":"             {return Tiger::Parser::make_COLON(loc);}
";"             {return Tiger::Parser::make_SEMICOLON(loc);}
"("             {return Tiger::Parser::make_LPAREN(loc);}
")"	            {return Tiger::Parser::make_RPAREN(loc);}
"{"             {return Tiger::Parser::make_LBRACE(loc);}
"}"             {return Tiger::Parser::make_RBRACE(loc);}
"["             {return Tiger::Parser::make_LBRACK(loc);}
"]"             {return Tiger::Parser::make_RBRACK(loc);}
"."	            {return Tiger::Parser::make_DOT(loc);}
"+"             {return Tiger::Parser::make_PLUS(loc);}
"-"		        {return Tiger::Parser::make_MINUS(loc);}
"*"	            {return Tiger::Parser::make_TIMES(loc);}
"/"	            {return Tiger::Parser::make_DIVIDE(loc);}
"="	            {return Tiger::Parser::make_EQ(loc);}
"<>"	        {return Tiger::Parser::make_NEQ(loc);}
"<="            {return Tiger::Parser::make_LE(loc);}
"<"             {return Tiger::Parser::make_LT(loc);}
">="	        {return Tiger::Parser::make_GE(loc);}
">"	            {return Tiger::Parser::make_GT(loc);}
"&"             {return Tiger::Parser::make_AND(loc);}
"|"             {return Tiger::Parser::make_OR(loc);}
array           {return Tiger::Parser::make_ARRAY(loc);}
break           {return Tiger::Parser::make_BREAK(loc);}
do		        {return Tiger::Parser::make_DO(loc);}
end             {return Tiger::Parser::make_END(loc);}
else            {return Tiger::Parser::make_ELSE(loc);}
function        {return Tiger::Parser::make_FUNCTION(loc);}
for             {return Tiger::Parser::make_FOR(loc);}
if		        {return Tiger::Parser::make_IF(loc);}
in	            {return Tiger::Parser::make_IN(loc);}
let             {return Tiger::Parser::make_LET(loc);}
of              {return Tiger::Parser::make_OF(loc);}
nil             {return Tiger::Parser::make_NIL(loc);}
then            {return Tiger::Parser::make_THEN(loc);}
to		        {return Tiger::Parser::make_TO(loc);}
type	        {return Tiger::Parser::make_TYPE(loc);}
var		        {return Tiger::Parser::make_VAR(loc);}
while           {return Tiger::Parser::make_WHILE(loc);}
{id}	        {return Tiger::Parser::make_ID(yytext, loc);}	
{digits}        {long n = strtol(yytext, NULL, 10); return Tiger::Parser::make_INT(n, loc);}

"/*"                        {comment_level++; BEGIN IN_COMMENT;}
<IN_COMMENT>"/*"            {comment_level++; BEGIN IN_COMMENT;}
<IN_COMMENT>"*/"            {comment_level--; if (!comment_level) BEGIN (0);}
<IN_COMMENT>\n			    {loc.lines(yyleng);}	
<IN_COMMENT>(.)             {continue;}

\"                          {BEGIN IN_STRING;}
<IN_STRING>\\				{current_string += 0x5c;}
<IN_STRING>"\\\""			{current_string += 0x22;}
<IN_STRING>\\n				{current_string += 0x0A;}
<IN_STRING>\\t				{current_string += 0x09;}
<IN_STRING>\\[0-9]{3}		{current_string += atoi(yytext);}
<IN_STRING>\"				{BEGIN (0); return Tiger::Parser::make_STRING(current_string, loc);}
<IN_STRING>\n				{loc.lines(yyleng);}
<IN_STRING>{white_space}	{current_string += yytext;}	
<IN_STRING>[^\\" \t\n]+     {current_string += yytext;}

.	                        {driver.error(loc, "Illegal Token!");}
<<EOF>>                     return Tiger::Parser::make_ENDFILE(loc);
%%
