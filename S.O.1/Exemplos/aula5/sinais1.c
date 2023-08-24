#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void trata_sinal(int sinal)
{
    printf("\n received %d\n", sinal);
}

int main()
{
    // signal(SIGTERM, SIG_IGN); //ignora sigterm ctrt +c
    signal(SIGTERM, trata_sinal); // Trata sigterm signal ctrt + c
    for (;;)
    {
        printf("\nha ha\n");
        sleep(1);
    }
}
