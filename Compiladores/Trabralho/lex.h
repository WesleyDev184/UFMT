/**
 * @file lex.h
 * @author Prof. Ivairton M. Santos
 * @brief Modulo do analisador lexico
 * @version 0.3
 * @date 2021-12-09
 *
 */

#ifndef _LEX_H_
#define _LEX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"

// Prototipos
void initLex(char input_file_name[]);
type_token *getToken();
type_token *keyWordFind(char *);
type_token *symbolFind(char *symbol);

#endif //_LEX_H_