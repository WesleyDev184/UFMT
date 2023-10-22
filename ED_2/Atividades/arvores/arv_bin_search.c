#include <stdio.h>
#include <stdlib.h>

typedef struct sNoA
{
  int chave;
  char info;
  struct sNoA *esq;
  struct sNoA *dir;
} TNoA;

TNoA *abb_cria(void)
{
  return NULL;
}

void abb_imprime(TNoA *nodo, int tab)
{

  if (nodo != NULL)
  {

    abb_imprime(nodo->esq, tab + 2);
    printf("%d\n", nodo->chave);
    // printf("\n");
    abb_imprime(nodo->dir, tab + 2);
  }
}

TNoA *abb_busca(TNoA *no, int chave)
{
  if (no == NULL)
    return NULL;
  else if (no->chave > chave)
    return abb_busca(no->esq, chave);
  else if (no->chave < chave)
    return abb_busca(no->dir, chave);
  else
    return no;
}

TNoA *abb_insere(TNoA *no, int chave)
{
  if (no == NULL)
  {
    no = (TNoA *)malloc(sizeof(TNoA));
    no->chave = chave;

    no->esq = no->dir = NULL;
  }
  else if (chave < no->chave)
    no->esq = abb_insere(no->esq, chave);
  else
    no->dir = abb_insere(no->dir, chave);
  return no;
}

TNoA *abb_exclui(TNoA *no, int chave)
{
  TNoA *aux;
  if (no == NULL)
    return NULL;
  else if (no->chave > chave)
    no->esq = abb_exclui(no->esq, chave);
  else if (no->chave < chave)
    no->dir = abb_exclui(no->dir, chave);
  else
  {
    if (no->esq == NULL && no->dir == NULL)
    {
      free(no);
      no = NULL;
    }
    else if (no->esq == NULL)
    {
      aux = no;
      no = no->dir;
      free(aux);
    }
    else if (no->dir == NULL)
    {
      aux = no;
      no = no->esq;
      free(aux);
    }
  }
  return no;
}

int main(void)
{
  TNoA *raiz;
  raiz = abb_cria();
  int qt, value, x;

  printf("Digite a quantidade de valores a serem inseridos: ");
  scanf("%i", &qt);

  for (int i = 0; i < qt; i++)
  {

    scanf("%i", &value);
    raiz = abb_insere(raiz, value);
  }
  printf("Qual valor deseja excluir: ");
  scanf("%i", &x);
  raiz = abb_exclui(raiz, x);

  printf("\n");
  printf("Arvore:\n");
  abb_imprime(raiz, 0);

  return 0;
}