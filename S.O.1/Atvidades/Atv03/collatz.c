#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX 4096

void aloca_memoria_compartilhada(int *fd, int **ptr, size_t size)
{
  const char *name = "/memoria_compartilhada";
  *fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(*fd, size);
  *ptr = (int *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
  if (*ptr == MAP_FAILED)
  {
    perror("mmap");
    exit(1);
  }
}

void le_memoria_compartilhada(int *fd, int **ptr, size_t size)
{
  const char *name = "/memoria_compartilhada";
  *fd = shm_open(name, O_RDONLY, 0666);
  *ptr = (int *)mmap(NULL, size, PROT_READ, MAP_SHARED, *fd, 0);
  if (*ptr == MAP_FAILED)
  {
    perror("mmap");
    exit(1);
  }
}

int main(int argc, char const *argv[])
{
  int pid;
  int *fd;
  int *ptr;
  char input[MAX];

  pid = fork();

  if (pid == 0)
  {
    printf("Digite um numero: ");
    fgets(input, MAX, stdin);
    int num = atoi(input);
    aloca_memoria_compartilhada(&fd, &ptr, sizeof(int) * (num + 1));
    ptr[0] = num;

    int count = 1;

    while (num != 1)
    {
      if (num % 2 == 0)
      {
        num = num / 2;
      }
      else
      {
        num = 3 * num + 1;
      }

      ptr[count] = num;
      count++;
    }

    ptr[count] = -1; // Marca o final da sequência
  }
  else
  {
    wait(NULL);
    le_memoria_compartilhada(&fd, &ptr, MAX);

    printf("Sequencia de Collatz: ");
    int i = 0;
    while (ptr[i] != -1)
    {
      printf("%d ", ptr[i]);
      i++;
    }

    printf("\n");
    shm_unlink("/memoria_compartilhada");
  }

  return 0;
}
