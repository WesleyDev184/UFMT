#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *firstChild;
  struct node *nextSibling;
} Node;

Node *createNode(int data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->firstChild = NULL;
  newNode->nextSibling = NULL;
  return newNode;
}

void addChild(Node *parent, Node *child)
{
  if (parent->firstChild == NULL)
  {
    parent->firstChild = child;
  }
  else
  {
    Node *sibling = parent->firstChild;
    while (sibling->nextSibling != NULL)
    {
      sibling = sibling->nextSibling;
    }
    sibling->nextSibling = child;
  }
}

void printTree(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  printf("%d: ", root->data);
  Node *child = root->firstChild;
  while (child != NULL)
  {
    printf("%d ", child->data);
    child = child->nextSibling;
  }
  printf("\n");
  child = root->firstChild;
  while (child != NULL)
  {
    printTree(child);
    child = child->nextSibling;
  }
}

int main()
{
  Node *root = createNode(1);
  Node *child1 = createNode(2);
  Node *child2 = createNode(3);
  Node *child3 = createNode(4);
  Node *child4 = createNode(5);
  Node *child5 = createNode(6);
  Node *child6 = createNode(7);
  Node *child7 = createNode(8);
  Node *child8 = createNode(9);
  Node *child9 = createNode(10);
  Node *child10 = createNode(11);

  addChild(root, child1);
  addChild(root, child2);
  addChild(root, child3);
  addChild(child1, child4);
  addChild(child1, child5);
  addChild(child1, child6);
  addChild(child2, child7);
  addChild(child2, child8);
  addChild(child3, child9);
  addChild(child3, child10);

  printTree(root);

  return 0;
}