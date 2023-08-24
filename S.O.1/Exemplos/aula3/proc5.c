#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main (){
    pid_t id = fork();

    if(id<0){
        printf("Error for creating the process\n");
        return 1;

    }
    if(id==0){
        execlp("/usr/bin/ls","ls", "-l",NULL);
        perror("execlp falhou \n");
        printf(" nunca vai chegar aqui\n");
        return 1;
    }
    else {
        

        //printf("Processo pai aguardando o filho terminar ...\n");
        //wait(NULL);//processo pai
        sleep(10);
        printf("Processo pai chegando ao fim . . . \n");

    }
    return 0;
}