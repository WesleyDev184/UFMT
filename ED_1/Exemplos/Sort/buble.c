#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct lista_aloc
{
    int qtd;
    int capacidade;
    int *vet;
};
typedef struct lista_aloc tipo_lista;

// prototipação
void bubbleSort(tipo_lista *);

void shellSort(tipo_lista *);
void insertSort(tipo_lista *);
void insereLista(tipo_lista *, int);
void inicializaLista(tipo_lista *, int);
void imprimeLista(tipo_lista *);

int main()
{

    int i, tamanho;
    tipo_lista minha_lista;
    inicializaLista(&minha_lista, 10);
    srand(1);

    for (i = 0; i < 10; i++)
    {
        insereLista(&minha_lista, rand() % 100);
    }

    imprimeLista(&minha_lista);

    shellSort(&minha_lista);

    imprimeLista(&minha_lista);

    return 0;
}

void inicializaLista(tipo_lista *lst, int tamanho)
{
    lst->capacidade = tamanho;
    lst->qtd = 0;
    lst->vet = (int *)malloc(sizeof(int) * tamanho);
}
void insereLista(tipo_lista *lst, int valor)
{
    if (lst->qtd < lst->capacidade)
    {
        lst->vet[lst->qtd++] = valor;
    }
}
/*
void bubbleSort(tipo_lista*lst){
    int flagTroca, aux, i;

    flagTroca = 1;
    do{
        flagTroca = 0;
        for(i = 0; i< lst->qtd-1;i++){
            if(lst->vet[i]> lst->vet[i+1]){
                aux = lst->vet[i];
                lst->vet[i] = lst->vet[i+1];
                lst->vet[i+1] = aux;
                flagTroca = 1;
            }
        }
    }while(flagTroca == 1);
    printf("ultimo valor ->  %d", lst->vet[i]);
}
*/
/*
void shellSort(tipo_lista* lst){
    int  auxValor, salto, flagTroca, k;

    salto = lst->qtd/2;
    if(salto % 2 == 0){
        salto++;
    }
    do{
        for(int i = 0;i< salto ;i++){
            for(int j = i + salto;j<lst->qtd;j++){
                auxValor = lst->vet[i];
                lst->vet[i] = lst->vet[j];
                lst->vet[j] = auxValor;
                //verifica valores anteriores a atual posição
                flagTroca = 1;
                k = i;
                do{
                    flagTroca = 0;
                    if (lst->vet[k]< lst->vet[k-salto]){
                        auxValor = lst->vet[k];
                        lst->vet[k] = lst->vet[k-salto];
                        lst->vet[k-salto] = auxValor;
                        flagTroca = 1;
                        k = k-salto;
                    }
                    }while(flagTroca == 1);
            }
        }
    }while(salto >= 1);

    salto = salto/2;
    if(salto % 2 != 0){
        salto++;
    }
}
*/
/**/
void shellSort(tipo_lista *lst)
{
    int auxValor, salto, flagTroca, k;

    // definir o primeiro salto como a metade do tamanho da lista
    salto = lst->qtd / 2;

    // se o salto for par, torná-lo ímpar para garantir que não seja um múltiplo de um salto menor
    if (salto % 2 == 0)
    {
        salto++;
    }

    // iniciar o loop do algoritmo shellSort, executando repetidamente a ordenação para cada salto menor até que não haja mais salto para executar
    do
    {
        // calcular o próximo valor de salto, dividindo por dois
        salto = salto / 2;

        // loop interno para executar a ordenação para o salto atual
        for (int i = 0; i < salto; i++)
        {
            // loop interno para executar a ordenação para cada sublista com o salto atual
            for (int j = i + salto; j < lst->qtd; j++)
            {
                // armazenar o valor atual para ser comparado e movido para a posição correta
                auxValor = lst->vet[j];
                k = j;
                // loop para mover os valores na sublista para a posição correta, usando o salto atual
                while (k >= salto && lst->vet[k - salto] > auxValor)
                {
                    lst->vet[k] = lst->vet[k - salto];
                    k = k - salto;
                }
                // colocar o valor atual na posição correta na sublista
                lst->vet[k] = auxValor;
            }
        }
    } while (salto > 0); // o loop continua enquanto ainda houver salto para executar
}

void insertSort(tipo_lista *lst)
{
    tipo_lista lst_ordenada;
    inicializaLista(&lst_ordenada, lst->capacidade);

    int pos_lst, i;
    for (i = 0; i < lst->qtd; i++)
    {
        pos_lst = lst_ordenada.qtd;
        while ((pos_lst > 0) && (lst->vet[i] < lst_ordenada.vet[pos_lst - 1]))
        {
            lst_ordenada.vet[pos_lst] = lst_ordenada.vet[pos_lst - 1];
            pos_lst--;
        }
        lst_ordenada.vet[pos_lst] = lst->vet[i];
        lst_ordenada.qtd++;
    }
    for (i = 0; i < lst->qtd; i++)
    {
        lst->vet[i] = lst_ordenada.vet[i];
    }
}

void imprimeLista(tipo_lista *lst)
{
    printf("Capacidade Lista -> %d \n  quantidade Lista -> %d \n", lst->capacidade, lst->qtd);
    for (int i = 0; i < lst->qtd; i++)
    {
        printf("  [%d]  ", lst->vet[i]);
    }
}