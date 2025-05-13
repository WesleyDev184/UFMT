/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.4
 * @date 2022-02-04
 * 
 */

// Inclusao do cabecalho
#include "synt.h"

// Variaveis globais
type_token *lookahead;
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
extern char output_file_name[MAX_CHAR];
extern FILE *output_file;

/**
 * @brief Verifica se o proximo caracter (a frente) na cadeia eh o esperado
 * 
 * @param token_tag (int) codigo do token a ser verificado 
 * @return int true/false
 */
int match(int token_tag) {
    // printf("[DEBUG] Token esperado: %d\n", token_tag);
    printf("[DEBUG] Token recebido: %d\n", lookahead->tag);

    if ( lookahead->tag == token_tag ) {
        lookahead = getToken(); //Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return ERROR;
}

/**
 * @brief Regra de derivacao inicial
 */
int program (void) {
    gen_preambule(); 

    int flag = declarations();

    if (flag == false) {
        printf("[ERRO] Erro na declaracao.\n");
        return ERROR;
    }
    gen_bss_section();
    gen_preambule_code(); 

    if (lookahead->tag == BEGIN) {
        match(BEGIN);
        flag = statements();

        if (flag == false) {
            printf("[ERRO] Erro nos comandos.\n");
            return ERROR;
        }

        if (lookahead->tag == END) {
            match(END);
            gen_epilog_code();
            gen_data_section();
        } else {
            printf("[ERRO] Faltou o END.\n");
            return ERROR;
        }
    } else {
        printf("[ERRO] Faltou o BEGIN.\n");
        return ERROR;
    }

    
    return true;
}

/**
 * @brief Regra de derivacao para declaracoes
 */
int declarations(void) {
    int success;
    do {
        success = declaration();
    } while (success == true);

    if (success == ERROR) {
        printf("[ERRO] Erro na declaracao.\n");
        return ERROR;
    } else {
        printf("[SUCESSO] Declaracao realizada com sucesso.\n");
        return true;
    }
}

/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration (void) {
    type_symbol_table_entry *search_symbol;
    char var_name[MAX_CHAR];
    int var_type;

    //Verifica o tipo da variavel
    var_type = lookahead->tag;
    if ( var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING || var_type == VOID ) { 
        match(var_type);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find( var_name, &global_symbol_table_variables );

        if ( search_symbol != NULL) {
            printf ("[ERRO] Variavel '%s' ja declarada.\n", var_name); 
            return ERROR;
        } else {
            if ( match(ID) ) {
                if (lookahead->tag == SEMICOLON){
                    printf("[DEBUG] Declaracao de variavel: %s\n", var_name);
                    return declarationV(var_name, var_type);
                } else if (lookahead->tag == OPEN_PAR) {
                    printf("[DEBUG] Declaracao de funcao: %s\n", var_name);
                    return declarationF(var_name, var_type);
                } else {
                    printf("[ERRO] Nao foi possivel identificar se é variavel ou funcao.\n");
                    return ERROR;
                }
            } else {
                printf("[ERRO] Deveria existir um ID.\n");
                return ERROR;
            }
        }
    } else if (lookahead->tag == ENDTOKEN ||
                lookahead->tag == READ ||
                lookahead->tag == BEGIN ||
                lookahead->tag == WRITE || lookahead->tag == IF || lookahead->tag == ID) {
        return false;         
    } else {
        printf ("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return ERROR; 
    }
}

/**
 * @brief Regra de derivacao declaracaoV, responsavel por declarar uma variavel
 * @param var_name nome da variável
 * @param var_type tipo da variável
 * @return int true/false
 */
int declarationV(char *var_name, int var_type) {
    if (var_type == VOID) {
        printf("[ERRO] Variavel do tipo VOID nao eh permitida.\n");
        return ERROR;
    }

    sym_declare( var_name, var_type, 0, &global_symbol_table_variables);
    return match(SEMICOLON); 
}

/**
 * @brief Processa a lista de parâmetros da função
 * @param params array de parâmetros
 * @param nparams ponteiro para o número de parâmetros
 * @return int true/false
 */
int process_params(type_symbol_table_entry params[], int *nparams) {
    int count = 0;
    while (lookahead->tag != CLOSE_PAR && count < MAX_PARAMS) {
        int var_type = lookahead->tag;
        if (var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING || var_type == VOID) {
            match(var_type);
            if (lookahead->tag != ID) {
                printf("[ERRO] Esperado identificador do parametro.\n");
                return ERROR;
            }
            char var_name[MAX_CHAR];
            strcpy(var_name, lookahead->lexema);
            match(ID);
            strncpy(params[count].name, var_name, MAX_TOKSZ);
            params[count].type = var_type;
            count++;

            if (lookahead->tag == COMMA) {
                match(COMMA);
                continue;
            } else {
                break;
            }
        } else {
            break;
        }
    }
    *nparams = count;
    return true;
}

/**
 * @brief Regra de derivacao declaracaoF, responsavel por declarar uma funcao
 * @param func_name nome da função
 * @param func_type tipo da funcao
 * @return int true/false
 */
int declarationF(char *func_name, int func_type) {
    type_symbol_function_entry *f = sym_func_find(func_name);
    int nparams = 0;
    type_symbol_table_entry params[MAX_PARAMS];

    // Inicia a leitura dos parâmetros
    if (!match(OPEN_PAR)) {
        printf("[ERRO] Esperado '(' apos o nome da funcao.\n");
        return ERROR;
    }
    
    // Processa da lista de parâmetros usando a função auxiliar
    if (process_params(params, &nparams) == ERROR) {
        printf("[ERRO] Problema na lista de parametros da funcao '%s'.\n", func_name);
        return ERROR;
    }
    
    if (!match(CLOSE_PAR)) {
        printf("[ERRO] Esperado ')' apos os parametros da funcao.\n");
        return ERROR;
    }
    
    // Diferencia se é somente a declaracao (prototype) ou a implementacao completa.
    if (lookahead->tag == SEMICOLON) {
        // Prototype: declara a funcao sem corpo
        match(SEMICOLON);
        // Verifica se a funcao ja foi declarada
        if (f != NULL) {
            printf("[ERRO] Funcao '%s' ja declarada.\n", func_name);
            return ERROR;
        }
        sym_func_declare(func_name, func_type, params, nparams);
        return true;
    } else if (lookahead->tag == BEGIN) {
        // Definicao: implementacao completa da funcao
        match(BEGIN);
        gen_func_label(func_name);
        if (f != NULL) {
            if (f->implemented) {
                printf("[ERRO] Funcao '%s' ja implementada.\n", func_name);
                return ERROR;
            }
        } else {
            printf("[ERRO] Funcao '%s' nao declarada.\n", func_name);
            return ERROR;
        }
        
        // Processa os comandos (corpo) da funcao
        int flag = statements();
        if (flag == ERROR) {
            printf("[ERRO] Problemas na implementacao da funcao '%s'.\n", func_name);
            return ERROR;
        }
        if (!match(END)) {
            printf("[ERRO] Fim de corpo da funcao ausente.\n");
            return ERROR;
        }
        // Marca a funcao como implementada
        f->implemented = 1;
        gen_return();
        return true;
    } else {
        printf("[ERRO] Esperado ';' (declaracao) ou 'BEGIN' (implementacao) apos os parametros da funcao.\n");
        return ERROR;
    }
}

/**
 * @brief Regra de derivacao para comandos
 */
int statements (void) {
//    while ( statement() );  //processa enquanto houver comandos
    int sucess;
    do {
        sucess = statement();
    } while (sucess == true);

    if (sucess == ERROR) {
        return ERROR;
    } else {
        return true;
    } 
}

/**
 * @brief Regra de derivacao que processa os comandos
 * 
 * @return int true/false
 */
int statement (void) {
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;
    type_symbol_table_string_entry *search_symbol_string;
    type_symbol_table_string_entry *gen_string;
    int ok1, ok2, type;
    char string_value[MAX_STRING];

    if (lookahead->tag == READ) {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        ok1 = match(ID);
        if (ok1 == false) {
            printf("[ERRO] Comando de leitura sem identificador.\n");
            return ERROR;
        }
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol != NULL) {
            type = search_symbol->type;
            gen_read(lexeme_of_id, type);
            // se nao receber ; eh erro
            if (lookahead->tag != SEMICOLON) {
                printf("[ERRO] Comando de leitura sem ponto e virgula.\n");
                return ERROR;
            } else {
                match(SEMICOLON);
                return true;
            }
            
        } else {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada - read): %s\n", lexeme_of_id);
            return ERROR;
        }
    } else if (lookahead->tag == WRITE) {
        match(WRITE);
        if ( lookahead->tag == STRING ) {
            strcpy(string_value, lookahead->lexema);
            //TODO: verificar se o valor da constante ja foi incluida na tabela de simbolos
            search_symbol_string = sym_string_find(string_value);
            if (search_symbol_string == NULL) {
                gen_string = sym_string_declare(string_value);
            } else {
                gen_string = search_symbol_string;
            }
            
            match(STRING);
            if ( gen_string != NULL ) {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                // se nao receber ; eh erro
                if (lookahead->tag != SEMICOLON) {
                    printf("[ERRO] Comando de escrita sem ponto e virgula.\n");
                    return ERROR;
                } else {
                    match(SEMICOLON);
                    return true;
                }
            } else {
                printf("[ERRO] Erro ao declarar string.\n");
                return ERROR;
            }
        } else if ( lookahead->tag == ID) {
            strcpy(lexeme_of_id, lookahead->lexema);
            match(ID);
            search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
            if (search_symbol != NULL) {
                type = search_symbol->type;
                gen_write(lexeme_of_id, type);
                if (lookahead->tag != SEMICOLON) {
                    printf("[ERRO] Comando de escrita sem ponto e virgula.\n");
                    return false;
                } else {
                    match(SEMICOLON);
                    return true;
                }

                return true;
            } else {
                printf("[ERRO] Simbolo desconhecido (Variavel nao declarada - write): %s\n", lexeme_of_id);
                return ERROR;
            }
        }
    } else if (lookahead->tag == IF) {
        char label_else[MAX_CHAR];
        char label_end[MAX_CHAR];
        int flag_bool, flag;
        gen_label_name(label_else);
        gen_label_name(label_end);

        match(IF);
        // verificar se de fato recebe parenteses
        flag = match(OPEN_PAR);
        if (flag == false) {
            printf("[ERRO] Comando IF sem parenteses.\n");
            return ERROR;
        }

        flag_bool = B(); //Expressao booleana
        if (flag_bool == false) {
            printf("[ERRO] Expressao booleana mal formada.\n");
            return ERROR;
        }
        
        gen_cond_jump(label_else);
        
        flag = match(CLOSE_PAR);
        if (flag == false) {
            printf("[ERRO] Comando IF sem parenteses.\n");
            return ERROR;
        }
        
        flag = match(BEGIN);
        if (flag == false) {
            printf("[ERRO] Comando IF sem BEGIN.\n");
            return ERROR;
        }

        flag = statements();

        if (flag == false) {
            printf("[ERRO] Comando IF sem comandos.\n");
            return ERROR;
        }

        flag = match(END);

        if (flag == false) {
            printf("[ERRO] Comando IF sem END.\n");
            return ERROR;
        }

        gen_incond_jump(label_end);
        gen_label(label_else);

        //Verifica se ocorre um ELSE
        if (lookahead->tag == ELSE) {
            flag = match(ELSE);
            if (flag == false) {
                printf("[ERRO] Comando ELSE sem ELSE.\n");
                return ERROR;
            }
            flag = match(BEGIN);
            if (flag == false) {
                printf("[ERRO] Comando ELSE sem BEGIN.\n");
                return ERROR;
            }
            flag = statements();
            if (flag == false) {
                printf("[ERRO] Comando ELSE sem comandos.\n");
                return ERROR;
            }
            flag = match(END);
            if (flag == false) {
                printf("[ERRO] Comando ELSE sem END.\n");
                return ERROR;
            }
        }
        gen_label(label_end);
        return true;
    } else if (lookahead->tag == WHILE) {
        char label_begin[MAX_CHAR];
        char label_end[MAX_CHAR];
        int flag;
        gen_label_name(label_begin);
        gen_label_name(label_end);

        flag = match(WHILE);
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem WHILE.\n");
            return ERROR;
        }

        flag = match(OPEN_PAR);
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem parenteses.\n");
            return ERROR;
        }

        gen_label(label_begin);

        flag = B(); //Expressao booleana
        if (flag == false) {
            printf("[ERRO] Expressao booleana mal formada.\n");
            return ERROR;
        }

        gen_cond_jump(label_end);

        flag = match(CLOSE_PAR);
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem parenteses.\n");
            return ERROR;
        }

        flag = match(BEGIN);
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem BEGIN.\n");
            return ERROR;
        }

        flag = statements();
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem comandos.\n");
            return ERROR;
        }

        flag = match(END);
        if (flag == false) {
            printf("[ERRO] Comando WHILE sem END.\n");
            return ERROR;
        }

        gen_incond_jump(label_begin);
        gen_label(label_end);
        return true;
        
    } else if (lookahead->tag == ID) {
    strcpy(lexeme_of_id, lookahead->lexema);
    match(ID);
    search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
    if (search_symbol != NULL) {
        type = search_symbol->type;
        genId(lexeme_of_id); // gera código para o ID ser salvo na pilha
        if (lookahead->tag == ASSIGN) {
            match(ASSIGN);
            // Parse the arithmetic expression after '=':
            if (!E()) {
                printf("[ERRO] Expressao invalida na atribuicao.\n");
                return ERROR;
            }
            genAssign(lexeme_of_id, type);
            if (lookahead->tag != SEMICOLON) {
                printf("[ERRO] Comando de atribuicao sem ponto e virgula.\n");
                return ERROR;
            } else {
                match(SEMICOLON);
                return true;
            }
        } else {
            printf("[ERRO] Comando de atribuicao sem '=' ou função mal declarada.\n");
            return ERROR;
        }
    } else {
        // Se não encontrou como variável, verifica se é uma função declarada
        type_symbol_function_entry *search_symbol_func = sym_func_find(lexeme_of_id);
        if (search_symbol_func != NULL && search_symbol_func->implemented) {
            // Verifica se a chamada está correta: deve abrir e fechar parênteses
            if (lookahead->tag == OPEN_PAR) {
                match(OPEN_PAR);

                // Processamento dos parâmetros da chamada de função
                int param_count = 0;
                int expected_params = search_symbol_func->nparams;
                type_symbol_table_entry *param_entry;

                if (lookahead->tag != CLOSE_PAR) {
                    while (1) {
                        // Verifica se há mais parâmetros do que o esperado
                        if (param_count >= expected_params) {
                            printf("[ERRO] Chamada de função '%s' com parâmetros em excesso.\n", lexeme_of_id);
                            return ERROR;
                        }

                        // Espera um identificador como argumento
                        if (lookahead->tag == ID) {
                            char param_lex[MAX_CHAR];
                            strcpy(param_lex, lookahead->lexema);
                            match(ID);

                            // Busca o parâmetro na tabela de símbolos
                            param_entry = sym_find(param_lex, &global_symbol_table_variables);
                            if (!param_entry) {
                                printf("[ERRO] Parâmetro '%s' não declarado.\n", param_lex);
                                return ERROR;
                            }

                            // Verifica o tipo do parâmetro
                            if (param_entry->type != search_symbol_func->params[param_count].type) {
                                printf("[ERRO] Tipo do parâmetro %d incompatível na chamada da função '%s'. Esperado: %d, Encontrado: %d\n",
                                       param_count + 1, lexeme_of_id,
                                       search_symbol_func->params[param_count].type, param_entry->type);
                                return ERROR;
                            }

                            // Gera código para empilhar o valor do parâmetro
                            genId(param_lex);

                            // Gera código para copiar o valor do parâmetro real para o parâmetro formal da função
                            // Isso garante que o valor passado seja atribuído à variável do parâmetro da função
                            genAssign(search_symbol_func->params[param_count].name, search_symbol_func->params[param_count].type);

                        } else {
                            printf("[ERRO] Esperado identificador como parâmetro na chamada da função '%s'.\n", lexeme_of_id);
                            return ERROR;
                        }

                        param_count++;

                        // Se houver vírgula, continua para o próximo parâmetro
                        if (lookahead->tag == COMMA) {
                            match(COMMA);
                            continue;
                        } else {
                            break;
                        }
                    }
                }

                // Verifica se o número de parâmetros está correto
                if (param_count != expected_params) {
                    printf("[ERRO] Quantidade de parâmetros incompatível na chamada da função '%s'. Esperado: %d, Encontrado: %d\n",
                           lexeme_of_id, expected_params, param_count);
                    return ERROR;
                }

                // Gera o código de chamada da função
                gen_call_function(lexeme_of_id);

                if (lookahead->tag != CLOSE_PAR) {
                    printf("[ERRO] Chamada de função '%s' sem fechamento de parênteses.\n", lexeme_of_id);
                    return ERROR;
                }
                match(CLOSE_PAR);
                if (lookahead->tag != SEMICOLON) {
                    printf("[ERRO] Chamada de função '%s' sem ponto e vírgula.\n", lexeme_of_id);
                    return ERROR;
                }
                match(SEMICOLON);
                return true;
            } else {
                printf("[ERRO] Chamada de função '%s' sem abertura de parênteses.\n", lexeme_of_id);
                return ERROR;
            }
        } else {
            printf("[ERRO] Simbolo desconhecido (Variavel ou Funcao nao declarada ou implementada - id): %s\n", lexeme_of_id);
            return ERROR;
        }
    }
}
    else if (lookahead->tag == ENDTOKEN || lookahead->tag == END) {
        return false;
    } else {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n", lookahead->tag, lookahead->lexema);
        return ERROR;
    }
}

