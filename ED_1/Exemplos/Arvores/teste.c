#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
} Node;

Node *createNode(int data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *insert(Node *root, int data)
{
  if (root == NULL)
  {
    return createNode(data);
  }
  else
  {
    if (data <= root->data)
    {
      root->left = insert(root->left, data);
    }
    else
    {
      root->right = insert(root->right, data);
    }
    return root;
  }
}

void preOrder(Node *root)
{
  if (root != NULL)
  {
    printf("%d ", root->data);
    preOrder(root->left);
    preOrder(root->right);
  }
}

int height(Node *root)
{
  if (root == NULL)
  {
    return -1;
  }
  else
  {
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    if (leftHeight > rightHeight)
    {
      return leftHeight + 1;
    }
    else
    {
      return rightHeight + 1;
    }
  }
}

int main()
{
  Node *root = NULL;
  root = insert(root, 50);
  insert(root, 30);
  insert(root, 20);
  insert(root, 40);
  insert(root, 70);
  insert(root, 60);
  insert(root, 80);

  printf("Height: %d\n", height(root));

  printf("Pre Order: ");
  preOrder(root);
  printf("\n");

  return 0;
}
