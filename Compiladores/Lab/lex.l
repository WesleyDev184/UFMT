%{
#include <stdio.h>

FILE *output;
%}

digit       [0-9]
id          [a-zA-Z_][a-zA-Z0-9_]*
string      \"([^\\\"]|\\.)*\"
char        \'([^\\\']|\\.)\'
float       {digit}+"."{digit}+

%%

"int"           { fprintf(output, "<TYPE: int>\n"); }
"string"        { fprintf(output, "<TYPE: string>\n"); }
"void"          { fprintf(output, "<TYPE: void>\n"); }
"float"         { fprintf(output, "<TYPE: float>\n"); }
"char"          { fprintf(output, "<TYPE: char>\n"); }

"begin"         { fprintf(output, "<BEGIN>\n"); }
"end"           { fprintf(output, "<END>\n"); }
"read"          { fprintf(output, "<READ>\n"); }
"write"         { fprintf(output, "<WRITE>\n"); }
"while"         { fprintf(output, "<WHILE>\n"); }

{string}        { fprintf(output, "<STRING: %s>\n", yytext); }
{char}          { fprintf(output, "<CHAR: %s>\n", yytext); }
{float}         { fprintf(output, "<FLOAT: %s>\n", yytext); }
{digit}+        { fprintf(output, "<INT: %s>\n", yytext); }

"=="            { fprintf(output, "<EQ>\n"); }
"!="            { fprintf(output, "<NEQ>\n"); }
"<="            { fprintf(output, "<LE>\n"); }
">="            { fprintf(output, "<GE>\n"); }
"<"             { fprintf(output, "<LT>\n"); }
">"             { fprintf(output, "<GT>\n"); }
"="             { fprintf(output, "<ASSIGN>\n"); }
"+"             { fprintf(output, "<PLUS>\n"); }
"-"             { fprintf(output, "<MINUS>\n"); }
"*"             { fprintf(output, "<MUL>\n"); }
"/"             { fprintf(output, "<DIV>\n"); }

"("             { fprintf(output, "<LPAREN>\n"); }
")"             { fprintf(output, "<RPAREN>\n"); }
";"             { fprintf(output, "<SEMICOLON>\n"); }
","             { fprintf(output, "<COMMA>\n"); }
./
{id}            { fprintf(output, "<ID: %s>\n", yytext); }

[ \t\r\n]+      ;

.               { fprintf(output, "<UNKNOWN: %s>\n", yytext); }

%%

int main() {
    output = fopen("tokens.txt", "w");
    if (!output) {
        perror("Erro ao abrir arquivo de saída");
        return 1;
    }

    yylex();

    fclose(output);
    return 0;
}
