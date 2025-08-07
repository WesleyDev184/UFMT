%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
%}

%option yylineno

%%

[ \t]+          { /* ignora espacos e tabs */ }
\n              { /* ignora quebras de linha */ }

[0-9]+          { 
                    yylval.num = atoi(yytext); 
                    return NUM; 
                }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MULT; }
"/"             { return DIV; }
"("             { return LPAREN; }
")"             { return RPAREN; }

.               { 
                    printf("Caractere nao reconhecido: %s\n", yytext); 
                    return yytext[0]; 
                }

%%

int yywrap() {
    return 1;
}