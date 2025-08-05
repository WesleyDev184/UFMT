

#ifndef __CODEGENERATION_H__
#define __CODEGENERATION_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolTable.h"

#define STRING_SIZE 256
extern FILE *out_file;

void makeCodeDeclaration(char* dest, char* identifier, Type type, char* value);
void dumpCodeDeclarationEnd();
int makeCodeRead(char* dest, char *id);
int makeCodeWrite(char* dest, char *id, int ln);
int makeCodeAssignment(char* dest, char* id, char* expr);
int makeCodeLoad(char* dest, char* id, int ref);
void makeCodeAdd(char* dest, char* value);
void makeCodeSub(char* dest, char* value);
void makeCodeMul(char* dest, char* value2);
void makeCodeDiv(char* dest, char* value2);
void makeCodeMod(char* dest, char* value2);
#endif //__CODEGENERATION_H__