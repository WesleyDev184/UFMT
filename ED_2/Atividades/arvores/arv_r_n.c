#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct sNoA{
  int chave;
  int cor;
  struct sNoA *esq;
  struct sNoA *dir;
  struct sNoA *pai;
} TNoA;

int cor(TNoA *no){
  if (no == NULL)
    return BLACK;
  else
    return no->cor;
}

TNoA *rotacao_direita(TNoA *pt){
  TNoA *ptu;
  ptu = pt->esq;

  printf("RSD (%d)\n", pt->chave);

  pt->esq = ptu->dir;
  if (ptu->dir != NULL)
    ptu->dir->pai = pt;
  ptu->pai = pt->pai;

  if (pt->pai != NULL){
    if (pt == ptu->pai->dir)
      pt->pai->dir = ptu;
    else
      pt->pai->esq = ptu;
  }
  ptu->dir = pt;
  pt->pai = ptu;
  pt = ptu;
  return pt;
}

TNoA *rotacao_esquerda(TNoA *pt){

  TNoA *ptu;
  ptu = pt->dir;
  printf("RSE (%d)\n", pt->chave);

  pt->dir = ptu->esq;
  if (ptu->esq != NULL)
    ptu->esq->pai = pt;
  ptu->pai = pt->pai;

  if (pt->pai != NULL){
    if (pt == ptu->pai->esq)
      pt->pai->esq = ptu;
    else
      pt->pai->dir = ptu;
  }
  ptu->esq = pt;
  pt->pai = ptu;
  pt = ptu;
  return pt;
}

TNoA *insere_fixup(TNoA *T, TNoA *z)
{
  TNoA *y;
  while (cor(z->pai) == RED){
    // Verifica se o pai de Z é filho a esquerda do avo de Z
    if (z->pai == z->pai->pai->esq){
      // y recebe o tio de Z
      y = (z->pai)->pai->dir;

      // Se o tio de z for vermelho
      if (cor(y) == RED){
        // caso 01
        printf("CASO 1 (%d) \n", z->chave);
        z->pai->cor = BLACK;    // Pai de Z troca de vermelho para preto
        y->cor = BLACK;         // Tio de Z troca de vermelho para preto
        z->pai->pai->cor = RED; // Avo de Z troca de preto para vermeho
        z = z->pai->pai;        // Z passa a ser'' o AVO
      }else{
        // Verificando se Z é filho direita
        if (z == z->pai->dir){
          // caso 02
          printf("CASO 2 (%d) \n", z->chave);
          z = z->pai;
          z = rotacao_esquerda(z);
          z = z->esq;
        }
        else{
          // caso 03
          printf("CASO 3 (%d) \n", z->chave);
          z->pai->cor = BLACK;
          z->pai->pai->cor = RED;
          z = rotacao_direita(z->pai->pai);

          z = z->esq;
        }
      }
    }else{
      // se o pai é filho a direita
      // y recebe o tio de Z
      y = (z->pai)->pai->esq;

      // Se o tio de z for vermelho
      if (cor(y) == RED){
        // caso 01
        printf("CASO 1 (%d) \n", z->chave);
        z->pai->cor = BLACK;    // Pai de Z troca de vermelho para preto
        y->cor = BLACK;         // Tio de Z troca de vermelho para preto
        z->pai->pai->cor = RED; // Avo de Z troca de preto para vermeho
        z = z->pai->pai;        // Z passa a ser'' o AVO
      }else{
        // Verificando se Z é filho dir
        if (z == z->pai->dir){
          // caso 02
          printf("CASO 2 (%d) \n", z->chave);
          z = z->pai;
          z = rotacao_esquerda(z);
          z = z->esq;
        }else{
          // caso 03
          printf("CASO 3 (%d) \n", z->chave);
          z->pai->cor = BLACK;
          z->pai->pai->cor = RED;
          z = rotacao_esquerda(z->pai->pai);

          z = z->esq->dir;
        }
      }
    }
  }

  while (z->pai != NULL){
    z = z->pai;
  }
  z->cor = BLACK;
  return z;
}

TNoA *insere(TNoA *no, int chave){

  TNoA *y = NULL;
  TNoA *x = no;

  while (x != NULL){
    y = x;
    if (chave < x->chave)
      x = x->esq;
    else
      x = x->dir;
  }

  x = (TNoA *)malloc(sizeof(TNoA));
  x->chave = chave;
  x->esq = x->dir = NULL;
  x->cor = RED;
  x->pai = y;

  if (y == NULL){
    no = x;
  }else{
    if (x->chave < y->chave)
      y->esq = x;
    else
      y->dir = x;
  }

  printf("---------------FIXUP-BEGIN----------------");
  no = imprime(no, 0);
  x = insere_fixup(no, x);
  printf("---------------FIXUP-END----------------");

  return x;
}

void imprime(TNoA *no, int tab){

  if (no != NULL){
    tab += 10;
    imprime(no->dir, tab);
    printf("\n");
    for (int i = 10; i < tab; i++)
      printf(" ");

    printf("%d", no->chave);
    if (no->cor == RED)
      printf("(V)\n");
    else
      printf("(B)\n");
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

  return 0;
}