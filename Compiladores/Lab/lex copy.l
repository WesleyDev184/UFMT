%{
/***
 * UFMT - Ciencia da Computação
 * Laboratorio de Compiladores - Prof. Ivairton
 *
 * Wesley Antonio Junior dos Santos
 * RGA: 202011722024
 * Meu primeiro programa em FLEX
 */

#include <string.h>
#include <stdio.h>

#define WS        256
#define ID        257
#define NUM       258
#define ERROR     259
#define INT       260
#define STRING    261
#define VOID      262
#define FLOAT     263
#define CHAR      264
#define BEGIN     265
#define END       266
#define READ      267
#define WRITE     268
#define WHILE    269
#define SEMICOLON 270
#define NUM_FLOAT 271

#define EQ        272
#define NEQ       273
#define LE        274
#define GE        275
#define LT        276
#define GT        277
#define ASSIGN    278
#define PLUS      279
#define MINUS     280
#define MUL       281
#define DIV       282
#define OPENPAR    283
#define CLOSEPAR    284
#define COMMA     285
#define STR 286

%}

digit      [0-9]
letter     [A-Za-z]
ws         [ \t\n]
id {letter}({letter}|{digit})*
num_int    {digit}+
num_float  {digit}+\.{digit}+
string      \"([^\\\"]|\\.)*\"
char        \'([^\\\']|\\.)\'

%%

{ws} {
    printf("ESPACO/TAB\n");
    return WS;
}

"int" {
    printf("TYPE: INT\n");
    return INT;
}

"string" {
    printf("TYPE: STRING\n");
    return STRING;
}

"void" {
    printf("TYPE: VOID\n");
    return VOID;
}

"float" {
    printf("TYPE: FLOAT\n");
    return FLOAT;
}

"char" {
    printf("TYPE: CHAR\n");
    return CHAR;
}

"begin" {
    printf("RW: BEGIN\n");
    return BEGIN;
}

"end" {
    printf("RW: END\n");
    return END;
}

"read" {
    printf("RW: READ\n");
    return READ;
}

"write" {
    printf("RW: WRITE\n");
    return WRITE;
}

"while" {
    printf("RW: WHILE\n");
    return WHILE;
}

"==" {
    printf("OP: EQ\n");
    return EQ;
}

"!=" {
    printf("OP: NEQ\n");
    return NEQ;
}

"<=" {
    printf("OP: LE\n");
    return LE;
}

">=" {
    printf("OP: GE\n");
    return GE;
}

"<" {
    printf("OP: LT\n");
    return LT;
}

">" {
    printf("OP: GT\n");
    return GT;
}

"=" {
    printf("OP: ASSIGN\n");
    return ASSIGN;
}

"\+" {
    printf("OP: PLUS\n");
    return PLUS;
}

"-" {
    printf("OP: MINUS\n");
    return MINUS;
}

"\*" {
    printf("OP: MUL\n");
    return MUL;
}

"/" {
    printf("OP: DIV\n");
    return DIV;
}

";" {
    printf("DT: SEMICOLON\n");
    return SEMICOLON;
}

"\(" {
    printf("DT: OPENPAR\n");
    return OPENPAR;
}

"\)" {
    printf("DT: CLOSEPAR\n");
    return CLOSEPAR;
}

";" {
    printf("SEMICOLON\n");
    return SEMICOLON;
}

"," {
    printf("COMMA\n");
    return COMMA;
}

{string} {
    printf("STRING: %s\n", yytext);
    return STR;
}

{char} {
    printf("CHAR: %s\n", yytext);
    return STR;
}

{id} {
    printf("ID: %s\n", yytext);
    return ID;
}

{num_int} {
    printf("NUM_INT: %s\n", yytext);
    return NUM;
}

{num_float} {
    printf("NUM_FLOAT: %s\n", yytext);
    return NUM_FLOAT;
}

. {
    printf("ERROR\n");
    return ERROR;
}

%%

int yywrap () {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int token;
    
        yyin = fopen(argv[1],"r");
        do {
            token = yylex();
            printf("Token=%d\n", token);
        } while(token != 0);
        fclose(yyin);
        return EXIT_SUCCESS;
    } else {
        printf("Informe um arquivo de entrada\n");
        return EXIT_FAILURE;
    }
}