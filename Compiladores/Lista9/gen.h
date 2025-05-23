/**
 * @file gen.h
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Modulo do gerador de codigo
 * @version 0.3
 * @date 2022-02-04
 *
 */
#ifndef _GEN_H_
#define _GEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "struct_compiler.h"
#include "symbols.h"

// Prototipos
void genAdd();
void genSub();
void genMult();
void genDiv();
void genNum(char num_string[MAX_TOKEN]);
void genId(char *lexeme_of_id);
void gen_preambule(void);
void gen_data_section(void);
void gen_bss_section(void);
void gen_preambule_code(void);
void gen_epilog_code(void);
void gen_read(char *, int);
void gen_write(char *, int);
void gen_label_name(char *);
void gen_label(char *);
void gen_cond_jump(char *);
void gen_incond_jump(char *);
void gen_bool(int);
void gen_bool_label_name(char *);
void gen_store_on_stack(const char *);
void gen_assign(char *id);
void gen_and(void); // Adicionado: operador lógico AND
void gen_or(void);  // Adicionado: operador lógico OR

#endif //_GEN_H_