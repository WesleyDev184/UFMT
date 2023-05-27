/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#ifndef ARVORE_MULTI_FILHOS_C
#define ARVORE_MULTI_FILHOS_C

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 3
typedef struct node
{
  int values[MAX_CHILDREN];
  int count;
  struct node *childs[MAX_CHILDREN + 1];
} Node;

Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->values[0] = value;
  newNode->count = 1;
  for (int i = 0; i < MAX_CHILDREN + 1; i++)
    newNode->childs[i] = NULL;
  return newNode;
}

void insert(Node **root, int value)
{
  if (*root == NULL)
    *root = createNode(value);
  else
  {
    if ((*root)->count < MAX_CHILDREN)
    {
      int i = (*root)->count - 1;
      while (i >= 0 && (*root)->values[i] > value)
      {
        (*root)->values[i + 1] = (*root)->values[i];
        i--;
      }
      (*root)->values[i + 1] = value;
      (*root)->count++;
    }
    else
    {
      int i = (*root)->count - 1;
      while (i >= 0 && (*root)->values[i] > value)
        i--;
      insert(&(*root)->childs[i + 1], value);
    }
  }
}

void printTreePreOrder(Node *root)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
      printf("%d ", root->values[i]);
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      printTreePreOrder(root->childs[i]);
  }
}

int calculateTreeHeight(Node *root)
{
  if (root == NULL)
  {
    return -1;
  }

  int childrenHeight[MAX_CHILDREN + 1];
  int i;

  for (i = 0; i < root->count + 1; i++)
  {
    childrenHeight[i] = calculateTreeHeight(root->childs[i]);
  }

  int maxChildrenHeight = childrenHeight[0];

  for (i = 1; i < root->count + 1; i++)
  {
    if (childrenHeight[i] > maxChildrenHeight)
    {
      maxChildrenHeight = childrenHeight[i];
    }
  }

  return maxChildrenHeight + 1;
}

#endif