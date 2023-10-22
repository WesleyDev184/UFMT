#include <stdio.h>
#include <stdlib.h>

typedef struct sNoA
{
  int chave;
  struct sNoA *esq;
  struct sNoA *dir;
} TNoA;

// Função para realizar a rotação à direita em um nó desbalanceado
TNoA *rotacaoDireita(TNoA *raiz)
{
  TNoA *novaRaiz = raiz->esq;
  raiz->esq = novaRaiz->dir;
  novaRaiz->dir = raiz;
  return novaRaiz;
}

// Função para realizar a rotação à esquerda em um nó desbalanceado
TNoA *rotacaoEsquerda(TNoA *raiz)
{
  TNoA *novaRaiz = raiz->dir;
  raiz->dir = novaRaiz->esq;
  novaRaiz->esq = raiz;
  return novaRaiz;
}

// Função para inserir um novo nó na árvore
TNoA *insere(TNoA *no, int chave)
{
  if (no == NULL)
  {
    // Cria um novo nó com a chave especificada
    no = (TNoA *)malloc(sizeof(TNoA));
    no->chave = chave;
    no->esq = NULL;
    no->dir = NULL;
  }
  else if (chave < no->chave)
  {
    // Insere na subárvore esquerda e verifica se é necessário aplicar rotação à direita
    no->esq = insere(no->esq, chave);
    if (no->esq != NULL && no->esq->chave == chave)
      no = rotacaoDireita(no);
  }
  else
  {
    // Insere na subárvore direita e verifica se é necessário aplicar rotação à esquerda
    no->dir = insere(no->dir, chave);
    if (no->dir != NULL && no->dir->chave == chave)
      no = rotacaoEsquerda(no);
  }
  return no;
}

// Função para buscar um nó na árvore e trazê-lo para a raiz, aplicando rotações quando necessário
TNoA *busca(TNoA *no, int chave)
{
  if (no == NULL || no->chave == chave)
  {
    return no;
  }

  if (chave < no->chave)
  {
    // Realiza a busca na subárvore esquerda e verifica se é necessário aplicar rotação à direita
    no->esq = busca(no->esq, chave);
    if (no->esq != NULL && no->esq->chave == chave)
      return rotacaoDireita(no);
  }
  else
  {
    // Realiza a busca na subárvore direita e verifica se é necessário aplicar rotação à esquerda
    no->dir = busca(no->dir, chave);
    if (no->dir != NULL && no->dir->chave == chave)
      return rotacaoEsquerda(no);
  }
  return no;
}

// Função para imprimir a árvore em ordem
void imprime(TNoA *nodo, int tab)
{
  if (nodo != NULL)
  {
    // Imprime a subárvore direita
    imprime(nodo->dir, tab + 2);
    // Imprime o nó atual com o devido recuo
    printf("%*s%d\n", tab, "", nodo->chave);
    // Imprime a subárvore esquerda
    imprime(nodo->esq, tab + 2);
  }
}

// Função para criar uma árvore vazia
TNoA *cria(void)
{
  return NULL;
}

int main(void)
{
  TNoA *raiz;
  raiz = cria();

  // Inserção dos valores na árvore
  raiz = insere(raiz, 50);
  raiz = insere(raiz, 70);
  raiz = insere(raiz, 80);
  raiz = insere(raiz, 75);
  raiz = insere(raiz, 40);
  raiz = insere(raiz, 30);
  raiz = insere(raiz, 55);
  raiz = insere(raiz, 53);

  // Imprime a árvore original
  printf("\nArvore Original:\n");
  imprime(raiz, 0);

  // Lê o valor a ser buscado
  int x;
  printf("Digite o valor a ser buscado: ");
  scanf("%i", &x);

  // Busca o valor na árvore e imprime a árvore resultante
  raiz = busca(raiz, x);
  printf("\nArvore Apos Busca:\n");
  imprime(raiz, 0);

  return 0;
}