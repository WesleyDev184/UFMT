#include <stdlib.h>
#include <stdio.h>

#include "teste.c"
int main(int argc,char *argv[]){
    if(argc==2){
        FILE *arq_entrada;
        arq_entrada = fopen(argv[0],"r");

        if(arq_entrada == NULL){
            printf("[ERRO] Não foi possivel abrir o arquivo");
            return 0;
        }else{
            
            char cmd[10];
            int valor;

            tipo_pilha minha_pilha;
            minha_pilha.cont = 0;
            //cmd = fgetc (arq_entrada);
            
            while(fscanf(arq_entrada, "%s",cmd)==1){
                switch (cmd[0])
                {
                case 'E':
                    fscanf(arq_entrada,"%d", &valor);
                    break;
                case 'D':
                    valor = desempilha(&minha_pilha);
                    break;
                case 'P':
                    imprimePilha(minha_pilha);
                    break;
                
                default:
                    break;
                }

            }
        }


      
        


    }else{
        printf("[ERRO]Numero de parametros incorreto.Para execução do programa é necessario informar o nome ");
        printf("\t $ %s arquivo_entrada.txt",argv[0]);
        return 0;
    }
    



}