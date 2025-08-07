%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

int result;
%}

%union {
    int num;
    char* str;
}

%token <num> NUM
%token PLUS MINUS MULT DIV LPAREN RPAREN

%type <num> expr term factor

%left PLUS MINUS
%left MULT DIV
%right UMINUS

%%

input:
    /* vazio */
    | input line
    ;

line:
    expr '\n'       { 
                        result = $1; 
                        printf("Resultado: %d\n", result); 
                    }
    | expr          { 
                        result = $1; 
                        printf("Resultado: %d\n", result); 
                    }
    | '\n'          { /* linha vazia */ }
    ;

expr:
    expr PLUS term  { $$ = $1 + $3; }
    | expr MINUS term { $$ = $1 - $3; }
    | term          { $$ = $1; }
    ;

term:
    term MULT factor { $$ = $1 * $3; }
    | term DIV factor { 
                        if ($3 == 0) {
                            yyerror("Divisão por zero!");
                            YYABORT;
                        }
                        $$ = $1 / $3; 
                      }
    | factor        { $$ = $1; }
    ;

factor:
    NUM             { $$ = $1; }
    | LPAREN expr RPAREN { $$ = $2; }
    | MINUS factor %prec UMINUS { $$ = -$2; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Erro: %s\n", s);
}