/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

// Inclusão de bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura da árvore de caracteres em código Morse
typedef struct morseCharacterTree
{
  char character;                  // Caractere representado pelo nó
  struct morseCharacterTree *dot;  // Ponteiro para o filho que representa o ponto '.'
  struct morseCharacterTree *dash; // Ponteiro para o filho que representa o traço '-'
} MorseCharacterTree;

// Função para criar um nó na árvore com o caractere fornecido
MorseCharacterTree *createMorseCharacterTree(char character)
{
  // Aloca memória para o nó
  MorseCharacterTree *morseCharacterTree = (MorseCharacterTree *)malloc(sizeof(MorseCharacterTree));

  // Define o caractere representado pelo nó
  morseCharacterTree->character = character;

  // Inicializa os ponteiros para os filhos como NULL
  morseCharacterTree->dot = NULL;
  morseCharacterTree->dash = NULL;

  return morseCharacterTree;
}

// Função para inserir um caractere na árvore com o seu código Morse
MorseCharacterTree *insertMorseCharacterTree(MorseCharacterTree *morseCharacterTree, char *morseCode, char character)
{
  // Se a árvore está vazia, cria um nó com o caractere fornecido
  if (morseCharacterTree == NULL)
  {
    morseCharacterTree = createMorseCharacterTree(character);
  }
  // Se o código Morse começa com '.', insere o caractere no filho representado pelo ponto
  else if (*morseCode == '.')
  {
    morseCharacterTree->dot = insertMorseCharacterTree(morseCharacterTree->dot, morseCode + 1, character);
  }
  // Se o código Morse começa com '-', insere o caractere no filho representado pelo traço
  else if (*morseCode == '-')
  {
    morseCharacterTree->dash = insertMorseCharacterTree(morseCharacterTree->dash, morseCode + 1, character);
  }

  return morseCharacterTree;
}

// Função para buscar um caractere na árvore pelo seu código Morse
MorseCharacterTree *searchMorseCharacterTree(MorseCharacterTree *morseCharacterTree, char *morseCode)
{
  // Se a árvore está vazia, retorna NULL
  if (morseCharacterTree == NULL)
  {
    return NULL;
  }
  // Se o código Morse começa com '.', busca o caractere no filho representado pelo ponto
  else if (*morseCode == '.')
  {
    return searchMorseCharacterTree(morseCharacterTree->dot, morseCode + 1);
  }
  // Se o código Morse começa com '-', busca o caractere no filho representado pelo traço
  else if (*morseCode == '-')
  {
    return searchMorseCharacterTree(morseCharacterTree->dash, morseCode + 1);
  }
  // Se chegou ao fim do código Morse, retorna o nó encontrado
  else
  {
    return morseCharacterTree;
  }
}

// Função para traduzir um código Morse em um texto em caracteres
void translateMorseCode(MorseCharacterTree *root, const char *morseCode)
{
  // Separa as letras do código Morse usando espaço em branco como separador

  char *token = strtok((char *)morseCode, " ");

  while (token != NULL)
  {
    // Se o token é uma barra '/', imprime um espaço
    if (strcmp(token, "/") == 0)
    {
      printf(" ");
    }
    // Caso contrário, busca o caractere correspondente ao código Morse na árvore e imprime
    else
    {
      MorseCharacterTree *result = searchMorseCharacterTree(root, token);
      if (result != NULL)
      {
        printf("%c", result->character);
      }
    }

    // Obtém o próximo token
    token = strtok(NULL, " ");
  }
}

// Função para imprimir a árvore em pré-ordem
void printPreOrderMorseCharacterTree(MorseCharacterTree *morseCharacterTree)
{
  if (morseCharacterTree != NULL)
  {
    printf("%c ", morseCharacterTree->character);
    printPreOrderMorseCharacterTree(morseCharacterTree->dot);
    printPreOrderMorseCharacterTree(morseCharacterTree->dash);
  }
}

// Função para liberar a memória ocupada pela árvore
void freeMorseCharacterTree(MorseCharacterTree *morseCharacterTree)
{
  if (morseCharacterTree != NULL)
  {
    freeMorseCharacterTree(morseCharacterTree->dot);
    freeMorseCharacterTree(morseCharacterTree->dash);
    free(morseCharacterTree);
  }
}