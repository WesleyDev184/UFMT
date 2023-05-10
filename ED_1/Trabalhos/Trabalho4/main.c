/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1 - Trabalho 6 : lst - estática x dinamica
 * Prof Ivairton
 * Discentes:  Lucas Barbosa Amaral, Wesley Antonio Junior dos Santos
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de um nó da árvore binária
typedef struct Node
{
  int value;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct players
{
  Node *player1;
  Node *player2;
} Players;

/**
 * The function creates a new node with a given value and returns a pointer to it.
 *
 * @param value The value to be stored in the node.
 *
 * @return The function `createNode` is returning a pointer to a newly created `Node` structure with
 * the specified `value`, and `left` and `right` pointers set to `NULL`.
 */
Node *createNode(int value)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

/**
 * The function inserts a new node with a given value into a binary search tree.
 *
 * @param root a pointer to the root node of a binary search tree.
 * @param value The integer value that needs to be inserted into the binary search tree.
 */
void insert(Node *root, int value)
{
  if (value <= root->value)
  {
    if (root->left == NULL)
    {
      root->left = createNode(value);
    }
    else
    {
      insert(root->left, value);
    }
  }
  else
  {
    if (root->right == NULL)
    {
      root->right = createNode(value);
    }
    else
    {
      insert(root->right, value);
    }
  }
}

/**
 * The function traverses a binary tree based on a given sequence of choices.
 *
 * @param root A pointer to the root node of a binary tree.
 * @param choices choices is a character array that contains the choices made by the user to traverse a
 * binary tree. The first character of the array determines whether to go left ('e') or right ('d')
 * from the root node.
 *
 * @return a pointer to a Node.
 */
Node *traverse(Node *root, char *choices)
{
  Node *node = root;

  if (choices[0] == 'e')
  {
    if (node->left == NULL)
    {
      return NULL;
    }
    node = node->left;
  }
  else if (choices[0] == 'd')
  {
    if (node->right == NULL)
    {
      return NULL;
    }
    node = node->right;
  }
  else
  {
    return NULL;
  }

  return node;
}

/**
 * These are three functions that print the values of a binary tree in pre-order, in-order, and
 * post-order traversal.
 *
 * @param arv a pointer to a binary tree node, which represents the root of the tree or a subtree.
 */
void imprimePreOrdem(Node *arv)
{
  if (arv != NULL)
  {
    printf("%d ", arv->value);
    imprimePreOrdem(arv->left);
    imprimePreOrdem(arv->right);
  }
}

void imprimeOrdem(Node *arv)
{
  if (arv != NULL)
  {
    imprimeOrdem(arv->left);
    printf("%d ", arv->value);
    imprimeOrdem(arv->right);
  }
}

void imprimePosOrdem(Node *arv)
{
  if (arv != NULL)
  {
    imprimePosOrdem(arv->left);
    imprimePosOrdem(arv->right);
    printf("%d ", arv->value);
  }
}

/**
 * The function creates a binary tree with random values, allows two players to traverse the tree and
 * accumulate scores based on the values of the nodes they visit, and prints the final scores.
 *
 * @return The function `main()` is returning an integer value of 0.
 */
int main()
{
  // Inicialização da árvore binária com 15 valores aleatórios
  Node *root = createNode(rand() % 31);
  for (int i = 0; i < 14; i++)
  {
    insert(root, rand() % 31);
  }

  Players *players = (Players *)malloc(sizeof(Players));
  players->player1 = root;
  players->player2 = root;

  // Impressão da árvore binária
  imprimeOrdem(root);
  printf("\n");

  // Jogo
  srand(time(NULL));
  int score1 = 0, score2 = 0;
  char choices[1];
  for (int round = 1; round <= 3; round++)
  {
    printf("Round %d\n", round);
    printf("Jogador 1, escolha um caminho (ex: e ou d): ");
    scanf("%1s", choices);
    Node *node1 = traverse(players->player1, choices);
    if (node1 == NULL)
    {
      printf("Jogador 1 desclassificado!\n");
      break;
    }
    players->player1 = node1;
    score1 += node1->value;
    printf("Pontuacao: %d\n", score1);

    printf("Jogador 2, escolha um caminho (ex: e ou d): ");
    scanf("%1s", choices);
    Node *node2 = traverse(players->player2, choices);
    if (node2 == NULL)
    {
      printf("Jogador 2 desclassificado!\n");
      break;
    }
    players->player2 = node2;
    score2 += node2->value;
    printf("Pontuacao: %d\n", score2);
  }

  printf("Pontuacao final:\n");
  printf("Jogador 1: %d\n", score1);
  printf("Jogador 2: %d\n", score2);

  return 0;
}