/**
 * @brief Regra de derivação que analisa expressoes booleanas
 *        no padrao '[id | expr] op_rel [id | expr]' 
 * 
 */
int B() { 
    int flag_left = B_and();
    
    while (lookahead->tag == OR) { 
        match(OR);
        int flag_right = B_and();
        gen_logical(OR);
        flag_left = true; // Indica sucesso
    }
    
    return flag_left;
}

// Processa o and
int B_and() {
    int flag_left = B_relacional();
    
    while (lookahead->tag == AND) {
        match(AND);
        int flag_right = B_relacional(); 
        gen_logical(AND); 
        flag_left = true; // indica sucesso
    }
    
    return flag_left;
}

// Processa operadores relacionais
int B_relacional() {
    int flag_left = 0;
    int flag = 0;

    // se tiver (), primeiro deve avaliar a subexpressao
    if (lookahead->tag == '(') {
        match('(');
        flag_left = B(); // recursividade
        match(')');
    } else if (lookahead->tag == ID) { // se for ID
        genId(lookahead->lexema); // gera código para o ID ser salvo
        match(ID);
        flag_left = true;
    } else {
        flag_left = E(); // Processa expressão aritmética
    }

    if (boolOperatorVerify()) { // verifica se tem operador relacional
        int operator;
        boolOperator(&operator); 

        // Avalia o lado direito
        if (lookahead->tag == '(') {
            match('(');
            B(); // Avalia a subexpressão dentro dos parênteses
            flag = match(')');
            if (flag == false) {
                printf("[ERRO] Comando IF sem fechamento de parenteses.\n");
                return ERROR;
            }
        } 
        else if (lookahead->tag == ID) {
            genId(lookahead->lexema);
            match(ID);
        } 
        else {
            flag = E(); // expressao aritmetica
            if (flag == false) {
                printf("[ERRO] Expressao booleana mal formada.\n");
                return ERROR;
            }
        }
        
        gen_bool(operator); 
        flag_left = true;
    }
    
    return flag_left;
}


