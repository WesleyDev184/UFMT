#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
  char buf[BUFFER_SIZE];
  int n;

  open("arc1.c", O_RDONLY);

  while ((n = read(STDIN_FILENO, buf, BUFFER_SIZE)) > 0)
  {
    if (write(STDOUT_FILENO, buf, n) != n)
    {
      perror("write error");
      exit(1);
    }
  }
  return 0;
}
