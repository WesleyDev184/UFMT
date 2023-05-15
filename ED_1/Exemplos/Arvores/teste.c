#include <stdio.h>
#include <stdlib.h>

#define MAX_CHILDREN 3
typedef struct node
{
  int values[MAX_CHILDREN];
  struct node *childs[MAX_CHILDREN + 1];
} Node;

Node *createNode(int value)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->values[0] = value;
  for (int i = 0; i < MAX_CHILDREN + 1; i++)
  {
    newNode->childs[i] = NULL;
  }
  return newNode;
}

void insert(Node *root, int value)
{
  if (root->values[0] == 0)
  {
    root->values[0] = value;
    return;
  }
  if (root->values[0] > value)
  {
    if (root->childs[0] == NULL)
    {
      root->childs[0] = createNode(value);
      return;
    }
    insert(root->childs[0], value);
    return;
  }
  if (root->values[0] < value)
  {
    if (root->childs[1] == NULL)
    {
      root->childs[1] = createNode(value);
      return;
    }
    insert(root->childs[1], value);
    return;
  }
}

void printTreeOrdinate(Node *root)
{
  if (root->childs[0] != NULL)
  {
    printTreeOrdinate(root->childs[0]);
  }
  printf("%d ", root->values[0]);
  if (root->childs[1] != NULL)
  {
    printTreeOrdinate(root->childs[1]);
  }
}

void printTreePreOrder(Node *root)
{
  printf("%d ", root->values[0]);
  if (root->childs[0] != NULL)
  {
    printTreePreOrder(root->childs[0]);
  }
  if (root->childs[1] != NULL)
  {
    printTreePreOrder(root->childs[1]);
  }
}

void printTreePostOrder(Node *root)
{
  if (root->childs[0] != NULL)
  {
    printTreePostOrder(root->childs[0]);
  }
  if (root->childs[1] != NULL)
  {
    printTreePostOrder(root->childs[1]);
  }
  printf("%d ", root->values[0]);
}

void printNodeByChildLevel(Node *root, int level)
{
  if (level == 0)
  {
    printf("%d ", root->values[0]);
    return;
  }
  if (root->childs[0] != NULL)
  {
    printNodeByChildLevel(root->childs[0], level - 1);
  }
  if (root->childs[1] != NULL)
  {
    printNodeByChildLevel(root->childs[1], level - 1);
  }
}

void seachNode(Node *root, int value)
{
  if (root->values[0] == value)
  {
    printf("Valor encontrado!\n");
    printf("value: %d\n", root->values[0]);
    return;
  }
  if (root->values[0] > value)
  {
    if (root->childs[0] == NULL)
    {
      printf("Valor nao encontrado!\n");
      return;
    }
    seachNode(root->childs[0], value);
    return;
  }
  if (root->values[0] < value)
  {
    if (root->childs[1] == NULL)
    {
      printf("Valor nao encontrado!\n");
      return;
    }
    seachNode(root->childs[1], value);
    return;
  }
}

void seachMax(Node *root)
{
  if (root->childs[1] == NULL)
  {
    printf("Valor maximo: %d\n", root->values[0]);
    return;
  }
  seachMax(root->childs[1]);
}

void seachMin(Node *root)
{
  if (root->childs[0] == NULL)
  {
    printf("Valor minimo: %d\n", root->values[0]);
    return;
  }
  seachMin(root->childs[0]);
}

void removeNode(Node *root, int value)
{
  if (root->values[0] == value)
  {
    if (root->childs[0] == NULL && root->childs[1] == NULL)
    {
      root->values[0] = 0;
      return;
    }
    if (root->childs[0] != NULL && root->childs[1] == NULL)
    {
      root->values[0] = root->childs[0]->values[0];
      root->childs[0] = NULL;
      return;
    }
    if (root->childs[0] == NULL && root->childs[1] != NULL)
    {
      root->values[0] = root->childs[1]->values[0];
      root->childs[1] = NULL;
      return;
    }
    if (root->childs[0] != NULL && root->childs[1] != NULL)
    {
      Node *aux = root->childs[1];
      while (aux->childs[0] != NULL)
      {
        aux = aux->childs[0];
      }
      root->values[0] = aux->values[0];
      removeNode(root->childs[1], aux->values[0]);
      return;
    }
  }
  if (root->values[0] > value)
  {
    if (root->childs[0] == NULL)
    {
      printf("Valor nao encontrado!\n");
      return;
    }
    removeNode(root->childs[0], value);
    return;
  }
  if (root->values[0] < value)
  {
    if (root->childs[1] == NULL)
    {
      printf("Valor nao encontrado!\n");
      return;
    }
    removeNode(root->childs[1], value);
    return;
  }
}

int main()
{
  Node *root = createNode(0);
  insert(root, 10);
  insert(root, 5);
  insert(root, 15);
  insert(root, 3);
  insert(root, 7);
  insert(root, 12);
  insert(root, 17);
  insert(root, 1);
  insert(root, 4);
  insert(root, 6);
  insert(root, 8);
  insert(root, 11);
  insert(root, 13);
  insert(root, 16);
  insert(root, 18);
  insert(root, 2);
  insert(root, 9);
  insert(root, 14);
  insert(root, 19);
  insert(root, 20);

  printf("Ordem: ");
  printTreeOrdinate(root);

  printf("\nPre-Ordem: ");
  printTreePreOrder(root);

  printf("\nPos-Ordem: ");
  printTreePostOrder(root);

  printf("\nNivel 0: ");
  printNodeByChildLevel(root, 0);

  printf("\nNivel 1: ");
  printNodeByChildLevel(root, 1);

  printf("\nNivel 2: ");
  printNodeByChildLevel(root, 2);

  printf("\nBusca: ");
  seachNode(root, 10);

  printf("\nBusca: ");
  seachNode(root, 22);

  printf("\nMaximo: ");
  seachMax(root);

  printf("\nMinimo: ");
  seachMin(root);

  printf("\nRemovendo no 10\n");
  removeNode(root, 10);

  printf("\nOrdem: ");
  printTreeOrdinate(root);
}