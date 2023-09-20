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
  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  char *msg = "Hello World!";
  // define o tamanho da memória compartilhada
  ftruncate(fd, SIZE);
  // mapeia a memória compartilhada
  void *ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
  // escreve na memória compartilhada
  sprintf(ptr, "%s", msg);
  return 0;
}
