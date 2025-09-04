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
#include "symbolTable.h"

// Size of an uninitialized string
#define STRING_SIZE 4096
extern FILE *out_file;

// Assembly file structure functions
void makePreambule(const char *filename);
void makeCodeEpilogue(void);
void resetLabelCounter();

// Variable declaration and management
void makeCodeDeclaration(char *dest, char *identifier, Type type, char *value);
void dumpCodeDeclarationEnd(void);

// Assignment and loading
int makeCodeAssignment(char *dest, char *id, char *expr);
int makeCodeLoad(char *dest, char *id, int ref);

// Arithmetic operations (no value parameter needed)
void makeCodeAdd(char *dest);
void makeCodeSub(char *dest);
void makeCodeMul(char *dest);
void makeCodeDiv(char *dest);
void makeCodeMod(char *dest);
void makeCodeNeg(char *dest);

// I/O operations
void makeCodeRead(char *dest, char *varname, Type type);
void makeCodeWrite(char *dest);
void makeCodeWriteType(char *dest, Type type);
void makeCodeWriteString(char *dest, char *str);

// Type conversion
void makeCodeFloatToInt(char *dest);

// Control structures
void makeCodeIf(char *dest, char *condition, char *body);
void makeCodeIfElse(char *dest, char *condition, char *ifBody, char *elseBody);
void makeCodeWhile(char *dest, char *condition, char *body);

// Comparison and logical operations
void makeCodeComparison(char *dest, char *op);
void makeCodeNot(char *dest);

#endif