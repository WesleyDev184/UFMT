/**
 * @file synt.c
 * @brief Codificacao do modulo do analisador sintatico
 * @version 0.1
 * @date 2021-11-24
 * 
 */

// Inclusao do cabecalho
#include "synt.h"

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
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: EXPRESSION
 * EXPRESSION -> TERM EXPRESSION_R
 * 
 * @return int true/false
 */
 int expression() {
    if ( term() && expressionR() )
        return true;
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: EXPRESSION_R
 * EXPRESSION_R -> '+' TERM EXPRESSION_R
 *                | '-' TERM EXPRESSION_R
 *                | ε
 * 
 * @return int true/false
 */
int expressionR() {
    int test1, test2;
    if ( lookahead->tag == PLUS ) {
        test1 = match(PLUS);
        test2 = term();
        genAdd();
        if ( test1 && test2 && expressionR() )
            return true;
        return false;
    }
    else if ( lookahead->tag == MINUS ) {
        test1 = match(MINUS);
        test2 = term();
        genSub();
        if ( test1 && test2 && expressionR() )
            return true;
        return false;
    }
    // Epsilon producao
    return true;
}

/**
 * @brief Regra de derivacao da gramatica: TERM
 * TERM -> digit() TERM_R
 * 
 * @return int true/false
 */
int term() {
    if ( digit() && termR() )
        return true;
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: TERM_R
 * TERM_R -> '*' digit() TERM_R
 *            | '/' digit() TERM_R
 *            | ε
 * 
 * @return int true/false
 */
int termR() {
    int test1, test2;
    if ( lookahead->tag == MULT ) {
        test1 = match(MULT);
        test2 = digit();
        genMult();
        if ( test1 && test2 && termR() )
            return true;
        return false;
    }
    else if ( lookahead->tag == DIV ) {
        test1 = match(DIV);
        test2 = digit();
        genDiv();
        if ( test1 && test2 && termR() )
            return true;
        return false;
    }
    // Epsilon producao
    return true;
}

/**
 * @brief Regra de derivacao da gramatica: LIST (Entrada)
 * LIST -> EXPRESSION ENDTOKEN
 * 
 * @return int true/false
 */
int list() {
    if ( expression() && lookahead->tag == ENDTOKEN )
        return true;
    return false;
}

/**
 * @brief Regra de derivacao da gramatica: DIGIT
 * 
 * @return int true/false
 */
int digit() {
    char aux_lexema[MAX_TOKEN];
    strcpy(aux_lexema, lookahead->lexema); //armazena temporariamente o lexema

    if ( match(NUM) ) {
        genNum(aux_lexema); //Geracao de codigo por meio de funcao do GERADOR
        return true;
    }
    return false;
}