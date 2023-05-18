/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morseCharacterTree.c"

void loadMorseCodes(MorseCharacterTree **root, const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }

  char line[100];
  while (fgets(line, sizeof(line), file))
  {
    char *morseCode = strtok(line, " ");
    char character = strtok(NULL, "\n")[0];

    *root = insertMorseCharacterTree(*root, morseCode, character);
  }

  fclose(file);
}

int main()
{
  MorseCharacterTree *root = createMorseCharacterTree('|');
  loadMorseCodes(&root, "cola.txt");

  printPreOrderMorseCharacterTree(root);
  printf("\n");

  printf("Digite o codigo Morse: ");
  char morseCode[500];
  fgets(morseCode, sizeof(morseCode), stdin);
  morseCode[strcspn(morseCode, "\n")] = '\0';

  printf("\nTraducao: ");
  translateMorseCode(root, morseCode);
  printf("\n");

  freeMorseCharacterTree(root);
  return 0;
}
