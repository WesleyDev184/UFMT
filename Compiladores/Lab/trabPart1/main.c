/*
 *
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"
#include "codeGeneration.h"
#include "errorHandler.h"
#include "parser.tab.h"

FILE *out_file = NULL;

SymTable table;

int cont_lines = 1;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("comp: no input file\n");
        return 1;
    }

    int n = strlen(argv[1]);
    if (n > 256)
    {
        fprintf(stderr, "[ERROR]: Input filename too long (max 256 characters)\n");
        return 1;
    }
    char s[n + 10];

    int i;
    for (i = 0; i < (n + 10); i++)
        s[i] = '\0';

    if (argc >= 4 && strcmp(argv[2], "-o") == 0)
        strcpy(s, argv[3]);

    else
    {
        for (i = n - 1; i >= 0 && argv[1][i] != '.'; i--)
        {
        }

        if (i == -1)
        {
            fprintf(stderr, "[ERROR]: Incorrect input file extension\n");
            return 0;
        }

        strncpy(s, argv[1], i);
        strcat(s, ".asm");
    }

    // Reset label counter for fresh compilation
    resetLabelCounter();

    // Initialize error handling system
    initErrorHandler();

    out_file = fopen(s, "w");
    if (out_file == NULL)
    {
        fprintf(stderr, "[ERROR]: Could not create output file %s\n", s);
        return 1;
    }

    // Generate assembly file preambule
    makePreambule(argv[1]);

    // Initialize symbol table and parse input
    if (!initSymTable(&table))
    {
        fprintf(stderr, "[ERROR]: Failed to initialize symbol table\n");
        fclose(out_file);
        remove(s);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "[ERROR]: Could not open input file %s\n", argv[1]);
        fclose(out_file);
        remove(s);
        return 1;
    }

    stdin = input_file;

    int ret = yyparse(); // call the syntactic analyzer
    if (ret == 1)
    {
        fclose(out_file);
        fclose(input_file);
        remove(s);
        return 1;
    }

    // Generate assembly file epilogue
    makeCodeEpilogue();

    fclose(out_file);
    fclose(input_file);

    // Print success message and symbol table
    printf("\n=== COMPILATION SUCCESSFUL ===\n");
    printf("Assembly code generated in: %s\n\n", s);

    // Show compilation statistics
    printErrorSummary();

    printf("=== SYMBOL TABLE ===\n");
    printSymTable(&table);

    // Free allocated memory
    freeSymTable(&table);
    freeErrorHandler();

    return 0;
}
