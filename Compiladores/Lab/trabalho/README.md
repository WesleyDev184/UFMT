# Compilador C Simplificado

**Autor:** Wesley Antonio Junior dos Santos  
**RGA:** 202011722024  
**Instituição:** UFMT - Universidade Federal de Mato Grosso  
**Disciplina:** Laboratório de Compiladores

## 📋 Descrição do Projeto

Este projeto implementa um compilador completo para uma linguagem C simplificada, capaz de traduzir código fonte em linguagem de alto nível para código assembly x86-64. O compilador foi desenvolvido utilizando as ferramentas **Flex** (analisador léxico) e **Bison** (analisador sintático), implementando todas as fases de compilação: análise léxica, sintática, semântica e geração de código.

## 🎯 Características Principais

### ✅ Funcionalidades Implementadas

- **Análise Léxica Completa**: Reconhecimento de tokens, palavras-chave, operadores e literais
- **Análise Sintática**: Parser LR(1) com tratamento de precedência e associatividade
- **Análise Semântica**: Verificação de tipos, declarações e escopo
- **Geração de Código**: Tradução para assembly x86-64 executável
- **Gerenciamento de Escopo**: Suporte a múltiplos níveis de escopo (global, função, bloco)
- **Sistema de Tipos**: Suporte a tipos primitivos (int, float, char, bool, string)
- **Funções**: Protótipos, implementação, parâmetros e valores de retorno
- **Estruturas de Controle**: Condicionais (if/else) e laços (while)
- **I/O**: Operações de leitura (read) e escrita (write)
- **Tratamento de Erros**: Sistema robusto de detecção e reporte de erros

## 🏗️ Arquitetura do Compilador

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

## 📁 Estrutura de Arquivos

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

## 🔤 Gramática da Linguagem

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

## 📊 Precedência e Associatividade

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

## 🔧 Compilação e Uso

### Pré-requisitos

```bash
# Instalar dependências no Ubuntu/Debian
sudo apt-get install flex bison gcc nasm

# Instalar dependências no Fedora/CentOS
sudo yum install flex bison gcc nasm
```

### Compilação

```bash
# Compilar o compilador
make

# Compilar e executar programa de teste
make asm

# Limpar arquivos gerados
make clean
```

### Uso Manual

```bash
# Compilar arquivo fonte
./compiler programa.txt

# Ou especificar arquivo de saída
./compiler programa.txt -o programa.asm

# Gerar executável
nasm -f elf64 programa.asm -o programa.o
gcc -no-pie programa.o -o programa
./programa
```

## 📝 Exemplo de Código

```c
// Variáveis globais
float total;
float media;
bool impar;
string empresa;

// Protótipo de função
float soma(float a, float b);

// Função principal
int main() {
    string nome;
    float x, y;

    empresa = "UFMT";

    write("Digite seu nome: ");
    read(nome);
    write("Digite X: ");
    read(x);
    write("Digite Y: ");
    read(y);

    total = soma(x, y);
    media = total / 2.0;
    impar = false;

    while (total > 0.0) {
        if (impar == false) {
            impar = true;
        } else {
            impar = false;
        }
        total = total - 1.0;
    }

    write("Empresa: ");
    write(empresa);
    write("Nome: ");
    write(nome);
    write("Média: ");
    write(media);

    if (impar == true) {
        write("Número é ímpar");
    } else {
        write("Número é par");
    }

    return 0;
}

// Implementação da função
float soma(float a, float b) {
    return (a + b);
}
```

## 🎛️ Funcionalidades Avançadas

### Sistema de Escopo

- **Escopo Global**: Variáveis declaradas fora de funções
- **Escopo de Função**: Parâmetros e variáveis locais
- **Escopo de Bloco**: Variáveis em blocos if/while

### Verificação Semântica

