%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);

typedef struct {
    int ival;
    float fval;
    char *sval;
} YYSTYPE;

#define YYSTYPE_IS_DECLARED 1

%}

%union {
    int ival;
    float fval;
    char *sval;
}

%token <ival> INTVAL
%token <fval> FLOATVAL
%token <sval> STRVAL IDENTIFIER

%token BEGIN_ END_
%token INT FLOAT CHAR STRING
%token WRITE READ WHILE
%token EQ NEQ LE GE LT GT ASSIGN PLUS MINUS MUL DIV
%token LPAREN RPAREN SEMICOLON COMMA
%token UNKNOWN

%type <ival> expression statement

%%

program:
    block
    ;

block:
    BEGIN_ statements END_
    ;

statements:
    /* vazio */
    | statements statement
    ;

statement:
    WRITE expression SEMICOLON
    {
        printf("WRITE: %d\n", $2);
    }
    | READ IDENTIFIER SEMICOLON
    {
        printf("READ: %s\n", $2);
    }
    | WHILE LPAREN expression RPAREN block
    {
        printf("WHILE\n");
    }
    | INT IDENTIFIER SEMICOLON
    {
        printf("Declare int: %s\n", $2);
    }
    ;

expression:
    INTVAL
    {
        $$ = $1;
    }
    | IDENTIFIER
    {
        $$ = 0; // Placeholder
    }
    | expression PLUS expression
    {
        $$ = $1 + $3;
    }
    | expression MINUS expression
    {
        $$ = $1 - $3;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erro: %s\n", s);
}

int main(void) {
    printf("Iniciando o parser...\n");
    return yyparse();
}
