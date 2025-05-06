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

#define true 1  //por conveniencia, para facilitar leitura de codigo
#define false 0 //por conveniencia, para facilitar leitura de codigo

// Definicao dos codigos dos tokens
#define ENDTOKEN '\0'
#define ERROR -1
#define NUM 1
#define PLUS '+'
#define MINUS '-'
#define MULT '*'
#define DIV '/'
#define OPEN_PAR '('
#define CLOSE_PAR ')'
#define SEMICOLON ';'
#define DOUBLE_QUOTES '"'

//KeyWords
#define ID 256
#define IF 257
#define ELSE 258
#define WHILE 259
#define DO 260
#define READ 261
#define WRITE 262
#define INT 263
#define STRING 264
#define FLOAT 265
#define CHAR 266
#define BEGIN 267
#define END 268

//Operadores
#define ASSIGN '='
#define EQUAL 269 
#define NE 270
#define GE 271
#define LE 272
#define GT '>'
#define LT '<'
#define NOT '!'
#define AND 273
#define OR 274


// Definicao da estrutura de dados 'token'
struct st_token {
    int tag;
    char lexema[MAX_STRING];
    int value;
};
typedef struct st_token type_token;

#endif //_STRUCT_COMPILER_ 