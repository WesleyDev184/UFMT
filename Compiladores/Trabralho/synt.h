/**
 * @file synt.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do analisado sintatico
 * @version 0.5
 * @date 2022-03-17
 * 
 */

#ifndef _SYNT_H_
#define _SYNT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"
#include "lex.h"
#include "gen.h"
#include "symbols.h"

/*
 * Gramatica: 
 *      program -> declarations  statements
 *      declarations-> declaration declarations | [vazio]
 *      declaration -> int id;
 *      statements --> statement statements | [vazio]
 *      statement  --> read_stmt | write_stmt | if_stmt | if_else_stmt | while_stmt | assign_stmt
 *      read_stmt  --> read id;
 *      write_stmt --> write id;
 *      if_stmt    --> if '(' rel_expr ')' begin statements end [ else begin statements end  ]  (ideal, ainda por fazer)
 *      if_stmt    --> if '(' E ')' begin statements end [ else begin statements end ] (implementado)
 *      assign_stmt -> id '=' E;
 *      rel_expr   --> id rel_operator E
 *      rel_operator -->  '<' | '>' | '<=' | '>=' | '==' | '!='
 *      E          --> expressões com numeros inteiros, cujo resultado final fica na pilha.
 */


// Prototipos
int program (void);
int declarations(void);
int statements (void);
int declaration(void);
int statement(void);

int B(void);
int B_and(void);
int B_relacional(void);
int boolOperator(int*);

int E();
int ER();
int T();
int TR();
int F();

int boolOperatorVerify();
int T1();
int T2();
int T3();

int main();

#endif //_SYNT_H_