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

// Code for variable declaration
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
            double x = atof(value);
            sprintf(dest, "%s: dq %f\n", identifier, x);
        }
    }
    else
    {
        printf("error: unknown type\n");
    }
}

// End of data section and beginning of code section
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

    // Validation already done in the syntactic analyzer
    if (ret->type == INTEGER || ret->type == REAL)
    {
        sprintf(dest + strlen(dest), "%s", expr);
        sprintf(dest + strlen(dest), "pop rbx\n");
        sprintf(dest + strlen(dest), "mov [%s],rbx\n", ret->identifier);
    }
    else
    {
        fprintf(stderr, "Unsupported operation involving string at line %d\n",
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
        // It's a numeric literal (integer or float)
        if (strchr(id, '.') != NULL)
        {
            // It's a float number
            double val = atof(id);
            sprintf(dest + strlen(dest), "mov rbx,%ld\n", *(long *)&val);
        }
        else
        {
            // It's an integer number
            sprintf(dest + strlen(dest), "mov rbx,%s\n", id);
        }
        sprintf(dest + strlen(dest), "push rbx\n");
        return 1;
    }

    SymTableEntry *ret = findSymTable(&table, id);
    // Validation already done in the syntactic analyzer

    sprintf(dest + strlen(dest), "mov rbx,[%s]\n", ret->identifier);
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
    sprintf(dest + strlen(dest), "pop rcx\npop rbx\nimul rbx,rcx\npush rbx\n");
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

void makeCodeNeg(char *dest)
{
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "neg rbx\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

// Implementation of new functions for I/O
void makeCodeRead(char *dest, char *varname, Type type)
{
    dest[0] = '\0';
    if (type == INTEGER)
    {
        sprintf(dest + strlen(dest), "lea rdi, [fmt_d]\n");
        sprintf(dest + strlen(dest), "lea rsi, [%s]\n", varname);
        sprintf(dest + strlen(dest), "call scanf\n");
    }
    else if (type == REAL)
    {
        sprintf(dest + strlen(dest), "lea rdi, [fmt_f]\n");
        sprintf(dest + strlen(dest), "lea rsi, [%s]\n", varname);
        sprintf(dest + strlen(dest), "call scanf\n");
    }
}

void makeCodeWrite(char *dest)
{
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "mov rsi, rbx\n");
    sprintf(dest + strlen(dest), "lea rdi, [fmt_dln]\n");
    sprintf(dest + strlen(dest), "call printf\n");
}

void makeCodeWriteString(char *dest, char *str)
{
    dest[0] = '\0';
    // Remove quotes from string and create a label for it
    static int string_counter = 0;
    char string_label[64];
    sprintf(string_label, "str_%d", string_counter++);

    // Add string to data section (this should be done in a separate function)
    // For now, we'll use the string directly
    int len = strlen(str);
    char clean_str[len + 1];

    // Remove the quotes
    if (str[0] == '"' && str[len - 1] == '"')
    {
        strncpy(clean_str, str + 1, len - 2);
        clean_str[len - 2] = '\0';
    }
    else
    {
        strcpy(clean_str, str);
    }

    sprintf(dest + strlen(dest), "lea rdi, [fmt_sln]\n");
    sprintf(dest + strlen(dest), "mov rsi, %s\n", clean_str);
    sprintf(dest + strlen(dest), "call printf\n");
}

// Implementation of functions for control structures
static int label_counter = 0;

void makeCodeIf(char *dest, char *condition, char *body)
{
    int label = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "je .L%d\n", label);
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), ".L%d:\n", label);
}

void makeCodeIfElse(char *dest, char *condition, char *ifBody, char *elseBody)
{
    int label1 = label_counter++;
    int label2 = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "je .L%d\n", label1);
    sprintf(dest + strlen(dest), "%s", ifBody);
    sprintf(dest + strlen(dest), "jmp .L%d\n", label2);
    sprintf(dest + strlen(dest), ".L%d:\n", label1);
    sprintf(dest + strlen(dest), "%s", elseBody);
    sprintf(dest + strlen(dest), ".L%d:\n", label2);
}

void makeCodeWhile(char *dest, char *condition, char *body)
{
    int label1 = label_counter++;
    int label2 = label_counter++;
    dest[0] = '\0';

    sprintf(dest + strlen(dest), ".L%d:\n", label1);
    sprintf(dest + strlen(dest), "%s", condition);
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "je .L%d\n", label2);
    sprintf(dest + strlen(dest), "%s", body);
    sprintf(dest + strlen(dest), "jmp .L%d\n", label1);
    sprintf(dest + strlen(dest), ".L%d:\n", label2);
}

// Implementation of functions for comparisons
void makeCodeComparison(char *dest, char *op)
{
    sprintf(dest + strlen(dest), "pop rcx\n");
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, rcx\n");

    if (strcmp(op, "<") == 0)
    {
        sprintf(dest + strlen(dest), "setl al\n");
    }
    else if (strcmp(op, ">") == 0)
    {
        sprintf(dest + strlen(dest), "setg al\n");
    }
    else if (strcmp(op, "<=") == 0)
    {
        sprintf(dest + strlen(dest), "setle al\n");
    }
    else if (strcmp(op, ">=") == 0)
    {
        sprintf(dest + strlen(dest), "setge al\n");
    }
    else if (strcmp(op, "==") == 0)
    {
        sprintf(dest + strlen(dest), "sete al\n");
    }
    else if (strcmp(op, "!=") == 0)
    {
        sprintf(dest + strlen(dest), "setne al\n");
    }

    sprintf(dest + strlen(dest), "movzx rbx, al\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}

void makeCodeNot(char *dest)
{
    sprintf(dest + strlen(dest), "pop rbx\n");
    sprintf(dest + strlen(dest), "cmp rbx, 0\n");
    sprintf(dest + strlen(dest), "sete al\n");
    sprintf(dest + strlen(dest), "movzx rbx, al\n");
    sprintf(dest + strlen(dest), "push rbx\n");
}
