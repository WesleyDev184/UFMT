/**
 * @file synt.c
 * @author Prof. Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.4
 * @date 2022-02-04
 * 
 */

#include "synt.h"

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
void program (void) {
    gen_preambule();
    declarations();
    gen_preambule_code();
    if (lookahead->tag == BEGIN) {
        match(BEGIN);
        statements();
        //end
        if (lookahead->tag == END) {
            match(END);
            func_code();
            gen_epilog_code();
            gen_data_section();
        } else {
            printf("[ERRO] Não encontrado o fim da função principal.\n");
        }
    } else {
        printf("[ERRO] Não encontrada uma função principal.\n");
    }
    if (lookahead->tag == ENDTOKEN) {
        match(ENDTOKEN);
    } else {
        printf("[ERRO] Não encontrado o fim do programa.\n");
    }
}

/**
 * @brief Regra de derivacao para declaracoes
 */
void declarations(void) {
    while ( declaration() );
}

/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration (void) {
    type_symbol_table_entry *search_symbol_var;
    type_symbol_function_entry *search_symbol_func;
    int ok1, ok2;
    char name[MAX_CHAR];
    int type;
    type = lookahead->tag;
    if ( type == INT || type == FLOAT || type == CHAR || type == STRING) { 
        match(type);
        strcpy(name, lookahead->lexema);
        search_symbol_var = sym_find( name, &global_symbol_table_variables );
        search_symbol_func = sym_func_find(name);

        if ( (search_symbol_var != NULL) ) {
            printf ("[ERRO] Variavel '%s' ja declarada.\n", name); 
            return false;
        }
        else if ( (search_symbol_func != NULL) ) {
            printf ("[ERRO] Funcao '%s' ja declarada.\n", name); 
            return false;
        } else {
            if ( match(ID) ) {
                if (lookahead->tag == SEMICOLON){
                    return declarationV(name, type);
                } else if (lookahead->tag == OPEN_PAR) {
                    return declarationF(name, type);
                } else {
                    printf("[ERRO] Nao foi possivel identificar se é variavel ou funcao.\n");
                    return false;
                }
            } else {
                printf("[ERRO] Deveria existir um ID.\n");
                return false;
            }
        }
    } else if (lookahead->tag == ENDTOKEN ||
                lookahead->tag == READ ||
                lookahead->tag == WRITE ||
                lookahead->tag == BEGIN) {
        return false;         
    } else {
        printf ("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false; 
    }
}

/**
 * @brief Regra de derivacao declaracaoV, responsavel por declarar uma variavel
 * @param var_name nome da variável
 * @param var_type tipo da variável
 * @return int true/false
 */
int declarationV(char *var_name, int var_type) {
    sym_declare( var_name, var_type, 0, &global_symbol_table_variables);
    return match(SEMICOLON); 
}

/**
 * @brief Regra de derivacao declaracaoF, responsavel por declarar uma funcao
 * @param func_name nome da função
 * @param func_type tipo da funcao
 * @return int true/false
 */
int declarationF(char *func_name, int func_type) {
    int nparams = 0;
    int ok1, ok2;
    type_symbol_table_entry params[MAX_PARAMS];

    if ( match(OPEN_PAR) ) {
        int fim = false;
        while ( (fim != true) && (nparams < MAX_PARAMS) ) {
            int var_type;
            char var_name[MAX_CHAR];
            var_type = lookahead->tag;
            if (var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING) {
                match(var_type);
                strcpy(var_name, lookahead->lexema);

                if(lookahead->tag == ID){
                    match(ID);
                    strncpy(params[nparams].name, var_name, MAX_TOKSZ);
                    params[nparams].type = var_type;
                    nparams++;

                    if (lookahead->tag == COMMA) {
                        match(COMMA);
                        if (lookahead->tag == INT || lookahead->tag == FLOAT || lookahead->tag == CHAR || lookahead->tag == STRING){
                            fim = false;
                        } else
                            fim = true;
                    } else {
                        printf("[ERRO] Esperado ',' apos a declaracao de variavel.\n");
                        return false;
                    }
                } else {
                    printf("[ERROR] Esperado ID identificador da variavel da funcao"); 
                    return false;
                }
            } else {
                fim = true;
            }
        }
    } 
    if (lookahead->tag == CLOSE_PAR) {
        ok1 = match(CLOSE_PAR);
        ok2 = match(SEMICOLON);
        if ( ok1 && ok2) {
            if (sym_func_declare(func_name, func_type, params, nparams) != NULL) 
                return true;
        }
    }
    return false;
}
 
/**
 * @brief Regra de derivacao para comandos
 */
void statements (void) {
   while ( statement() );  //processa enquanto houver comandos
}

/**
 * @brief Regra de derivacao que processa os comandos
 * 
 * @return int true/false
 */
int statement (void) {
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;
    type_symbol_table_string_entry *gen_string;
    int ok1, ok2, type;
    char string_value[MAX_CHAR];

    if (lookahead->tag == READ) {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        ok1 = match(ID);
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol != NULL) {
            type = search_symbol->type;
            gen_read(lexeme_of_id, type);
            ok2 = match(SEMICOLON);
            return ok1 && ok2;
        } else {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
            return false;
        }
    } else if (lookahead->tag == WRITE) {
        match(WRITE);
        if ( lookahead->tag == STRING ) {
            strcpy(string_value, lookahead->lexema);
            gen_string = sym_string_declare(string_value);
            match(STRING);
            if ( gen_string != NULL ) {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                match(SEMICOLON);
            }
        } else if ( lookahead->tag == ID) {
            strcpy(lexeme_of_id, lookahead->lexema);
            match(ID);
            search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
            if (search_symbol != NULL) {
                type = search_symbol->type;
                gen_write(lexeme_of_id, type);
                match(SEMICOLON);
                return true;
            } else {
                printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
                return false;
            }
        }
    } else if (lookahead->tag == IF) {
        char label_else[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_else);
        gen_label_name(label_end);

        match(IF);
        match(OPEN_PAR);
        B(); //Expressao booleana
        gen_cond_jump(label_else);
        match(CLOSE_PAR);
        
        match(BEGIN);
        statements();
        match(END);

        gen_incond_jump(label_end);
        gen_label(label_else);

        //Verifica se ocorre um ELSE
        if (lookahead->tag == ELSE) {
            match(ELSE);
            match(BEGIN);
            statements();
            match(END);
        }
        gen_label(label_end);
        return true;
    } else if (lookahead->tag == WHILE) {
        char label_begin[MAX_CHAR];
        char label_end[MAX_CHAR];
        gen_label_name(label_begin);
        gen_label_name(label_end);

        match(WHILE);
        match(OPEN_PAR);
        gen_label(label_begin);
        B(); //Expressao booleana
        gen_cond_jump(label_end);
        match(CLOSE_PAR);
        match(BEGIN);
        statements();
        match(END);
        gen_incond_jump(label_begin);
        gen_label(label_end);
        return true;
    } else if (lookahead->tag == ID) {
        char name[MAX_CHAR];
        strcpy(name, lookahead->lexema);
        int open = false;
        match(ID);
        if (lookahead->tag == ASSIGN) { 
            match(ASSIGN);
            if ( E() ) {
                match(SEMICOLON);
                return true;
            } else {
                printf("[ERRO] Atribuicao.\n");
                return false;
            }
            
        } else if (lookahead->tag == OPEN_PAR) {
            return func_call_cmd(name);
        }

    } else if ( (lookahead->tag == ENDTOKEN) || (lookahead->tag == END) ) {
        return false;
    } else {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n",lookahead->tag, lookahead->lexema);
        return false;
    }
}

