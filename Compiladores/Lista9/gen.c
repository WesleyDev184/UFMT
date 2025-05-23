/**
 * @file gen.c
 * @author Ivairton M. Santos - UFMT - Computacao
 * @brief Codificacao do modulo gerador de codigo
 * @version 0.2
 * @date 2022-02-23
 *
 */

// Inclusao do cabecalho
#include "gen.h"

// Inclusao explicita de variaveis globais de outro contexto (symbols.h)
extern type_symbol_table_variables global_symbol_table_variables;
extern type_symbol_table_string symbol_table_string;
char output_file_name[MAX_CHAR];
FILE *output_file;

/**
 * @brief Funcao que gera codigo de montagem para SOMA
 *
 */
void genAdd()
{
    fprintf(output_file, "\n\t;Adicao\n");
    fprintf(output_file, "\n\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\tadd rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para SUBTRACAO
 *
 */
void genSub()
{
    fprintf(output_file, "\n\t;Subtracao\n");
    fprintf(output_file, "\n\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tsub rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para MULTIPLICACAO
 *
 */
void genMult()
{
    fprintf(output_file, "\n\t;Multiplicacao\n");
    fprintf(output_file, "\n\tpop rax\n");
    fprintf(output_file, "\tpop rbx\n");
    fprintf(output_file, "\timult rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para DIVISAO
 *
 */
void genDiv()
{
    fprintf(output_file, "\n\t;Divisao\n");
    fprintf(output_file, "\n\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    fprintf(output_file, "\tidiv rax,rbx\n");
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento de NUMERAL
 *
 * @param num_string
 */
void genNum(char num_string[MAX_TOKEN])
{
    fprintf(output_file, "\n\t;Armazenamento de numero\n");
    fprintf(output_file, "\n\tmov rax,%s\n", num_string);
    fprintf(output_file, "\tpush rax\n");
}

/**
 * @brief Funcao que gera codigo de montagem para armazenamento do valor de uma variavel
 *
 *
 */

void genId(char *lexeme_of_id)
{
    fprintf(output_file, "\n\t;Armazenamento de valor de variavel\n");
    fprintf(output_file, "\n\tpush qword [%s]\n", lexeme_of_id);
}

/**
 * @brief Funcao que gera um preambulo que permite o uso das funcoes do C (scanf e printf)
 *
 */
void gen_preambule(void)
{
    fprintf(output_file, ";UFMT-Compiladores\n");
    fprintf(output_file, ";Prof. Ivairton\n");
    fprintf(output_file, ";Procedimento para geracao do executavel apos compilacao (em Linux):\n");
    fprintf(output_file, ";(1) compilacao do Assembly com nasm: $ nasm -f elf64 <nome_do_arquivo>\n");
    fprintf(output_file, ";(2) likedicao: $ ld -m elf_x86_64 <nome_arquivo_objeto>\n\n");
    fprintf(output_file, "extern printf\n");
    fprintf(output_file, "extern scanf\n");
    fprintf(output_file, "extern exit\n");
}

/**
 * @brief Funcao que gera codigo da secao de dados (declaracao de variaveis).
 */
void gen_data_section(void)
{
    int i, n;

    fprintf(output_file, "section .data\n");

    // emite strings de formato fixo
    // fprintf(output_file, "str0: db \"%%d\",13,10,0\n");
    // fprintf(output_file, "str1: db \"%%s\",13,10,0\n");
    // fprintf(output_file, "str2: db \"%%c\",13,10,0\n");
    // fprintf(output_file, "str3: db \"%%lf\",13,10,0\n");
    // fprintf(output_file, "\n");
    fprintf(output_file, "\tfmt_input_int db \"%%d\", 0\n");
    fprintf(output_file, "\tfmt_output_int db \"%%d\", 10, 0\n");
    fprintf(output_file, "\tfmt_input_float db \"%%lf\", 0\n");
    fprintf(output_file, "\tfmt_output_float db \"%%lf\", 10, 0\n");
    fprintf(output_file, "\tfmt_input_char db \"%%c\", 0\n");
    fprintf(output_file, "\tfmt_output_char db \"%%c\", 10, 0\n");
    fprintf(output_file, "\tfmt_input_string db \"%%s\", 0\n");
    fprintf(output_file, "\tfmt_output_string db \"%%s\", 10, 0\n");
    fprintf(output_file, "\n");

    // processa cada simbolo da tabela de strings
    // n = symbol_table_string.n_strings;
    // for (i = 0; i < n; i++) {
    //    fprintf(output_file, "%s: db %s, 0\n",
    //        symbol_table_string.string[i].name,
    //        symbol_table_string.string[i].value);
    //}
    // fprintf(output_file,"\n");

    // processa cada simbolo da tabela e gera um ponteiro para cada variavel na memoria
    n = global_symbol_table_variables.n_variables;
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "\t;%s: ", global_symbol_table_variables.variable[i].name);

        switch (global_symbol_table_variables.variable[i].type)
        { // Por enquanto gera endereco zero
        case INT:
            fprintf(output_file, "dd \"%%d\", 4\n");
            break;
        case STRING:
            fprintf(output_file, "db \"                \" \n");
            break;
        case FLOAT:
            fprintf(output_file, "dd \"%%lf\", 16\n");
            break;
        case CHAR:
            fprintf(output_file, "dd \"%%c\", 1\n");
            break;
        default:
            fprintf(output_file, "[ERRO] Tipo desconhecido.\n");
            break;
        }
    }

    n = symbol_table_string.n_strings;
    for (i = 0; i < n; i++)
    {
        fprintf(output_file, "\t%s: db %s, 0\n",
                symbol_table_string.string[i].name,
                symbol_table_string.string[i].value);
    }
}

/**
 * @brief Funcao que gera bss section
 *
 */

void gen_bss_section(void)
{
    int n;

    fprintf(output_file, "\nsection .bss\n");

    n = global_symbol_table_variables.n_variables;
    for (int i = 0; i < n; i++)
    {
        if (global_symbol_table_variables.variable[i].type == INT)
        {
            fprintf(output_file, "\t%s: resd 1\n", global_symbol_table_variables.variable[i].name);
        }
        else if (global_symbol_table_variables.variable[i].type == STRING)
        {
            fprintf(output_file, "\t%s: resb 256\n", global_symbol_table_variables.variable[i].name);
        }
        else if (global_symbol_table_variables.variable[i].type == FLOAT)
        {
            fprintf(output_file, "\t%s: resq 1\n", global_symbol_table_variables.variable[i].name);
        }
        else if (global_symbol_table_variables.variable[i].type == CHAR)
        {
            fprintf(output_file, "\t%s: resb 1\n", global_symbol_table_variables.variable[i].name);
        }
        else
        {
            fprintf(output_file, "[ERRO] Tipo desconhecido.\n");
        }
    }
}

/**
 * @brief Funcao que gera a marcacao do inicio da secao de codigo
 *
 */
void gen_preambule_code(void)
{
    fprintf(output_file, "\nsection .text\n");
    fprintf(output_file, "\tglobal main\n");
    fprintf(output_file, "\nmain:");
}

/**
 * @brief Funcao que encerra o codigo inserindo comandos de fechamento
 *
 */
void gen_epilog_code(void)
{
    // fprintf(output_file, "\nret\n");
    fprintf(output_file, "\n;encerra programa\n");
    fprintf(output_file, "\n.exit:\n");
    fprintf(output_file, "\tmov rdi, 0\n");
    fprintf(output_file, "\tcall exit\n");
    fprintf(output_file, "\n");
}

/**
 * @brief Funcao que gera automaticamente um novo nome para um label
 * @param string name
 */
void gen_label_name(char *name)
{
    char str_name[MAX_CHAR];
    char conv_value[16];
    static int nlabels = 0;

    sprintf(conv_value, "%d", nlabels);
    strcpy(str_name, "label");
    strcat(str_name, conv_value);
    strcpy(name, str_name);
    nlabels++;
}

/**
 * @brief Funcao que registra no codigo um label
 * @param string label
 */
void gen_label(char *label)
{
    fprintf(output_file, "%s:\n", label);
}

/**
 * @brief Funcao que gera um jump condicional
 * @param string label
 */
void gen_cond_jump(char *label)
{
    fprintf(output_file, "\n\t;jump condicional\n");
    fprintf(output_file, "\n\tpop rax\n");
    fprintf(output_file, "\tcmp rax, 0\n");
    fprintf(output_file, "\tjz %s\n", label);
}

/**
 * @brief Funcao que gera um jump incondicional
 * @param string label
 */
void gen_incond_jump(char *label)
{
    fprintf(output_file, "\n\t;jump incondicional\n");
    fprintf(output_file, "\n\tjmp %s\n", label);
}

/**
 * @brief Gera código para o operador lógico AND (&&)
 */
void gen_and(void)
{
    fprintf(output_file, "\n\t;Operador lógico AND");
    fprintf(output_file, "\n\tpop rbx");
    fprintf(output_file, "\n\tpop rax");
    fprintf(output_file, "\n\tand rax, rbx");
    fprintf(output_file, "\n\tpush rax");
}

/**
 * @brief Gera código para o operador lógico OR (||)
 */
void gen_or(void)
{
    fprintf(output_file, "\n\t;Operador lógico OR");
    fprintf(output_file, "\n\tpop rbx");
    fprintf(output_file, "\n\tpop rax");
    fprintf(output_file, "\n\tor rax, rbx");
    fprintf(output_file, "\n\tpush rax");
}

/**
 * @brief Funcao que gera codigo a partir do processamento da expressao logica
 *
 * @param oper
 */
void gen_bool(int oper)
{
    static int bool_label;
    char bool_label_name[MAX_CHAR];
    fprintf(output_file, "\n\t;Aplica operador booleano/exp.logica\n");
    fprintf(output_file, "\n\tpop rbx\n");
    fprintf(output_file, "\tpop rax\n");
    gen_bool_label_name(bool_label_name);
    fprintf(output_file, "\tmov rcx,1\n");
    fprintf(output_file, "\tcmp eax,ebx\n");

    switch (oper)
    {
    case EQUAL:
        fprintf(output_file, "\tje %s\n", bool_label_name);
        break;
    case NE:
        fprintf(output_file, "\tjne %s\n", bool_label_name);
        break;
    case ARROWLEFT:
        fprintf(output_file, "\tjl %s\n", bool_label_name);
        break;
    case ARROWRIGHT:
        fprintf(output_file, "\tjg %s\n", bool_label_name);
        break;
    case LE:
        fprintf(output_file, "\tjle %s\n", bool_label_name);
        break;
    case GE:
        fprintf(output_file, "\tjge %s\n", bool_label_name);
        break;
    default:
        printf("[ERRO] operador booleano nao suportado.\n");
        break;
    }
    fprintf(output_file, "\tmov rcx, 0\n\n");
    gen_label(bool_label_name);
    fprintf(output_file, "\n\tmov rax, rcx\n");
    fprintf(output_file, "\tpush rax\n");
}

void gen_bool_label_name(char *name)
{
    static int nbool_labels = 0;
    sprintf(name, "label_bool_%d", nbool_labels);
    nbool_labels++;
}

/**
 * @brief Funcao que gera codigo para armazenar o valor de uma variavel na pilha
 *
 * @param var Nome da variavel a ser armazenada na pilha
 */
void gen_store_on_stack(const char *var)
{
    fprintf(output_file, "\n\t;Armazenamento do valor da variavel %s na pilha\n", var);
    fprintf(output_file, "\tpush qword [%s]\n", var);
}

void gen_assign(char *id)
{
    fprintf(output_file, "\n\t;Atribuicao de valor a variavel %s\n", id);
    fprintf(output_file, "\n\tpop rax\n");
    fprintf(output_file, "\tmov [ %s ], rax\n", id);
}

/**
 * @brief Gera codigo para o comando READ
 *
 * @param lexeme_of_id nome do identificador
 */
void gen_read(char *lexeme_of_id, int type)
{
    /*
    //Codigo antigo, demanda estudo para ser usado com o liker GCC no Linux
    fprintf(output_file, "mov rdi, fmtstr0\n");
    fprintf(output_file, "mov rsi, %s\n", lexeme_of_id);
    fprintf(output_file, "mov rax, 0\n");
    fprintf(output_file, "call scanf\n");
    */
    switch (type)
    {
    case INT:
        fprintf(output_file, "\n\t;le valor inteiro\n");
        fprintf(output_file, "\n\tmov rdi, fmt_input_int\n");
        fprintf(output_file, "\tlea rsi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall scanf\n");
        break;
    case FLOAT:
        fprintf(output_file, "\n\t;le valor float\n");
        fprintf(output_file, "\n\tmov rdi, fmt_input_float\n");
        fprintf(output_file, "\tlea rsi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall scanf\n");
        break;
    case CHAR:
        fprintf(output_file, "\n\t;le valor char\n");
        fprintf(output_file, "\n\tmov rdi, fmt_input_char\n");
        fprintf(output_file, "\tlea rsi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall scanf\n");
        break;
    case STRING:
        fprintf(output_file, "\n\t;le valor string\n");
        fprintf(output_file, "\n\tmov rdi, fmt_input_string\n");
        fprintf(output_file, "\tlea rsi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall scanf\n");
        break;
    }
}

/**
 * @brief Gera codigo para o comando WRITE
 *
 * @param lexeme_of_id nome do identificador
 */
void gen_write(char *lexeme_of_id, int type)
{
    /*
    //Codigo antigo, demanda estudo para ser usado com o liker GCC no Linux
    fprintf(output_file, "mov rdi, fmtstr0\n");
    fprintf(output_file, "mov rsi, [rel %s]\n", lexeme_of_id);
    fprintf(output_file, "mov rax, 0\n");
    fprintf(output_file, "call printf\n");
    */
    switch (type)
    {
    case INT:
        fprintf(output_file, "\n\t;escreve valor inteiro\n");
        fprintf(output_file, "\n\tmov rdi, fmt_output_int\n");
        fprintf(output_file, "\tmov esi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall printf\n");
        break;
    case FLOAT:
        fprintf(output_file, "\n\t;escreve valor float\n");
        fprintf(output_file, "\n\tmov rdi, fmt_output_float\n");
        fprintf(output_file, "\tmovq xmm0, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\tmov eax, 1\n");
        fprintf(output_file, "\tcall printf\n");
        break;
    case CHAR:
        fprintf(output_file, "\n\t;escreve valor char\n");
        fprintf(output_file, "\n\tmov rdi, fmt_output_char\n");
        fprintf(output_file, "\tmov esi, [%s]\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall printf\n");
        break;
    case STRING:
        fprintf(output_file, "\n\t;escreve valor string\n");
        fprintf(output_file, "\n\tmov rdi, fmt_output_string\n");
        fprintf(output_file, "\tmov rsi, %s\n", lexeme_of_id);
        fprintf(output_file, "\txor eax, eax\n");
        fprintf(output_file, "\tcall printf\n");
        break;
    }
}