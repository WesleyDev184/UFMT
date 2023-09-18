#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main (){
    pid_t id = fork();

    if(id<0){
        printf("Error for creating the process\n");
        return 1;

    }
    if(id==0){
        //prcesso filho


        close(STDOUT_FILENO);
        open("./saida.txt", O_CREAT | O_WRONLY |O_TRUNC, S_IRWXU);
        execlp("/usr/bin/ls","meu-ls", "-l",NULL);
        perror("execlp falhou \n");
        printf("nunca vai chegar aqui\n");
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