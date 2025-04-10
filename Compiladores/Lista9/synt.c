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
int match(int token_tag)
{
    if (lookahead->tag == token_tag)
    {
        lookahead = getToken(); // Pega o proximo token por meio do lexico
        return true;
    }
    printf("[ERRO] Entrada esperada: %s\n", lookahead->lexema);
    return false;
}

/**
 * @brief Regra de derivacao inicial
 */
int program(void)
{
    gen_preambule(); // Temporariamente cria um preambulo adicional que permite o uso das funcoes scanf e printf

    int flag = declarations();

    if (flag == false)
    {
        // printf("[ERRO] Erro na declaracao.\n");
        return false;
    }
    gen_bss_section();
    gen_preambule_code(); // Chamada do gerador de codigo para escrita do cabecalho da secao de codigo
    flag = statements();

    if (flag == false)
    {
        // printf("[ERRO] Erro nos comandos.\n");
        return false;
    }

    gen_epilog_code();
    gen_data_section(); // Chamada do gerador de codigo para declaracao de variaveis
    return true;
}

/**
 * @brief Regra de derivacao para declaracoes
 */
int declarations(void)
{
    // while ( declaration() ); //Laco para processamento continuo das declaracoes
    int sucess;
    do
    {
        sucess = declaration();
    } while (sucess == true);

    if (sucess == ERROR)
    {
        // printf("[ERRO] Erro na declaracao.\n");
        return false;
    }
    else
    {
        // printf("[SUCESSO] Declaracao realizada com sucesso.\n");
        return true;
    }
}

/**
 * @brief Regra de derivacao declaracao
 * @return int true/false
 */
