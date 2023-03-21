/*
 * UFMT - Ciencia da Computacao
 * Estrutura de Dados 1
 * Prof Ivairton
 * Discentes: Claudio Antonio Nery de Oliveira, Lucas Barbosa Amaral
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// criação da estrutura
struct str_lista
{
    int valor;
    struct str_lista *cont;
};
typedef struct str_lista tipo_lista;

// prototipos das funcoes

void insereInicioLista(tipo_lista **, int);
void insereFimLista(tipo_lista **, int);
void inserePosLista(tipo_lista **, int, int);

// realiza a inserção no inicio a partir da chamada da função inserePosLista na posição 0,ou seja, no inicio do vetor

void insereInicioLista(tipo_lista **lst, int vl)
{
    inserePosLista(lst, 0, vl);
}

// realiza a inserção no fim a partir da chamada da função inserePosLista na posição do ponteiro que aponta para o contador(pós quantidade de valores no vetor)

void insereFimLista(tipo_lista **lst, int vl)
{
    tipo_lista *novoNo, *aux;
    novoNo = (tipo_lista *)malloc(sizeof(tipo_lista));

    // inicializa valores do novoNo
    novoNo->valor = vl;
    novoNo->cont = NULL;

    // Acopla novoNo na lista
    if ((*lst) == NULL)
    {
        *lst = novoNo;
    }
    else
    {
        // percorre a lista ate o ultimo no
        aux = *lst;
        while (aux->cont != NULL)
        {
            aux = aux->cont;
        }
        // anexa o novoNo ao  ultimo noh
        aux->cont = novoNo;
    }
}

// insere na posição

void inserePosLista(tipo_lista **lst, int vl, int pos)
{
    int cont = 0;
    tipo_lista *aux, *ant, *novo_no;
    novo_no = (tipo_lista *)malloc(sizeof(tipo_lista));
    novo_no->valor = vl;

    aux = (*lst);
    while ((aux != NULL) && (cont < pos))
    { // laço para atualizar as posições dentro do vetor e atualizar o contador/aux
        ant = aux;
        aux = aux->cont;
        cont++;
    }

    novo_no->cont = aux;
    ant->cont = novo_no;
}

int main()
{
    tipo_lista *minha_lista;
    minha_lista = NULL;

    int cont1, i, j;
    clock_t t;

    // Inicializa o gerador de numeros randomicos, a partir de uma semente
    srand(time(NULL));

    // INSERCAO NO INICIO
    //---------------------------------------------------------------------------------------------------------
    printf("\n\nINSERCAO NO INICIO\n");
    printf("-----------------------------------------------------------------------------------------\n");
    t = clock();
    for (cont1 = 0; cont1 < 3333; cont1++)
    { // laço que gera randomicamente 3333 numeros para serem alocados
        i = rand() % 1000000;
        insereInicioLista(&minha_lista, i);
    }
    t = clock() - t;
    printf("Tempo: %lf milissegundos\n\n", ((double)t) / ((CLOCKS_PER_SEC / 1000)));
    printf("-----------------------------------------------------------------------------------------\n");
    //---------------------------------------------------------------------------------------------------------

    // INSERCAO NO FIM
    //---------------------------------------------------------------------------------------------------------
    printf("\n\nINSERCAO NO FIM\n");
    printf("-----------------------------------------------------------------------------------------\n");
    t = clock();
    for (cont1 = 0; cont1 < 3333; cont1++)
    { // laço que gera randomicamente 3333 numeros para serem alocados
        i = rand() % 1000000;
        insereFimLista(&minha_lista, i);
    }
    t = clock() - t;
    printf("Tempo: %lf milissegundos\n\n", ((double)t) / ((CLOCKS_PER_SEC / 1000)));
    printf("-----------------------------------------------------------------------------------------\n");
    //---------------------------------------------------------------------------------------------------------

    // INSERCAO EM POSICOES ALEATORIAS
    //---------------------------------------------------------------------------------------------------------
    printf("\n\nINSERCAO EM POSICOES ALEATORIAS\n");
    printf("-----------------------------------------------------------------------------------------\n");
    t = clock();
    for (cont1 = 0; cont1 < 3334; cont1++)
    { // laço que gera randomicamente 3333 numeros para serem alocados
        i = rand() % 1000000;
        j = rand() % 10000;
        inserePosLista(&minha_lista, j, i);
    }
    t = clock() - t;
    printf("Tempo: %lf milissegundos\n\n", ((double)t) / ((CLOCKS_PER_SEC / 1000)));
    printf("-----------------------------------------------------------------------------------------\n");
    //---------------------------------------------------------------------------------------------------------
    printf("\n\n\n");
    // imprimeLista(&minha_lista);

    return 0;
}