int boolOperator(int *operator) {
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    *operator = -1;
    
    if (lookahead_tag == EQUAL ||
        lookahead_tag == NE ||
        lookahead_tag == LT ||
        lookahead_tag == GT ||
        lookahead_tag == LE ||
        lookahead_tag == GE) {
            *operator = lookahead_tag;
            match(lookahead_tag);
            return true;
    } else {
        printf("[ERRO] Operador relacional esperado.\n");
        return ERROR;
    }
}

int boolOperatorVerify() {
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    
    if (lookahead_tag == EQUAL ||
        lookahead_tag == NE ||
        lookahead_tag == LT ||
        lookahead_tag == GT ||
        lookahead_tag == LE ||
        lookahead_tag == GE) {
            return true;
    } else {
        return false;
    }
}

int logicalOperatorVerify() {
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    
    if (lookahead_tag == AND ||
        lookahead_tag == OR) {
            return true;
    } else {
        return false;
    }
}

//------
/* Funções que representam a gramatica que reconhece expressoes aritmeticas */
/* Elaborada nas primeiras aulas */
int E() {
    int b1, b2;
    b1 = T();
    
    if (b1) {
        b2 = ER();
    }
    return b1 && b2;
}

int ER() {
    if (lookahead->tag == '+')  { 
        int b1, b2;
        match('+');
        b1 = T();
        genAdd();
        if (b1) 
            b2 = ER();
        return b1 && b2;
    } else if (lookahead->tag == '-') {
        int b1, b2;
        match('-');
        b1 = T();
        genSub();
        if (b1)
            b2 = ER();
        return b1 && b2;      
    } else if (lookahead -> tag == ')') {
        return true;
    } else if (lookahead -> tag == ENDTOKEN || boolOperatorVerify() || logicalOperatorVerify() || lookahead->tag == SEMICOLON) { //EOF
        return true;
    } else if (lookahead -> tag == '*') {
        return true;
    } else if (lookahead -> tag == '/') {
        return true;
    } else {
        printf("[ERRO] Operador aritmetico esperado.\n");
        return ERROR;
    }
}

