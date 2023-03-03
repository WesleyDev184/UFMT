#include <stdlib.h>
#include <stdio.h>

#define N 10


struct str_pilha{
    int pilha[N];
    int cont;
};

typedef struct str_pilha tipo_pilha;

void empilha(tipo_pilha*,int);
int desempilha(tipo_pilha*);
int topo(tipo_pilha);
tipo_pilha copia_pilha(tipo_pilha);
int verificaPilhaVazia(tipo_pilha );
int verificaPilhaCheia(tipo_pilha );
void imprimePilha(tipo_pilha);



void empilha(tipo_pilha*pl,int valor){
    if(verificaPilhaCheia(*pl)){
        printf("[ERRO] PILHA ESTA CHEIA, NADA SERA FEITO");
    }else{
    pl->pilha[pl->cont++]=valor;
    }
}
int desempilha(tipo_pilha *pl){
    int valor;
    if(verificaPilhaVazia(*pl)){
        printf(" [ERRO] Pilha vazia, desempilha não será processado");
        return -1;

    }else{
        valor = pl->pilha[--pl->cont];
    }
}
int verificaPilhaVazia(tipo_pilha pl){
    if(pl.cont ==0){
        return 1;
    }else{return 0;}
}

int verificaPilhaCheia(tipo_pilha pl){
    if(pl.cont<N){
        return 0;
    }else{
        return 1;
    }
}
int topo(tipo_pilha pl){
    if(verificaPilhaVazia(pl)){
        printf("[ERRO] Pilha não tem elemento no topo \n");
        return -1;
    }else{
        return pl.pilha[pl.cont-1];
    }

}


void imprimePilha(tipo_pilha pl){
    int i;
    printf("Estrutura pilha:\nQtd de valores = %d; Capacidade de %d;",pl.cont,N);
    printf("Base da pilha [");
    for(i=0;i<pl.cont;i++)
        printf("%d ", pl.pilha[i]);
    printf("<-topo\n");
}
