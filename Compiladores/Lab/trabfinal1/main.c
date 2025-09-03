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

    out_file = fopen(s, "w");
    fprintf(out_file, "extern printf\n");
    fprintf(out_file, "extern scanf\n");
    fprintf(out_file, "section .data\n");

    // this are strings without a line break character
    fprintf(out_file, "fmt_d: db \"%%ld\", 0\n");
    fprintf(out_file, "fmt_f: db \"%%f\", 0\n");
    fprintf(out_file, "fmt_s: db \"%%s\", 0\n");

    // this are strings that contain a line break character
    fprintf(out_file, "fmt_dln: db \"%%ld\", 10, 0\n");
    fprintf(out_file, "fmt_fln: db \"%%f\", 10, 0\n");
    fprintf(out_file, "fmt_sln: db \"%%s\", 10, 0\n");
    fprintf(out_file, "\n");

    initSymTable(&table);

    stdin = fopen(argv[1], "r");

    int ret = yyparse(); // call the syntactic analyzer
    if (ret == 1)
    {
        fclose(out_file);
        remove(s);
        return 1;
    }

    fprintf(out_file, "mov rax,0\n");
    fprintf(out_file, "ret\n");

    fclose(out_file);

    // Print success message and symbol table
    printf("\n=== COMPILATION SUCCESSFUL ===\n");
    printf("Assembly code generated in: %s\n\n", s);
    printf("=== SYMBOL TABLE ===\n");
    printSymTable(&table);
    fclose(stdin);

    return 0;
}
