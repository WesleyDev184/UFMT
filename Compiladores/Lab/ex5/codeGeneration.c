#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbolTable.h"
#include "codeGeneration.h"

// Codigo para declaracao de variaveis
void makeCodeDeclaration(char *dest, char *identifier, Type type, char *value)
{
    if (type == INTEGER)
    {
        if (value == NULL)
            sprintf(dest, "%s: dq 0\n", identifier);
        else
        {
            int x = atoi(value);
            sprintf(dest, "%s: dq %d\n", identifier, x);
        }
    }
    else if (type == REAL)
    {
        if (value == NULL)
            sprintf(dest, "%s: dq 0.0\n", identifier);
        else
        {
            float x = atof(value);
            sprintf(dest, "%s: dq %f\n", identifier, x);
        }
    }
    else if (type == STRING)
    {
        if (value == NULL)
            sprintf(dest, "%s: db 0\n", identifier);
        else
        {
            // Remove quotes from string literal
            char *str_value = strdup(value);
            int len = strlen(str_value);
            if (len >= 2 && str_value[0] == '"' && str_value[len - 1] == '"')
            {
                str_value[len - 1] = '\0';
                memmove(str_value, str_value + 1, len - 1);
                str_value[len - 2] = '\0';
            }
            sprintf(dest, "%s: db %s, 0\n", identifier, str_value);
            free(str_value);
        }
    }
    else
    {
        printf("error: unknown type\n");
    }
}

// Termino da secao de dados e comeco da secao de codigo
void dumpCodeDeclarationEnd()
{
    fprintf(out_file, "\nsection .text\n");
    fprintf(out_file, "global main\n");
    fprintf(out_file, "\nmain:\n");
}

int makeCodeAssignment(char *dest, char *id, char *expr)
{
    SymTableEntry *ret = findSymTable(&table, id);
    dest[0] = '\0';

    if (ret == NULL)
    {
        fprintf(stderr, "Error: %s not recognized at line %d\n", id, cont_lines);
        return 0;
    }

    if (ret->type == INTEGER || ret->type == REAL)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "pop rbx\n");
        sprintf(dest + strlen(dest), "mov [%s],rbx\n", ret->identifier);
    }
    else if (ret->type == STRING)
    {
        // For strings, we need different handling
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "pop rbx\n");
        sprintf(dest + strlen(dest), "mov [%s],rbx\n", ret->identifier);
    }
    else
    {
        fprintf(stderr, "Unsupported type for assignment at line %d\n",
                cont_lines);
        return 0;
    }
    return 1;
}

int makeCodeLoad(char *dest, char *id, int ref)
{
    dest[0] = '\0';

    if (ref == 0)
    {
        // Check if it's a floating point number
        if (strchr(id, '.') != NULL)
        {
            // For floating point literals, load as integer for now
            // This is a simplification - proper implementation would use xmm registers
            double val = atof(id);
            sprintf(dest + strlen(dest), "mov rbx, %lld\n", *(long long *)&val);
        }
        else
        {
            sprintf(dest + strlen(dest), "mov rbx,%s\n", id);
        }
        sprintf(dest + strlen(dest), "push rbx\n");
        return 1;
    }

    // Symbol table check is now done in syntactic analyzer
    sprintf(dest + strlen(dest), "mov rbx,[%s]\n", id);
    sprintf(dest + strlen(dest), "push rbx\n");
    return 1;
}

void makeCodeAdd(char *dest, char *value)
{
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "add rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

void makeCodeSub(char *dest, char *value)
{
    sprintf(dest + strlen(dest), "%s", value);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "sub rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

void makeCodeMul(char *dest, char *value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "imul rbx,rcx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

void makeCodeDiv(char *dest, char *value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rax\n");
}

void makeCodeMod(char *dest, char *value2)
{
    sprintf(dest + strlen(dest), "%s", value2);
    sprintf(dest + strlen(dest), "pop r8\n");
    sprintf(dest + strlen(dest), "pop rax\n");
    sprintf(dest + strlen(dest), "xor rdx,rdx\n");
    sprintf(dest + strlen(dest), "idiv r8\n");
    sprintf(dest + strlen(dest), "push rdx\n");
}
