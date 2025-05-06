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
    if ( lookahead->tag == token_tag ) {
        lookahead = getToken(); //Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

/**
 * @brief Regra de derivacao inicial
 */
int program (void) {
    gen_preambule(); //Temporariamente cria um preambulo adicional que permite o uso das funcoes scanf e printf

    int flag = declarations();

    if (flag == false) {
        //printf("[ERRO] Erro na declaracao.\n");
        return false;
    }
    gen_bss_section();
    gen_preambule_code(); //Chamada do gerador de codigo para escrita do cabecalho da secao de codigo
    flag = statements();

    if (flag == false) {
        //printf("[ERRO] Erro nos comandos.\n");
        return false;
    }

    gen_epilog_code();
    gen_data_section(); //Chamada do gerador de codigo para declaracao de variaveis
    return true;
}

/**
 * @brief Regra de derivacao para declaracoes
 */
int declarations(void) {
    // while ( declaration() ); //Laco para processamento continuo das declaracoes
    int sucess;
    do {
        sucess = declaration();
    } while (sucess == true);

    if (sucess == ERROR) {
        //printf("[ERRO] Erro na declaracao.\n");
        return false;
    } else {
        //printf("[SUCESSO] Declaracao realizada com sucesso.\n");
        return true;
    }
}

/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration (void) {
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];
    int var_type;

    //Verifica o tipo da variavel
    var_type = lookahead->tag;
    if ( var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING) { 
        match(var_type);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find( var_name, &global_symbol_table_variables );

        if ( search_symbol != NULL) {
            printf ("[ERRO] Variavel '%s' ja declarada.\n", var_name); 
            return ERROR;
        } else {
            ok1 = match(ID); //Verifica se identificador vem a seguir
            if (ok1 == false) {
                printf("[ERRO] Faltou identificador e não foi possível registrar a variável na tabela de simbolos.\n");
                return ERROR;
            }
            ok2 = match(SEMICOLON); //Verifica se ; vem a seguir

            if (ok2 == false) {
                printf("[ERRO] Faltou ponto e virgula e não foi possível registrar a variável na tabela de simbolos.\n");
                return ERROR;
            }
            sym_declare( var_name, var_type, 0, &global_symbol_table_variables);

            return ok1 && ok2;
        }
    } else if (lookahead->tag == ENDTOKEN ||
                lookahead->tag == READ ||
                lookahead->tag == WRITE || lookahead->tag == IF || lookahead->tag == ID) {
        //Verifica se fim de arquivo
        return false;         
    } else {
        printf ("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false; 
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
        return false;
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
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
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
                printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
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
                // int flag = E();
                // if (flag == false) {
                //     printf("[ERRO] Comando de atribuicao sem expressao.\n");
                //     return false;
                // }
                if (type == INT && lookahead->tag == INT) {
                    genNum(lookahead->lexema, INT);
                    match(INT);
                } else if (type == FLOAT && lookahead->tag == FLOAT) {
                    genNum(lookahead->lexema, FLOAT);
                    match(FLOAT);
                } else {
                    printf("[ERRO DE SEMANTICA] Tipo de variavel diferente do tipo da atribuicao.\n");
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
                printf("[ERRO] Comando de atribuicao sem '='.\n");
                return ERROR;
            }
        } else {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
            return ERROR;
        }
    }
    else if (lookahead->tag == ENDTOKEN || lookahead->tag == END) {
        return false;
    } else {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}


/**
 * @brief Regra de derivação que analisa expressoes booleanas
 *        no padrao '[id | expr] op_rel [id | expr]' 
 * 
 */
int B() { 
    int flag_left = B_and(); // processa o and primeiro
    
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
    int flag_left = B_relacional(); // processa os operadores relacionais
    
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
                return false;
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
                return false;
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
        return false;
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
        return false;
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
    } else if (lookahead->tag == ENDTOKEN || boolOperatorVerify() || logicalOperatorVerify() || lookahead->tag == SEMICOLON){ //EOF
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
        int b1,b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    } else if (lookahead->tag == INT) {
        int b1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        b1 = match(INT); //substituir 'id' por NUM
        genNum(lexema, INT);
        return b1;
    } else if (lookahead->tag == FLOAT) {
        int b1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        b1 = match(FLOAT); //substituir 'id' por NUM
        genNum(lexema, FLOAT);
        return b1;
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
    } else {
        printf("[ERRO] Erro na compilacao.\n");
    }

    fclose(output_file);
    return 1;
}