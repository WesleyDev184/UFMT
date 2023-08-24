#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void trata_sinal(int sinal)
{
    printf("\n Tempo esgotado %d\n", sinal);
}

int main()
{
    signal(SIGALRM, trata_sinal);
    alarm(5);
    while (1)
    {
        printf("Esperando sinal alarme\n");
        sleep(1);
    }

    return 0;
}