- ✅ Verificação de tipos em operações
- ✅ Detecção de variáveis não declaradas
- ✅ Detecção de redeclaração de variáveis
- ✅ Verificação de compatibilidade em atribuições
- ✅ Validação de chamadas de função
- ✅ Verificação de existência da função main

### Geração de Código

- ✅ Assembly x86-64 otimizado
- ✅ Gerenciamento automático de pilha
- ✅ Suporte a chamadas de função
- ✅ Operações aritméticas tipo-específicas
- ✅ Estruturas de controle eficientes

## 📊 Tabelas de Símbolos

### Tabela Global

Armazena variáveis globais e informações básicas de símbolos.

### Tabela de Funções

Gerencia protótipos, implementações, parâmetros e tipos de retorno.

### Tabela com Escopo

Sistema hierárquico para resolução de nomes em diferentes escopos.

## ⚠️ Sistema de Tratamento de Erros

### Tipos de Erro

- **Erros Sintáticos**: Problemas na estrutura do código
- **Erros Semânticos**: Problemas de tipo e escopo
- **Erros de Declaração**: Variáveis/funções não declaradas
- **Erros de Tipo**: Incompatibilidade de tipos

### Relatórios de Erro

```
Error: Variable 'x' not declared at line 15
Error: Type mismatch in addition operation: cannot operate 'int' with 'string' at line 23
Error: Function 'soma' already declared at line 8
```

## 🔍 Análise de Complexidade

### Análise Léxica: O(n)

- Onde n é o tamanho do arquivo fonte

### Análise Sintática: O(n)

- Parser LR(1) com complexidade linear

### Análise Semântica: O(n × m)

- Onde m é o número médio de símbolos por escopo

### Geração de Código: O(n)

- Tradução direta com otimizações locais

## 🧪 Testes e Validação

### Casos de Teste Cobertos

- ✅ Declarações de variáveis de todos os tipos
- ✅ Funções com e sem parâmetros
- ✅ Estruturas de controle aninhadas
- ✅ Operações aritméticas e lógicas
- ✅ Tratamento de erros sintáticos e semânticos
- ✅ Geração de código assembly válido

### Execução de Testes

```bash
# Teste básico fornecido
make asm

# Testes personalizados
./compiler meu_teste.txt
nasm -f elf64 meu_teste.asm -o meu_teste.o
gcc -no-pie meu_teste.o -o meu_programa
./meu_programa
```

## 🎓 Conceitos de Compiladores Implementados

1. **Front-End**:

   - Análise Léxica (Tokenização)
   - Análise Sintática (Parsing)
   - Análise Semântica (Type Checking)

2. **Back-End**:

   - Geração de Código Intermediário
   - Otimizações Locais
   - Geração de Código Assembly

3. **Estruturas de Dados**:

   - Tabelas de Símbolos Hash
   - Árvores Sintáticas (implícitas via Bison)
   - Pilhas de Escopo

4. **Algoritmos**:
   - Hash Functions para Tabelas de Símbolos
   - Algoritmo LR(1) para Parsing
   - Algoritmos de Verificação de Tipos

## 📈 Possíveis Extensões

### Funcionalidades Futuras

- [ ] Arrays e ponteiros
- [ ] Estruturas (structs)
- [ ] Operadores de incremento/decremento
- [ ] Comando for
- [ ] Funções recursivas otimizadas
- [ ] Otimizações avançadas de código

### Melhorias Técnicas

- [ ] Geração de código intermediário
- [ ] Otimizador de expressões
- [ ] Melhor tratamento de strings
- [ ] Debugging symbols
- [ ] Análise de fluxo de dados

## 🤝 Contribuições

Este projeto foi desenvolvido como parte do curso de Compiladores da UFMT. Contribuições são bem-vindas através de issues e pull requests.

## 📜 Licença

Este projeto é desenvolvido para fins acadêmicos como parte do Laboratório de Compiladores da UFMT.

---

**Wesley Antonio Junior dos Santos** - UFMT 2024
