%{
#define YYSTYPE double
#include <stdio.h>
#include <math.h>
#include <ctype.h>
%}
%token NUM
%left '-''+'
%left '*''/'
%left UMINUS
%right '^'

%%

input:
    |input line
    ;
line: '\n'
    |exp '\n' {printf("Result:%g\n", $1);}
    ;
exp: NUM {$$=$1;}
    |exp '+' exp {$$=$1+$3;}
    |exp '-' exp {$$=$1-$3;}
    |exp '*' exp {$$=$1*$3;}
    |exp '/' exp {$$=$1/$3;}
    |exp '^' exp {$$=pow($1,$3);}
    |'-' exp %prec UMINUS {$$=-$2;}
    |'('exp')'   {$$=$2;}
    ;

%%

int main()
{
    printf("Input the expressions:");
    yyparse();
}

int yyerror(char * msg)
{
    printf("Error: %s", msg);
}

int yylex()
{
    int c;
    while((c=getchar()) == ' ' || c == '\t');
    if(c == '.' || isdigit(c))
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUM;
    }
    if(c == EOF)
        return 0;
    return c;
}
