#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void trata_sinal(int sinal)
{
    printf("\nAqui nao, vagabundo %d\n", sinal);
}

int main()
{
    signal(SIGINT, trata_sinal);
    while (1)
    {
        printf("Processo chato do caralho\n");
        sleep(1);
    }

    return 0;
}
