#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Meu PID: %d\n",getpid());
    int id = fork();
    if (id < 0){
        printf("Failed to create the process!\n");
        return 1;
    }
    if(id ==0){
        printf("PID do filho: %d\n",getpid());
    }else{
        printf("PID do pai: %d\n",getpid());
    }
    return 0;
}