int func_code(){
    char func_name[MAX_CHAR];
    strcpy(func_name, lookahead->lexema);
    match(ID);
    match(OPEN_PAR);
    match(CLOSE_PAR);
    match(BEGIN);
    statements();
    match(END);
    return true;
}

/**
 * @brief Chama uma funçao que exista
 * 
 * @param func_name nome da função
 * @return int 
 */
int func_call_cmd(char *func_name) {
    type_symbol_table_entry *search_symbol;
    type_symbol_function_entry *search_symbol_func;
    search_symbol_func = sym_func_find(func_name);
    if (search_symbol_func == NULL) {
        printf("[ERRO] A funcao chamada não existe na tabela de funcoes.\n");
        return false;
    } else {
        match(OPEN_PAR);
        int i = 0; 
        int nparams = search_symbol_func->nparams;
        while ( (lookahead->tag != CLOSE_PAR) && (i < nparams) ) {
            search_symbol = sym_find(lookahead->lexema, &global_symbol_table_variables);
            if (search_symbol == NULL) {
                printf("[ERRO] A variavel passada no parametro não foi declarada.\n");
                return false;
            } else {
                if ( search_symbol_func->params[i++].type == search_symbol->type ) {
                    match(ID);
                    match(COMMA);
                } else {
                    printf("[ERRO] Parametro não é do mesmo tipo que o declarado no protótipo.\n");
                    return false;
                }
            }
        }
        return ( match(CLOSE_PAR) ) && ( match(SEMICOLON) );
    }
}

