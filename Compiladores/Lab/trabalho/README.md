# Compilador C Simplificado

**Autores:** Wesley Antonio Junior dos Santos, Lucas Barbosa Amaral  
**RGA:** 202011722024, 202111722037  
**Instituição:** UFMT - Universidade Federal de Mato Grosso  
**Disciplina:** Laboratório de Compiladores

### Funcionalidades Implementadas

- **Análise Léxica Completa**: Reconhecimento de tokens, palavras-chave, operadores e literais
- **Análise Sintática**: Parser LR(1) com tratamento de precedência e associatividade
- **Análise Semântica**: Verificação de tipos, declarações e escopo
- **Geração de Código**: Tradução para assembly x86-64 executável
- **Gerenciamento de Escopo**: Suporte a múltiplos níveis de escopo (global, função, bloco)
- **Sistema de Tipos**: Suporte a tipos primitivos (int, float, char, bool, string)
- **Funções**: Protótipos, implementação, parâmetros e valores de retorno
- **Estruturas de Controle**: Condicionais (if/else) e laços (while)
- **I/O**: Operações de leitura (read) e escrita (write)
- **Tratamento de Erros**: Detecção e reporte de erros

## Arquitetura do Compilador

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Código Fonte  │ -> │ Analisador      │ -> │ Analisador      │
│   (.txt)        │    │ Léxico (Flex)   │    │ Sintático(Bison)│
└─────────────────┘    └─────────────────┘    └─────────────────┘
                                                        |
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│ Assembly x86-64 │ <- │ Gerador de      │ <- │ Analisador      │
│   (.asm)        │    │ Código          │    │ Semântico       │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

## Estrutura de Arquivos

```
trabalho/
├── lex.l                  # Especificação do analisador léxico
├── parser.y               # Gramática e analisador sintático
├── main.c                 # Programa principal
├── symbolTable.h/.c       # Tabela de símbolos e escopo
├── codeGeneration.h/.c    # Gerador de código assembly
├── errorHandler.h/.c      # Sistema de tratamento de erros
├── Makefile              # Script de compilação
├── teste.txt             # Arquivo de teste
└── compiler              # Executável (gerado)
```

## Gramática da Linguagem

### Estrutura Geral

```bnf
programa ::= declaracoes_e_funcoes

declaracoes_e_funcoes ::= item_declaracao declaracoes_e_funcoes
                       | ε

item_declaracao ::= declaracao
                 | prototipo_funcao
                 | implementacao_funcao
```

### Declarações de Variáveis

```bnf
declaracao ::= declaracao_inteiro
            | declaracao_float
            | declaracao_char
            | declaracao_bool
            | declaracao_string

declaracao_inteiro ::= 'int' ID ';'
                    | 'int' ID '=' NUM ';'
                    | 'int' ID '=' expressao ';'

declaracao_float ::= 'float' ID ';'
                  | 'float' ID '=' FLOAT_NUM ';'
                  | 'float' ID '=' NUM ';'
                  | 'float' ID '=' expressao ';'

declaracao_char ::= 'char' ID ';'
                 | 'char' ID '=' CHAR_LITERAL ';'
                 | 'char' ID '=' expressao ';'

declaracao_bool ::= 'bool' ID ';'
                 | 'bool' ID '=' TRUE_VAL ';'
                 | 'bool' ID '=' FALSE_VAL ';'
                 | 'bool' ID '=' expressao ';'

declaracao_string ::= 'string' ID ';'
                   | 'string' ID '=' LITERAL_STR ';'
                   | 'string' ID '=' expressao ';'
```

### Funções

```bnf
prototipo_funcao ::= tipo ID '(' lista_parametros ')' ';'
                  | tipo ID '(' ')' ';'

implementacao_funcao ::= tipo ID '(' lista_parametros ')' bloco
                      | tipo ID '(' ')' bloco

lista_parametros ::= parametro
                  | lista_parametros ',' parametro

parametro ::= tipo ID

tipo ::= 'int' | 'float' | 'char' | 'bool' | 'string'
```

### Comandos e Estruturas de Controle

```bnf
bloco ::= '{' lista_instrucoes '}'
       | '{' '}'

lista_instrucoes ::= instrucao lista_instrucoes
                  | ε

instrucao ::= declaracao
           | comando

comando ::= comando_atribuicao
         | comando_io
         | comando_condicional
         | comando_repeticao
         | comando_retorno
         | chamada_funcao

comando_atribuicao ::= ID '=' expressao ';'

comando_io ::= 'read' '(' ID ')' ';'
            | 'write' '(' expressao ')' ';'
            | 'write' '(' LITERAL_STR ')' ';'

comando_condicional ::= 'if' '(' expressao_logica ')' bloco
                     | 'if' '(' expressao_logica ')' bloco 'else' bloco

comando_repeticao ::= 'while' '(' expressao_logica ')' bloco

comando_retorno ::= 'return' expressao ';'

chamada_funcao ::= ID '(' lista_expressoes ')' ';'
                | ID '(' ')' ';'
```

### Expressões e Operadores

```bnf
expressao ::= termo
           | expressao '+' expressao
           | expressao '-' expressao
           | expressao '*' expressao
           | expressao '/' expressao
           | expressao '%' expressao
           | '-' expressao
           | '(' expressao ')'

termo ::= NUM | FLOAT_NUM | CHAR_LITERAL | TRUE_VAL | FALSE_VAL
       | LITERAL_STR | ID
       | ID '(' lista_expressoes ')'
       | ID '(' ')'

expressao_logica ::= expressao '<' expressao
                  | expressao '>' expressao
                  | expressao '<=' expressao
                  | expressao '>=' expressao
                  | expressao '==' expressao
                  | expressao '!=' expressao
                  | expressao_logica '&&' expressao_logica
                  | expressao_logica '||' expressao_logica
                  | '!' expressao_logica
                  | '(' expressao_logica ')'
                  | TRUE_VAL | FALSE_VAL | ID

lista_expressoes ::= expressao
                  | lista_expressoes ',' expressao
```

### Tokens Léxicos

```bnf
ID ::= [A-Za-z]([A-Za-z]|[0-9]|_)*
NUM ::= [0-9]+
FLOAT_NUM ::= [0-9]+\.[0-9]+
LITERAL_STR ::= \"[^\"]*\"
CHAR_LITERAL ::= '.'
TRUE_VAL ::= 'true'
FALSE_VAL ::= 'false'
```

## Precedência e Associatividade

```c
%left OR                    // Menor precedência
%left AND
%right '!'
%left '<' '>' LE GE EQ NE   // Operadores de comparação
%left '+' '-'               // Adição e subtração
%left '*' '/' '%'           // Multiplicação, divisão e módulo
%right UMINUS               // Menos unário
%right '='                  // Atribuição
%left ';'
%nonassoc THEN
%nonassoc ELSE              // Maior precedência
```

**Wesley Antonio Junior dos Santos & Lucas Barbosa Amaral** - UFMT 2024
