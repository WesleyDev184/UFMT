/**
 * @file struct_compiler.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo para definicao de constantes e estruturas de dados do Sistema
 *        Compilador de C Simplificado
 * @version 0.3
 * @date 2021-12-09
 *
 */

#ifndef _STRUCT_COMPILER_
#define _STRUCT_COMPILER_

// Definicao de constantes para todo o compilador
#define MAX_CHAR 32
#define MAX_TOKEN 32
#define MAX_STRING 256

#define true 1  // por conveniencia, para facilitar leitura de codigo
#define false 0 // por conveniencia, para facilitar leitura de codigo

// Definicao dos codigos dos tokens
#define ENDTOKEN '\0'
#define ERROR -1
#define NUM 1
#define OPEN_PAR '('
#define CLOSE_PAR ')'
#define SEMICOLON ';'
#define COMMA ','
#define BRACKET_OPEN '{'
#define BRACKET_CLOSE '}'
#define DOUBLE_QUOTES '"'
#define BEGIN 268
#define END 269

// Palavras Reservadas
#define ID 256
#define IF 257
#define ELSE 258
#define WHILE 260
#define DO 261
#define READ 262
#define WRITE 263
#define FOR 264
#define STRUCT 274
#define RETURN 275
#define BREAK 276
#define CONTINUE 277
#define SWITCH 278
#define CASE 279
#define DEFAULT 280
#define ENUM 281
#define SIZEOF 282
#define TYPEDEF 283

// Operadores
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIV '/'
#define EQUAL '=='
#define ASSIGN '='
#define NE 274
#define GE 270
#define LE 271
#define ARROWLEFT '<'
#define ARROWRIGHT '>'
#define AND 272
#define OR 273

// Tipos de Variáveis
#define INT 265
#define FLOAT 267
#define STRING 268
#define CHAR 269
#define BOOL 272
#define VOID 273

// Definicao da estrutura de dados 'token'
struct st_token
{
    int tag;
    char lexema[MAX_CHAR];
    int value;
};
typedef struct st_token type_token;

#endif //_STRUCT_COMPILER_