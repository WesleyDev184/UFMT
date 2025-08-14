%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    /* Tabela de símbolos*/
    typedef struct symrec {
        char *name;
        int value;
        struct symrec *next;
    } symrec;

    static symrec *sym_table = NULL;

    static symrec* putsym(const char *name) {
        symrec *s = (symrec*)malloc(sizeof(symrec));
        s->name = strdup(name);
        s->value = 0;
        s->next = sym_table;
        sym_table = s;
        return s;
    }

    static symrec* getsym(const char *name) {
        for (symrec *s = sym_table; s; s = s->next) {
            if (strcmp(s->name, name) == 0) return s;
        }
        return NULL;
    }

    void yyerror(const char *s);
    int yylex(void);
%}

/* Tipos do yylval */
%union {
    int   num;
    char *str;
}

/* Tokens */
%token <num> INTEGER
%token <str> VARIABLE

/* Precedência/associatividade */
%left '+' '-'
%left '*' '/'

/* Tipo das expressões */
%type <num> expr

%start input

%%

input
    : %empty
    | input line
    ;

line
    : '\n'
    | expr '\n'                       { printf("= %d\n", $1); }
    | VARIABLE '=' expr '\n'
        {
            symrec *s = getsym($1);
            if (!s) s = putsym($1);
            s->value = $3;
            printf("%s = %d\n", s->name, s->value);
            free($1);
        }
    ;

expr
    : INTEGER                          { $$ = $1; }
    | VARIABLE
        {
            symrec *s = getsym($1);
            if (!s) {
                fprintf(stderr, "variavel nao definida: %s\n", $1);
                $$ = 0;
            } else {
                $$ = s->value;
            }
            free($1);
        }
    | expr '+' expr                    { $$ = $1 + $3; }
    | expr '-' expr                    { $$ = $1 - $3; }
    | expr '*' expr                    { $$ = $1 * $3; }
    | expr '/' expr                    { $$ = ($3 != 0) ? ($1 / $3) : 0; }
    | '(' expr ')'                     { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "erro: %s\n", s);
}

int main(void) {
    return yyparse();
}