/**
 * @brief Regra de derivação que analiza expressoes booleanas
 *        no padrao 'id op_rel expr'
 * 
 */
int B() {
    int operator;
    if ( (lookahead->tag == ID) || (lookahead->tag == NUM) ) {
        match(lookahead->tag);  
    } else if (lookahead->tag == '(') {
        E();
    } else {
        printf("[ERRO] ID, número ou expressão aritmética não experada\n");
        return false;
    }

    if (boolOperator(&operator)) {
        if ( (lookahead->tag == ID) || (lookahead->tag == NUM) ) {
            match(lookahead->tag);
            gen_bool(operator);
            return true;
        } else if (lookahead->tag == '(') {
            E();
            gen_bool(operator);
            return true;
        } else {
            printf("[ERRO] ID, número ou expressão aritmética não experada\n");
            return false;
        }
    }
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
        printf("[ERRO] Operador relacional experado.\n");
        return false;
    }
}

int E() {
    int b1, b2;
    b1 = T();
    if (b1) 
        b2 = ER();
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
    } else if (lookahead -> tag == ENDTOKEN) {
        return true;
    } else if (lookahead -> tag == '*') {
        return true;
    } else if (lookahead -> tag == '/') {
        return true;
    } else if (lookahead -> tag == SEMICOLON) {
        return true;
    }  else if (lookahead -> tag == COMMA) {
        return true;
    } else {
        return false;
    }
}

int T() {
    int b1, b2;
    b1 = F();
    if (b1)
        b2 = TR();
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
    } else if (lookahead->tag == ENDTOKEN){ //EOF
        return true;
    } else if (lookahead->tag == '+') {
        return true;
    } else if (lookahead->tag == '-') {
        return true;
    } else if (lookahead->tag == SEMICOLON) {
        return true;
    } else if (lookahead -> tag == COMMA) {
        return true;
    } else {
        return false;
    }
}

int F() {
    type_symbol_table_entry *search_symbol;
    if (lookahead->tag == '(') {
        int b1,b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    } else if (lookahead->tag == NUM) {
        int b1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        b1 = match(NUM); //substituir 'id' por NUM
        genNum(lexema);
        return b1;
    }
    else if (lookahead->tag == ID) {
        search_symbol =  sym_find(lookahead->lexema, &global_symbol_table_variables);
        if (search_symbol != NULL) {
            if ( (search_symbol->type == INT) || (search_symbol->type == FLOAT) ) {
                match(ID);
                return true;
            }  
        } else {
            printf("[ERRO] Variavel usada na expressao aritmetica nao existe.\n");
            return false;
        }
    }
    else {
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

    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    if (argc != 2) {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }
    
    initLex(argv[1]);
    lookahead = getToken();

    //Abre o arquivo de saida 
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    program();
    fclose(output_file);
    printTSFunction();
    return 0;
}