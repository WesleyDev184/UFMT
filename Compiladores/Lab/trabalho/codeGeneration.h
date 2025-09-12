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
extern FILE *out_file; // Assembly file structure functions
void makePreambule(const char *filename);
void makeCodeEpilogue(void);
void resetLabelCounter();

// Variable declaration and management
void makeCodeDeclaration(char *dest, char *identifier, Type type, char *value);
void dumpCodeDeclarationEnd(void);

// Assignment and loading
int makeCodeAssignment(char *dest, char *id, char *expr);
int makeCodeLoad(char *dest, char *id, int ref);

// Arithmetic operations (type-specific) - now with integrated optimizations
void makeCodeAdd(char *dest, Type type);
void makeCodeSub(char *dest, Type type);
void makeCodeMul(char *dest, Type type);
void makeCodeDiv(char *dest, Type type);
void makeCodeMod(char *dest);
void makeCodeNeg(char *dest, Type type);

// I/O operations
void makeCodeRead(char *dest, char *varname, Type type);
void makeCodeWrite(char *dest, Type type);
void makeCodeWriteString(char *dest, char *str);

// Comparison operations (type-specific)
void makeCodeComparison(char *dest, char *op, Type type);

// Type checking utilities
int checkTypeCompatibility(Type type1, Type type2);
void printTypeMismatchError(int line, const char *operation, Type type1, Type type2);
void makeCodeIf(char *dest, char *condition, char *body);
void makeCodeIfElse(char *dest, char *condition, char *ifBody, char *elseBody);
void makeCodeWhile(char *dest, char *condition, char *body);

// Logical operations
void makeCodeNot(char *dest);
void makeCodeAnd(char *dest);
void makeCodeOr(char *dest);

// Function operations
void makeCodeFunction(char *dest, char *funcName, Type returnType, char *body);
void makeCodeFunctionWithParams(char *dest, char *funcName, Type returnType, char *body, char *paramString);
void makeCodeMain(char *dest, char *body);
void makeCodeReturn(char *dest, char *expr, Type type);
void makeCodeFunctionCall(char *dest, char *funcName, char *args, Type returnType);
void makeCodeFunctionCallExpression(char *dest, char *funcName, char *args, Type returnType);

#endif