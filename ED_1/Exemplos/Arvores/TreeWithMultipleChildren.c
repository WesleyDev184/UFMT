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

void insert(Node *root, int value)
{
  if (root->count < MAX_CHILDREN)
  {
    root->values[root->count] = value;
    root->count++;
  }
  else
  {
    int i = 0;
    while (i < MAX_CHILDREN && root->values[i] < value)
      i++;
    if (root->childs[i] == NULL)
      root->childs[i] = createNode(value);
    else
      insert(root->childs[i], value);
  }
}

void printTreeOrdinate(Node *root)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
      printf("%d ", root->values[i]);
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      printTreeOrdinate(root->childs[i]);
  }
}

void printTreePreOrder(Node *root)
{
  if (root != NULL)
  {
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      printTreePreOrder(root->childs[i]);
    for (int i = 0; i < root->count; i++)
      printf("%d ", root->values[i]);
  }
}

void printTreePostOrder(Node *root)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
      printf("%d ", root->values[i]);
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      printTreePostOrder(root->childs[i]);
  }
}

void printTreeHeight(Node *root, int height)
{
  if (root != NULL)
  {
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      printTreeHeight(root->childs[i], height + 1);

    printf("Height: %d\n", height);
  }
}

void printNodeByChildLevel(Node *root, int level)
{
  if (root != NULL)
  {
    if (level == 0)
    {
      for (int i = 0; i < root->count; i++)
        printf("%d ", root->values[i]);
    }
    else
    {
      for (int i = 0; i < MAX_CHILDREN + 1; i++)
        printNodeByChildLevel(root->childs[i], level - 1);
    }
  }
}

void seachNodeByValue(Node *root, int value)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
    {
      if (root->values[i] == value)
      {
        printf("Value %d found!\n", value);
        return;
      }
    }
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      seachNodeByValue(root->childs[i], value);
  }
}

void removeNode(Node *root, int value)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
    {
      if (root->values[i] == value)
      {
        for (int j = i; j < root->count - 1; j++)
          root->values[j] = root->values[j + 1];
        root->count--;
        return;
      }
    }
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      removeNode(root->childs[i], value);
  }
}

void seachMax(Node *root)
{
  if (root->childs[MAX_CHILDREN] == NULL)
  {
    printf("Valor maximo: %d\n", root->values[root->count - 1]);
    return;
  }
  seachMax(root->childs[MAX_CHILDREN]);
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

void nodeCounter(Node *root, int *counter)
{
  if (root != NULL)
  {
    for (int i = 0; i < root->count; i++)
      (*counter)++;
    for (int i = 0; i < MAX_CHILDREN + 1; i++)
      nodeCounter(root->childs[i], counter);
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

  printf("Ordinate: ");
  printTreeOrdinate(root);

  printf("\nPre-Order: ");
  printTreePreOrder(root);

  printf("\nPost-Order: ");
  printTreePostOrder(root);

  printf("\nHeight: ");
  printTreeHeight(root, 0);

  printf("\nNode by level: ");
  printNodeByChildLevel(root, 1);

  printf("\nSearch node by value: ");
  seachNodeByValue(root, 10);

  printf("\nSearch max value: ");
  seachMax(root);

  printf("\nSearch min value: ");
  seachMin(root);

  int counter = 0;
  nodeCounter(root, &counter);
  printf("\nNumber of nodes: %d", counter);

  printf("\nRemove node by value: 10");
  removeNode(root, 10);

  printf("\nOrdinate: ");
  printTreeOrdinate(root);

  counter = 0;
  nodeCounter(root, &counter);
  printf("\nNumber of nodes: %d", counter);

  return 0;
}