int T() {
    int b1, b2;
    b1 = F();
    if (b1) {
        b2 = TR();
    }
    return b1 && b2;
}

int TR() {
    if (lookahead->tag == '*') { 
        int b1, b2;
        match('*');
        b1 = F();
        genMult();
        if (b1)
            b2 = TR();
        return b1 && b2;
    } else if (lookahead -> tag == '/') {
        int b1, b2;
        match('/');
        b1 = F();
        genDiv();
        if (b1)
            b2 = TR();
        return b1 && b2;
    } else if (lookahead->tag == ')') {
        return true;
    } else if (lookahead->tag == ENDTOKEN || boolOperatorVerify() || logicalOperatorVerify() || lookahead->tag == SEMICOLON){
        return true;
    } else if (lookahead->tag == '+') {
        return true;
    } else if (lookahead->tag == '-') {
        return true;
    } else {
        return false;
    }
}

int F() {
    if (lookahead->tag == '(') {
        int b1, b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    } else if (lookahead->tag == ID) {
        genId(lookahead->lexema);
        return match(ID);
    } else if (lookahead->tag == INT) {
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        int b1 = match(INT);
        genNum(lexema, INT);
        return b1;
    } else if (lookahead->tag == FLOAT) {
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        int b1 = match(FLOAT);
        genNum(lexema, FLOAT);
        return b1;
    } else if (lookahead->tag == STRING) {
        char literal[MAX_STRING];
        strcpy(literal, lookahead->lexema);
        type_symbol_table_string_entry *entry = sym_string_declare(literal);
        gen_push_string_literal(entry->name);
        match(STRING);
        return true;
    } else {
        return false;
    }
}
/*fim da importação */
//------


//--------------------- MAIN -----------------------

/**
 * @brief Funcao principal (main) do compilador
 * 
 * @return int 
 */
int main(int argc, char *argv[]) {
    int sucess;

    //Inicializa a tabela de simbolo global
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    //Verifica a passagem de parametro
    if (argc != 2) {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }
    
    initLex(argv[1]); //Carrega codigo
    lookahead = getToken(); //Inicializacao do lookahead

    //Abre o arquivo de saida 
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    sucess = program(); //Chamada da derivacao/funcao inicial da gramatica

    if (sucess == true) {
        printf("[SUCESSO] Compilacao realizada com sucesso.\n");
        // imprime a tabela de simbolos
        printSTVariables(&global_symbol_table_variables);
        printSTString();
        printTSFunction();
    } else {
        printf("[ERRO] Erro na compilacao.\n");
    }

    fclose(output_file);
    return 1;
}