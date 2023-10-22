#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct sNoA
{
  int chave;
  int fb; // fator de balanceamento
  int h;
  struct sNoA *esq;
  struct sNoA *dir;
} TNoA;

// Funcao que retorna altura de um nó
int altura_NO(TNoA *no)
{
  if (no == NULL)
    return -1;
  else
    return no->h;
}

int maior(int x, int y)
{
  if (x > y)
    return x;
  else
    return y;
}

// Calcula o fator de balanceamento
int fatorBalanceamento_NO(TNoA *no)
{
  return (altura_NO(no->dir) - altura_NO(no->esq));
}

TNoA *rotacao_direita(TNoA *pt)
{
  TNoA *ptu;

  ptu = pt->esq;
  pt->esq = ptu->dir;
  ptu->dir = pt;
  pt->h = maior(altura_NO(pt->esq),
                altura_NO(pt->dir)) +
          1;
  ptu->h = maior(altura_NO(ptu->esq),
                 pt->h) +
           1;
  pt = ptu;
  return pt;
}

TNoA *rotacao_esquerda(TNoA *pt)
{
  TNoA *ptu;
  ptu = pt->dir;

  pt->dir = ptu->esq;
  ptu->esq = pt;
  pt->h = maior(altura_NO(pt->esq),
                altura_NO(pt->dir)) +
          1;
  ptu->h = maior(altura_NO(ptu->dir),
                 pt->h) +
           1;
  pt = ptu;
  return pt;
}

TNoA *rotacao_dupla_direita(TNoA *pt)
{
  pt->esq = rotacao_esquerda(pt->esq);
  pt = rotacao_direita(pt);
  return pt;
}

TNoA *rotacao_dupla_esquerda(TNoA *pt)
{
  pt->dir = rotacao_direita(pt->dir);
  pt = rotacao_esquerda(pt);
  return pt;
}

// Tarefa para as férias
// Implementar a funcão remove
TNoA *remover(TNoA *no, int chave)
{
  TNoA *aux;
  if (no == NULL)
    return NULL;
  else if (no->chave > chave)
    no->esq = remover(no->esq, chave);
  else if (no->chave < chave)
    no->dir = remover(no->dir, chave);
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

TNoA *insere(TNoA *no, int chave)
{

  TNoA *u;

  if (no == NULL)
  {
    no = (TNoA *)malloc(sizeof(TNoA));
    no->chave = chave;
    no->esq = no->dir = NULL;
    no->h = 0;
    no->fb = 0;
  }
  else if (chave < (no->chave))
  {

    no->esq = insere(no->esq, chave);
    no->h = no->esq->h + 1;
    no->fb = fatorBalanceamento_NO(no);

    /* desbalanceado a esquerda */
    if (no->fb <= -2)
    {

      u = no->esq; /* Recebe filho a esquerda */
      u->fb = fatorBalanceamento_NO(u);

      if (u->fb == -1)
      { /* Caso de sinais iguais e negativos: RD*/
        printf("RSD(%d)\n", no->chave);
        no = rotacao_direita(no);
      }
      else
      { /* Caso de sinais diferentes: Rotacao dupla direita */
        printf("RDD(%d)\n", no->chave);
        no = rotacao_dupla_direita(no);
      }

      no->fb = 0;
    }
  }
  else if (chave > (no->chave))
  {

    no->dir = insere(no->dir, chave);
    no->h = no->dir->h + 1; // Incrementa a altura do nó
    no->fb = fatorBalanceamento_NO(no);

    /* desbalanceado a direita */
    if (no->fb == 2)
    {

      u = no->dir; // Recebe filho a direita
      u->fb = fatorBalanceamento_NO(u);

      /* Verifica sinal do filho a direita */
      if (u->fb == 1)
      { // Caso de sinais iguais: rotacao simples direita
        printf("RSE(%d)\n", no->chave);
        no = rotacao_esquerda(no);
      }
      else
      {
        // Caso de sinais diferentes: rotacao dupla esquerda
        printf("RDE(%d)\n", no->chave);
        no = rotacao_dupla_esquerda(no);
      }
      no->fb = 0;
    }
  }

  else
  {
    printf("Insercao invalida\n");
    exit(1);
  }
  return no;
}

void imprime(TNoA *no, int tab)
{

  if (no != NULL)
  {
    tab += 10;
    imprime(no->dir, tab);
    printf("\n");
    for (int i = 10; i < tab; i++)
      printf(" ");

    printf("%d (%d)\n", no->chave, no->h);

    imprime(no->esq, tab + 2);
  }
}

int main(void)
{
  TNoA *raiz;
  raiz = NULL;

  raiz = insere(raiz, 50);
  imprime(raiz, 0);
  printf("******************************************40\n");
  raiz = insere(raiz, 40);
  imprime(raiz, 0);
  printf("******************************************30\n");
  raiz = insere(raiz, 30);
  imprime(raiz, 0);
  printf("******************************************45\n");
  raiz = insere(raiz, 45);
  imprime(raiz, 0);
  printf("******************************************47\n");
  raiz = insere(raiz, 47);
  imprime(raiz, 0);
  printf("******************************************55\n");
  raiz = insere(raiz, 55);
  imprime(raiz, 0);
  printf("******************************************56\n");
  raiz = insere(raiz, 56);
  imprime(raiz, 0);
  printf("******************************************1\n");
  raiz = insere(raiz, 1);
  imprime(raiz, 0);
  printf("******************************************2\n");
  raiz = insere(raiz, 2);
  imprime(raiz, 0);
  printf("******************************************3\n");
  raiz = insere(raiz, 3);
  imprime(raiz, 0);
  printf("******************************************49\n");
  raiz = insere(raiz, 49);
  imprime(raiz, 0);

  printf("removerndo o 49\n");
  raiz = remover(raiz, 49);
  imprime(raiz, 0);

  return 0;
}