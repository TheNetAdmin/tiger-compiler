%{
    int wordCount = 0;
    int lineCount = 0;
%}
character [A-Za-z0-9]
word {character}+
separator [" "\t,\.]
whitespace {separator}+
linebreak [\n]
%%

{word} { wordCount++; }
{whitespace} { ; }
{linebreak} { lineCount++; }
%%

void main() {
    yylex();
    printf("Total words: %d\n", wordCount);
    printf("Total lines: %d\n", lineCount);
}

int yywrap() {
    return 1;
}
