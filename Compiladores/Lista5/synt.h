/**
 * @file synt.h
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do analisado sintatico
 * @version 0.3
 * @date 2021-12-09
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
 
 // Prototipos
 int E();
 int ER();
 int T();
 int TR();
 int F();
 int digit();
 int match(int token_tag);
 
 int main();
 
 #endif //_SYNT_H_