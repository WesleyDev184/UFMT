#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"

extern int yyparse();
extern FILE *yyin;
extern int result;

int main(int argc, char *argv[])
{
    FILE *input_file = NULL;

    printf("=== Compilador de Expressões Aritméticas ===\n");
    printf("Gramática suportada:\n");
    printf("E --> E + T | E - T | T\n");
    printf("T --> T * F | T / F | F\n");
    printf("F --> ( E ) | NUM\n");
    printf("NUM --> 0 | 1 | 2 | ... | 9\n\n");

    if (argc > 1)
    {
        // Lê de arquivo
        input_file = fopen(argv[1], "r");
        if (!input_file)
        {
            fprintf(stderr, "Erro: Não foi possível abrir o arquivo %s\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Lendo expressões do arquivo: %s\n", argv[1]);
    }
    else
    {
        // Lê da entrada padrão
        printf("Digite expressões aritméticas (Ctrl+D para sair):\n");
        yyin = stdin;
    }

    // Inicia o parsing
    if (yyparse() == 0)
    {
        printf("\nParsing concluído com sucesso!\n");
    }
    else
    {
        printf("\nErro durante o parsing.\n");
    }

    if (input_file)
    {
        fclose(input_file);
    }

    return 0;
}