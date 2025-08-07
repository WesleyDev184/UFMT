%{
#include <string.h>
#include <stdio.h>
void yyerror(char *);
int main(void);
extern int yylex();
extern char* yytext;
%}

%union {
char str[256];
};
%type <str> oracao sujeito predicado art subst verbo complemento
%token <str> O A GATO CACHORRO COMIDA BISCOITO E COME BONITO FEIO

%start oracao

%%

oracao : sujeito predicado {
strcpy($$,$1);
strcat($$," ");
strcat($$, $2);
printf("Oração reconhecida: %s\n", $$); }
| error {
yyerror("Oração não está correta! Use o padrão: [artigo] [substantivo] [verbo] [complemento]");
yyerrok;
}
;

sujeito : art subst {
strcpy($$,$1);
strcat($$," ");
strcat ($$, $2);
printf("Sujeito: %s\n", $$); }
| error subst {
yyerror("Artigo inválido no sujeito! Use 'o' ou 'a'");
yyerrok;
}
| art error {
yyerror("Substantivo inválido no sujeito! Use 'gato', 'cachorro', 'comida' ou 'biscoito'");
yyerrok;
}
;

predicado : verbo complemento {
strcpy($$,$1);
strcat($$," ");
strcat($$, $2);
printf("Predicado: %s\n", $$); }
| error complemento {
yyerror("Verbo inválido no predicado! Use 'é' ou 'come'");
yyerrok;
}
| verbo error {
yyerror("Complemento inválido no predicado! Use 'bonito', 'feio' ou um substantivo");
yyerrok;
}
;

art : O {
strcpy($$,$1);
printf("Artigo: %s\n",$$); }
| A {
strcpy($$,$1);
printf("Artigo: %s\n",$$); }
;

subst : GATO {
strcpy($$,$1);
printf("Substantivo: %s\n",$$); }
| CACHORRO {
strcpy($$,$1);
printf("Substantivo: %s\n",$$); }
| COMIDA {
strcpy($$,$1);
printf("Substantivo: %s\n",$$); }
| BISCOITO {
strcpy($$,$1);
printf("Substantivo: %s\n",$$); }
;

verbo : E {
strcpy($$,$1);
printf("Verbo: %s\n",$$); }
| COME {
strcpy($$,$1);
printf("Verbo: %s\n",$$); }
;

complemento : BONITO {
strcpy($$,$1);
printf("Complemento: %s\n",$$); }
| FEIO {
strcpy($$,$1);
printf("Complemento: %s\n",$$); }
| subst {
strcpy($$,$1);
printf("Complemento: %s\n",$$); }
;

%%

void yyerror(char *s) {
printf("ERRO: %s\n", s);
printf("Exemplo de oração correta: 'o gato é bonito' ou 'a comida é feio'\n");
printf("Padrão: [artigo] [substantivo] [verbo] [complemento]\n");
printf("- Artigos: o, a\n");
printf("- Substantivos: gato, cachorro, comida, biscoito\n");
printf("- Verbos: é, come\n");
printf("- Complementos: bonito, feio, ou substantivo\n");
}

int main(void) {
printf("=== ANALISADOR DE ORAÇÕES ===\n");
printf("Digite uma oração (exemplo: o gato é bonito):\n");
printf("Para sair, digite Ctrl+C\n\n");
if (yyparse() == 0) {
    printf("\nAnálise concluída com sucesso!\n");
} else {
    printf("\nAnálise falhou - oração incorreta!\n");
}
return 0;
}