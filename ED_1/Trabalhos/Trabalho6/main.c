/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#include <stdio.h>
#include <stdlib.h>

#include "arvoreMultiFilhos.c"

void readMatrixFromFile(const char *fileName, int ***matrix, int *columns, int *rows)
{
  FILE *file;
  int i, j;

  file = fopen(fileName, "r");
  if (file == NULL)
  {
    printf("Error opening the file.\n");
    exit(1);
  }

  fscanf(file, "%d", columns);
  fscanf(file, "%d", rows);

  *matrix = (int **)malloc((*columns) * sizeof(int *));
  for (i = 0; i < *columns; i++)
  {
    (*matrix)[i] = (int *)malloc((*rows) * sizeof(int));
    for (j = 0; j < *rows; j++)
    {
      fscanf(file, "%d", &(*matrix)[i][j]);
    }
  }

  fclose(file);
}

int main()
{
  int **matrix;
  int columns, rows;
  int i, j;

  Node *rowTree = NULL;
  Node *columnTree = NULL;

  readMatrixFromFile("dados.txt", &matrix, &columns, &rows);

  for (i = 0; i < columns; i++)
  {
    for (j = 0; j < rows; j++)
    {
      printf("%d ", matrix[i][j]);
      insert(&rowTree, matrix[i][j]);
    }
  }

  printf("\n");

  for (i = 0; i < rows; i++)
  {
    for (j = 0; j < columns; j++)
    {
      printf("%d ", matrix[j][i]);
      insert(&columnTree, matrix[j][i]);
    }
  }

  printf("\n\n");

  printf("Row Tree: ");
  printTreePreOrder(rowTree);
  int height = calculateTreeHeight(rowTree);
  printf("\nRowTree Height: %d\n", height);

  printf("\n");

  printf("Column Tree: ");
  printTreePreOrder(columnTree);
  height = calculateTreeHeight(columnTree);
  printf("\nColumnTree Height: %d\n", height);

  // Free allocated memory for the matrix
  for (i = 0; i < columns; i++)
  {
    free(matrix[i]);
  }
  free(matrix);

  return 0;
}
