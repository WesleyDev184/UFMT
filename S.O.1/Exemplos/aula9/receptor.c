#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 4096

int main(int argc, char const *argv[])
{
  const char *name = "memoria compartilhada";
  int fd = shm_open(name, O_RDONLY, 0666);

  if (fd == -1)
  {
    printf("Erro na abertura da memória compartilhada!\n");
    exit(-1);
  }

  void *ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

  if (ptr == MAP_FAILED)
  {
    printf("Erro no mapeamento da memória compartilhada!\n");
    exit(-1);
  }

  printf("%s\n", (char *)ptr);
  munmap(ptr, SIZE); // desfaz o mapeamento
  shm_unlink(name); // remove a memória compartilhada
  return 0;
}