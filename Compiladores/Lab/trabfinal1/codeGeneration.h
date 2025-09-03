/*
 *
 * UFMT - Universidade Federal de Mato Grosso
 * Laboratório de Compiladores
 * Author: Wesley Antonio Junior dos Santos
 * RGA:202011722024
 */

#ifndef CODE_H
#define CODE_H

#include <stdio.h>
#include <stdlib.h>

// Size of an uninitialized string
#define STRING_SIZE 256
extern FILE *out_file;

void makeCodeDeclaration(char *dest, char *identifier, Type type, char *value);
void dumpCodeDeclarationEnd();

int makeCodeAssignment(char *dest, char *id, char *expr);
int makeCodeLoad(char *dest, char *id, int ref);

void makeCodeAdd(char *dest, char *value);
void makeCodeSub(char *dest, char *value);
void makeCodeMul(char *dest, char *value2);
void makeCodeDiv(char *dest, char *value2);
void makeCodeMod(char *dest, char *value2);
void makeCodeNeg(char *dest);

// New functions for I/O
void makeCodeRead(char *dest, char *varname, Type type);
void makeCodeWrite(char *dest);
void makeCodeWriteString(char *dest, char *str);

// New functions for control structures
void makeCodeIf(char *dest, char *condition, char *body);
void makeCodeIfElse(char *dest, char *condition, char *ifBody, char *elseBody);
void makeCodeWhile(char *dest, char *condition, char *body);

// New functions for comparisons
void makeCodeComparison(char *dest, char *op);
void makeCodeNot(char *dest);

#endif