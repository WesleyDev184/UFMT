%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void yyerror(const char *s);
#include "tab_simb.tab.h"   
%}

/* Regras de tokens */
%%
[ \t\r]+                ;                       
\n                      return '\n';           

[0-9]+                  { yylval.num = atoi(yytext); return INTEGER; }


[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return VARIABLE; }

[-+()=/*]               { return yytext[0]; }

.                       { yyerror("invalid character"); }
%%
