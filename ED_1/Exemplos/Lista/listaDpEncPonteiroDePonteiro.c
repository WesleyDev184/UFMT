/*
* UFMT - Ciencia da Computacao
* Estrutura de Dados 1
* Prof Ivairton
* Discentes: Claudio Antonio Nery de Oliveira, Lucas Barbosa Amaral 
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// criacao da estrutura
struct est_No
{
    int valor;
    struct est_No *prox;
    struct est_No *ant;
};
typedef struct est_No tipoNo;

// prototipo das funcoes
void insereFimLista(tipoNo **lst, int vlr);
void insereInicioLista(tipoNo **lst, int vlr);
void inserePosiLista(tipoNo **lst, int pos, int vlr);

int main()
{
    tipoNo *minha_lista; // criacao da variavel a partir da estrutura
    minha_lista = NULL;

    int cont1, i, j; // inicia as variaveis
    clock_t t;       // define a variavel da funcao time para gerar os numeros randomicos

    // Inicializa o gerador de números randomicos, a partir de uma semente
    srand(time(NULL));

    //---------------------------------------------------------------------------------------------------------
    printf("\n\nINSERCAO NO INICIO\n");
    printf("-----------------------------------------------------------------------------------------\n");
    t = clock();
    for (cont1 = 0; cont1 < 3333; cont1++)
    {
        i = rand() % 1000000;
        insereInicioLista(&minha_lista, i);
    }
    t = clock() - t;
    printf("Tempo: %lf milissegundos\n\n", ((double)t) / ((CLOCKS_PER_SEC / 1000)));
    printf("-----------------------------------------------------------------------------------------\n");
    //---------------------------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------------------------
    printf("\n\nINSERCAO NO FIM\n");
    printf("-----------------------------------------------------------------------------------------\n");
    t = clock();
    for (cont1 = 0; cont1 < 3333; cont1++)
    {
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
    {
        i = rand() % 1000000;
        j = rand() % 10000;
        inserePosiLista(&minha_lista, j, i);
    }
    t = clock() - t;
    printf("Tempo: %lf milissegundos\n\n", ((double)t) / ((CLOCKS_PER_SEC / 1000)));
    printf("-----------------------------------------------------------------------------------------\n");
    //---------------------------------------------------------------------------------------------------------
    printf("\n\n\n");

    // imprimeLista(&minha_lista);

    return 0;
}

// Funcao que insere no fim da lista
void insereFimLista(tipoNo **lst, int vlr)
{
    tipoNo *novoNo, *aux;
    int pont = 0;

    // percorre a lista ate o ultimo noh
    aux = *lst;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
        pont++;
    }
    inserePosiLista(lst, pont, vlr);
}

//realiza a inserção no fim a partir da chamada da função inserePosLista na posição do ponteiro de ponteiro que aponta para o contador(pós quantidade de valores no vetor)
void insereInicioLista(tipoNo **lst, int vlr)
{
    inserePosiLista(lst, 0, vlr);
}

// insere um valor em uma posicao especifica
void inserePosiLista(tipoNo **lst, int pos, int vlr)
{
    int cont;
    tipoNo *novoNo, *aux, *aux_ant;
    novoNo = (tipoNo *)malloc(sizeof(tipoNo));
    novoNo->valor = vlr;
    cont = 0;
    aux = (*lst);

    while ((cont < pos) && (aux != NULL))
    {
        cont = cont + 1;
        aux_ant = aux;
        aux = aux->prox;
    }

    // verifica o contexto da parada do enquanto
    if ((cont == pos) && (pos > 0))
    {
        novoNo->prox = aux;
        aux_ant->prox = novoNo;
    }
    else
    {
        novoNo->prox = *lst;
        *lst = novoNo;
    }
}