%{
#include <string.h>
#include <stdio.h>
#include "gramatica.tab.h"
%}
ws [ \t]
%%
{ws} { }
"o" { printf("yytext: %s\n", yytext);
strcpy( yylval.str,yytext);
return O;}
"a" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return A; }
"gato" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return GATO; }
"cachorro" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return CACHORRO; }
"comida" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return COMIDA; }
"biscoito" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return BISCOITO; }
"é" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return E; }
"come" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return COME; }
"bonito" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return BONITO; }
"feio" { printf("yytext: %s\n", yytext);
strcpy(yylval.str,yytext);
return FEIO; }
\n { return 0; }
[ \t] { /* ignora espaços e tabs */ }
. { 
    printf("Token inválido: '%s'\n", yytext);
    return yytext[0]; /* retorna o caractere inválido */
}
%%

int yywrap(void) {
    return 1;
}