int declaration(void)
{
    type_symbol_table_entry *search_symbol;
    int ok1, ok2;
    char var_name[MAX_CHAR];
    int var_type;

    // Verifica o tipo da variavel
    var_type = lookahead->tag;
    if (var_type == INT || var_type == FLOAT || var_type == CHAR || var_type == STRING)
    {
        match(var_type);
        strcpy(var_name, lookahead->lexema);
        search_symbol = sym_find(var_name, &global_symbol_table_variables);

        if (search_symbol != NULL)
        {
            printf("[ERRO] Variavel '%s' ja declarada.\n", var_name);
            return ERROR;
        }
        else
        {
            ok1 = match(ID); // Verifica se identificador vem a seguir
            if (ok1 == false)
            {
                printf("[ERRO] Faltou identificador e não foi possível registrar a variável na tabela de simbolos.\n");
                return ERROR;
            }
            ok2 = match(SEMICOLON); // Verifica se ; vem a seguir

            if (ok2 == false)
            {
                printf("[ERRO] Faltou ponto e virgula e não foi possível registrar a variável na tabela de simbolos.\n");
                return ERROR;
            }
            sym_declare(var_name, var_type, 0, &global_symbol_table_variables);

            return ok1 && ok2;
        }
    }

    else if (lookahead->tag == ENDTOKEN ||
             lookahead->tag == READ ||
             lookahead->tag == WRITE ||
             lookahead->tag == IF)
    {
        return false;
    }
    else
    {
        printf("[ERRO] Tipo desconhecido: %d %s.\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Regra de derivacao para comandos
 */
int statements(void)
{
    //    while ( statement() );  //processa enquanto houver comandos
    int sucess;
    do
    {
        sucess = statement();
    } while (sucess == true);

    if (sucess == ERROR)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief Regra de derivacao que processa os comandos
 *
 * @return int true/false
 */
int statement(void)
{
    char lexeme_of_id[MAX_CHAR];
    type_symbol_table_entry *search_symbol;
    type_symbol_table_string_entry *search_symbol_string;
    type_symbol_table_string_entry *gen_string;
    int ok1, ok2, type;
    char string_value[MAX_STRING];

    if (lookahead->tag == READ)
    {
        match(READ);
        strcpy(lexeme_of_id, lookahead->lexema);
        ok1 = match(ID);
        if (ok1 == false)
        {
            printf("[ERRO] Comando de leitura sem identificador.\n");
            return ERROR;
        }
        search_symbol = sym_find(lexeme_of_id, &global_symbol_table_variables);
        if (search_symbol != NULL)
        {
            type = search_symbol->type;
            gen_read(lexeme_of_id, type);
            // se nao receber ; eh erro
            if (lookahead->tag != SEMICOLON)
            {
                printf("[ERRO] Comando de leitura sem ponto e virgula.\n");
                return ERROR;
            }
            else
            {
                match(SEMICOLON);
                return true;
            }
        }
        else
        {
            printf("[ERRO] Simbolo desconhecido (Variavel nao declarada): %s\n", lexeme_of_id);
            return ERROR;
        }
    }
    else if (lookahead->tag == WRITE)
    {
        match(WRITE);
        if (lookahead->tag == STRING)
        {
            strcpy(string_value, lookahead->lexema);
            // TODO: verificar se o valor da constante ja foi incluida na tabela de simbolos
            search_symbol_string = sym_string_find(string_value);
            if (search_symbol_string == NULL)
            {
                gen_string = sym_string_declare(string_value);
            }
            else
            {
                gen_string = search_symbol_string;
            }

            match(STRING);
            if (gen_string != NULL)
            {
                strcpy(lexeme_of_id, gen_string->name);
                gen_write(lexeme_of_id, STRING);
                // se nao receber ; eh erro
                if (lookahead->tag != SEMICOLON)
                {
                    printf("[ERRO] Comando de escrita sem ponto e virgula.\n");
                    return ERROR;
                }
                else
                {
                    match(SEMICOLON);
                    return true;
                }
            }
            else
            {
                printf("[ERRO] Erro ao declarar string.\n");
                return ERROR;
            }
        }
        else if (lookahead->tag == ID)
        {
            char lexeme_of_id[MAX_CHAR];
            strcpy(lexeme_of_id, lookahead->lexema);
            match(ID);
            if (lookahead->tag == ASSIGN)
            {
                // Consome o token de atribuição
                match(ASSIGN);
                // Processa o valor (por enquanto usando a regra E para expressões aritméticas)
                int flag = E();
                if (!flag)
                {
                    printf("[ERRO] Expressao invalida na atribuicao.\n");
                    return ERROR;
                }
                // Verifica se há ponto e vírgula final
                if (lookahead->tag != SEMICOLON)
                {
                    printf("[ERRO] Atribuicao sem ponto e virgula.\n");
                    return ERROR;
                }
                else
                {
                    match(SEMICOLON);
                }
                // Gera o codigo de atribuicao
                gen_assign(lexeme_of_id);
                return true;
            }
            else
            {
                // Se não for atribuição, pode ser um uso de variavel em outra producao (ou sinal de erro)
                printf("[ERRO] Comando desconhecido apos identificador: %s\n", lexeme_of_id);
                return ERROR;
            }
        }
    }
    else if (lookahead->tag == IF)
    {
        char label_else[MAX_CHAR];
        char label_end[MAX_CHAR];
        int flag_bool;

        gen_label_name(label_else);
        gen_label_name(label_end);

        if (!match(IF))
            return ERROR;
        if (!match(OPEN_PAR))
            return ERROR;
        flag_bool = logic_expr();
        if (!flag_bool)
        {
            printf("[ERRO] Expressao booleana mal formada.\n");
            return ERROR;
        }
        if (!match(CLOSE_PAR))
            return ERROR;

        gen_cond_jump(label_else);
        if (!match(BEGIN))
            return ERROR;
        if (!statements())
            return ERROR;
        if (!match(END))
            return ERROR;

        gen_incond_jump(label_end);
        gen_label(label_else);

        if (lookahead->tag == ELSE)
        {
            if (!match(ELSE))
                return ERROR;
            if (!match(BEGIN))
                return ERROR;
            if (!statements())
                return ERROR;
            if (!match(END))
                return ERROR;
        }
        gen_label(label_end);
        return true;
    }
    else if (lookahead->tag == WHILE)
    {
        char label_start[MAX_CHAR];
        char label_end[MAX_CHAR];
        int flag_bool;

        gen_label_name(label_start);
        gen_label_name(label_end);

        // Marca o início do loop
        gen_label(label_start);
        if (!match(WHILE))
            return ERROR;
        if (!match(OPEN_PAR))
            return ERROR;

        flag_bool = logic_expr();
        if (!flag_bool)
        {
            printf("[ERRO] Expressao booleana mal formada no while.\n");
            return ERROR;
        }
        if (!match(CLOSE_PAR))
            return ERROR;

        gen_cond_jump(label_end);
        if (!match(BEGIN))
            return ERROR;
        if (!statements())
            return ERROR;
        if (!match(END))
            return ERROR;

        gen_incond_jump(label_start);
        gen_label(label_end);
        return true;
    }
    else if (lookahead->tag == ENDTOKEN || lookahead->tag == END)
    {
        return false;
    }
    else
    {
        printf("[ERRO] Comando desconhecido.\nTag=%d; Lexema=%s\n", lookahead->tag, lookahead->lexema);
        return false;
    }
}

/**
 * @brief Regra que processa expressões lógicas, permitindo o uso dos operadores '&&' e '||'
 *
 * A produção é:
 *    logic_expr -> B { (AND | OR) B }
 *
 * @return int true/false conforme o processamento sintático
 */
int logic_expr(void)
{
    int flag = B();
    while (lookahead->tag == AND || lookahead->tag == OR)
    {
        int op = lookahead->tag;
        match(op);
        int flag2 = B();
        if (!flag2)
        {
            flag = false;
        }
        // Gera o código adequado para o operador lógico
        if (op == AND)
        {
            gen_and();
        }
        else // OR
        {
            gen_or();
        }
    }
    return flag;
}

/**
 * @brief Regra de derivação que analisa expressoes booleanas
 *        no padrao '[id | expr] op_rel [id | expr]'
 *
 */
int B()
{
    int operator, flag_left, flag_right;
    int expression = false;
    char id_lexeme[MAX_CHAR]; // buffer para armazenar o lexema do id

    if (lookahead->tag == ID)
    {
        strcpy(id_lexeme, lookahead->lexema);
        genId(id_lexeme);
        match(ID);
        // Armazena o valor da variável na pilha de memória
        gen_store_on_stack(id_lexeme);
        if (boolOperatorVerify() == false)
        {
            return false;
        }
        flag_left = true;
    }
    else
    {
        flag_left = E();
        expression = true;
    }

    if (!flag_left)
    {
        return false;
    }

    // Verifica se há um operador relacional
    if ((expression && boolOperatorVerify()) || (!expression))
    {
        if (boolOperator(&operator))
        {
            if (lookahead->tag == ID)
            {
                strcpy(id_lexeme, lookahead->lexema);
                genId(id_lexeme);
                match(ID);
                // Armazena também o valor da variável do lado direito
                gen_store_on_stack(id_lexeme);
                flag_right = true;
            }
            else
            {
                flag_right = E();
            }

            if (!flag_right)
            {
                return false;
            }
            // Gera código para a comparação booleana
            gen_bool(operator);
            return true;
        }
    }

    // Se não houver operador relacional, aceita apenas a expressão aritmética
    return true;
}

int processExpression()
{
    if (lookahead->tag == ID)
    {
        genId(lookahead->lexema);
        int flag = match(ID);
        // verifica se prox token é um operador relacional
        if (boolOperatorVerify())
        {
            return flag;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return E();
    }
}

int boolOperator(int *operator)
{
    int lookahead_tag;
    lookahead_tag = lookahead->tag;
    *operator= - 1;

    if (lookahead_tag == ASSIGN ||
        lookahead_tag == NE ||
        lookahead_tag == ARROWLEFT ||
        lookahead_tag == ARROWRIGHT ||
        lookahead_tag == LE ||
        lookahead_tag == GE)
    {
        *operator= lookahead_tag;
        match(lookahead_tag);
        return true;
    }
    else
    {
        printf("[ERRO] Operador relacional esperado.\n");
        return false;
    }
}

int boolOperatorVerify()
{
    int lookahead_tag = lookahead->tag;

    if (lookahead_tag == ASSIGN ||
        lookahead_tag == NE ||
        lookahead_tag == ARROWLEFT ||
        lookahead_tag == ARROWRIGHT ||
        lookahead_tag == LE ||
        lookahead_tag == GE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//------
/* Funções que representam a gramatica que reconhece expressoes aritmeticas */
/* Elaborada nas primeiras aulas */
int E()
{
    int b1, b2;
    b1 = T();
    if (b1)
    {
        b2 = ER();
    }
    return b1 && b2;
}

int ER()
{
    if (lookahead->tag == '+')
    {
        int b1, b2;
        match('+');
        b1 = T();
        genAdd();
        if (b1)
            b2 = ER();
        return b1 && b2;
    }
    else if (lookahead->tag == '-')
    {
        int b1, b2;
        match('-');
        b1 = T();
        genSub();
        if (b1)
            b2 = ER();
        return b1 && b2;
    }
    else if (lookahead->tag == ')')
    {
        return true;
    }
    else if (lookahead->tag == ENDTOKEN || boolOperatorVerify())
    {
        return true;
    }
    else if (lookahead->tag == '*')
    {
        return true;
    }
    else if (lookahead->tag == '/')
    {
        return true;
    }
    else
    {
        printf("[ERRO] Operador aritmetico esperado.\n");
        return false;
    }
}

int T()
{
    int b1, b2;
    b1 = F();
    if (b1)
        b2 = TR();
    return b1 && b2;
}

int TR()
{
    if (lookahead->tag == '*')
    {
        int b1, b2;
        match('*');
        b1 = F();
        genMult();
        if (b1)
            b2 = TR();
        return b1 && b2;
    }
    else if (lookahead->tag == '/')
    {
        int b1, b2;
        match('/');
        b1 = F();
        genDiv();
        if (b1)
            b2 = TR();
        return b1 && b2;
    }
    else if (lookahead->tag == ')')
    {
        return true;
    }
    else if (lookahead->tag == ENDTOKEN || boolOperatorVerify())
    { // EOF
        return true;
    }
    else if (lookahead->tag == '+')
    {
        return true;
    }
    else if (lookahead->tag == '-')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int F()
{
    if (lookahead->tag == '(')
    {
        int b1, b2;
        match('(');
        b1 = E();
        if (b1)
            b2 = match(')');
        return b1 && b2;
    }
    else if (lookahead->tag == NUM)
    {
        int b1;
        char lexema[MAX_TOKEN];
        strcpy(lexema, lookahead->lexema);
        b1 = match(NUM); // substituir 'id' por NUM
        genNum(lexema);
        return b1;
    }
    else
    {
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
int main(int argc, char *argv[])
{
    int sucess;

    // Inicializa a tabela de simbolo global
    initSymbolTableVariables(&global_symbol_table_variables);
    initSymbolTableString();

    // Verifica a passagem de parametro
    if (argc != 2)
    {
        printf("[ERRO]\n\tÉ necessário informar um arquivo de entrada (código) como parâmetro.\n\n");
        exit(EXIT_FAILURE);
    }

    initLex(argv[1]);       // Carrega codigo
    lookahead = getToken(); // Inicializacao do lookahead

    // Abre o arquivo de saida
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, ".asm");
    output_file = fopen(output_file_name, "w+");

    sucess = program(); // Chamada da derivacao/funcao inicial da gramatica

    if (sucess == true)
    {
        printf("[SUCESSO] Compilacao realizada com sucesso.\n");
        // imprime a tabela de simbolos
        printSTVariables(&global_symbol_table_variables);

        printf("\n\n");
        printSTString();
    }
    else
    {
        printf("[ERRO] Erro na compilacao.\n");
    }

    fclose(output_file);
    return 1;
}