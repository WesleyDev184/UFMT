%token INTEGER VARIABLE 
%left '+' '-' 
%left '*' '/' 
%{
    #include <stdlib.h> 
    #include <stdio.h>
    void yyerror(char *); 
    int yylex(void); 
    int sym[26]; 
%}

%% 

program: 
        program statement '\n' 
        |  
        ; 
statement: 
        expr                      { printf("%d\n", $1); } 
        | VARIABLE '=' expr       { printf("Atribuicao: idx_var=%d <- %d\n", $1, $3); sym[$1] = $3; } 
        ; 
expr: 
        INTEGER                   { $$ = $1;      }
        | VARIABLE                { $$ = sym[$1]; } 
        | expr '+' expr           { $$ = $1 + $3; } 
        | expr '-' expr           { $$ = $1 - $3; } 
        | expr '*' expr           { $$ = $1 * $3; } 
        | expr '/' expr           { $$ = $1 / $3; } 
        | '(' expr ')'            { $$ = $2; } 
        ; 
%% 

void yyerror(char *s) { 
    printf("%s\n", s); 
    //return 0; 
} 

int main(void) { 
    yyparse(); 
    return 0; 
} 
