%option yyclass="Tiger::Scanner"
%option c++
%option noyywrap
%option nodefault
%option debug
%{
    #include <string>
    #include "error.h"
    #include "driver.h"
    #include ""
    using namespace std;

    #undef yywrap
    #define yywrap() 1

    using token = Tiger::Parser::token;
    static Tiger::location loc;
    static int comment_level = 0;
    string current_string;
}

%}

%x IN_COMMENT
%x IN_STRING
id [A-Za-z][_A-Za-z0-9]*
digits [0-9]+
white_space [ \t]+
 
%{
    #define YY_USER_ACTION loc.columns(yyleng)
%}

%%

%{
    loc.step();
%}

{white_space}	{continue;}
\n	            {PE.newline(); continue;}
","	            {return token::COMMA;}
":="            {return token::ASSIGN;}
":"             {return token::COLON;}
";"             {return token::SEMICOLON;}
"("             {return token::LPAREN;}
")"	            {return token::RPAREN;}
"{"             {return token::LBRACE;}
"}"             {return token::RBRACE;}
"["             {return token::LBRACK;}
"]"             {return token::RBRACK;}
"."	            {return token::DOT;}
"+"             {return token::PLUS;}
"-"		        {return token::MINUS;}
"*"	            {return token::TIMES;}
"/"	            {return token::DIVIDE;}
"="	            {return token::EQ;}
"<>"	        {return token::NEQ;}
"<="            {return token::LE;}
"<"             {return token::LT;}
">="	        {return token::GE;}
">"	            {return token::GT;}
"&"             {return token::AND;}
"|"             {return token::OR;}
array           {return token::ARRAY;}
break           {return token::BREAK;}
do		        {return token::DO;}
end             {return token::END;}
else            {return token::ELSE;}
function        {return token::FUNCTION;}
for             {return token::FOR;}
if		        {return token::IF;}
in	            {return token::IN;}
let             {return token::LET;}
of              {return token::OF;}
nil             {return token::NIL;}
then            {return token::THEN;}
to		        {return token::TO;}
type	        {return token::TYPE;}
var		        {return token::VAR;}
while           {return token::WHILE;}
{id}	        {yylval.build<std::string> = yytext; return token::ID;}	
{digits}        {yylval.build<int>() = text_to_int(yytext); return token::INT;}

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
<IN_STRING>\"				{yylval.sval = current_string; BEGIN (0); return token::STRING;}
<IN_STRING>\n				{loc.lines(yyleng);}
<IN_STRING>{white_space}	{current_string += yytext;}	
<IN_STRING>[^\\" \t\n]+     {current_string += yytext;}

.	                        {error(loc, "Illegal Token!")}
%%
