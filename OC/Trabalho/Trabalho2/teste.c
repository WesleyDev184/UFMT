#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore
typedef struct tipo_arv_bin
{
  int data;
  struct tipo_arv_bin *esq;
  struct tipo_arv_bin *dir;
} Tipo_arv_bin;

// Definição da estrutura do nó da lista circular duplamente encadeada
typedef struct tipo_lst_dup_circ
{
  int data;
  struct tipo_lst_dup_circ *ant;
  struct tipo_lst_dup_circ *prox;
} Tipo_lst_dup_circ;

// Cria a árvore binária
Tipo_arv_bin *cria_arv_bin(int data)
{
  Tipo_arv_bin *arv = (Tipo_arv_bin *)malloc(sizeof(Tipo_arv_bin));
  arv->data = data;
  arv->esq = NULL;
  arv->dir = NULL;
  return arv;
}

// Insere um nó na árvore binária
Tipo_arv_bin *insere_arv_bin(Tipo_arv_bin *arv, int data)
{
  if (arv == NULL)
    return cria_arv_bin(data);
  if (data < arv->data)
    arv->esq = insere_arv_bin(arv->esq, data);
  else if (data > arv->data)
    arv->dir = insere_arv_bin(arv->dir, data);
  return arv;
}

// Insere um nó na lista circular duplamente encadeada
void insere_fim_lst_dup_circ(Tipo_lst_dup_circ **lst, int data)
{
  if (*lst == NULL)
  {
    Tipo_lst_dup_circ *novo_no = (Tipo_lst_dup_circ *)malloc(sizeof(Tipo_lst_dup_circ));
    novo_no->data = data;
    novo_no->ant = novo_no;  // Aponta para si mesmo inicialmente
    novo_no->prox = novo_no; // Aponta para si mesmo inicialmente
    *lst = novo_no;
  }
  else
  {
    Tipo_lst_dup_circ *novo = (Tipo_lst_dup_circ *)malloc(sizeof(Tipo_lst_dup_circ));
    novo->data = data;
    novo->ant = (*lst)->ant;
    novo->prox = *lst;
    (*lst)->ant->prox = novo;
    (*lst)->ant = novo;
  }
}

// Processa a árvore binária e insere os nós na lista circular duplamente encadeada
void processa_arv_bin(Tipo_arv_bin *arv, Tipo_lst_dup_circ **lst)
{
  if (arv == NULL)
  {
    printf("Arvore vazia\n");
    return;
  }
  insere_fim_lst_dup_circ(lst, arv->data); // Insere o nó atual na lista
  processa_arv_bin(arv->esq, lst);         // Processa a subárvore esquerda recursivamente
  processa_arv_bin(arv->dir, lst);         // Processa a subárvore direita recursivamente
}

int main()
{
  Tipo_arv_bin *arv = NULL;      // Árvore binária inicialmente vazia
  Tipo_lst_dup_circ *lst = NULL; // Lista circular duplamente encadeada inicialmente vazia

  // Insere os nós na árvore binária
  arv = insere_arv_bin(arv, 10);
  arv = insere_arv_bin(arv, 5);
  arv = insere_arv_bin(arv, 15);
  arv = insere_arv_bin(arv, 7);
  arv = insere_arv_bin(arv, 12);

  // Processa a árvore binária e insere os nós na lista circular duplamente encadeada
  processa_arv_bin(arv, &lst);

  // Imprime os elementos da lista circular duplamente encadeada
  if (lst != NULL)
  {
    Tipo_lst_dup_circ *atual = lst;
    do
    {
      printf("%d ", atual->data);
      atual = atual->prox;
    } while (atual != lst);
    printf("\n");
  }
  return 0;
}
