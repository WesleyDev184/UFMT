#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
  char *m;
  int men_size;
  int count = 0;

  if (argc < 2)
  {
    printf("uso: %s <men_size em kb>\n", argv[0]);
    exit(0);
  }

  men_size = atoi(argv[1]);
  m = (char *)malloc(men_size * 1024);

  if (m == NULL)
  {
    printf("Erro ao Alocar a memoria:\n");
    exit(0);
  }

  printf("Memoria Alocada: %d kbi\n", men_size);

  while (1)
  {
    m[count] = 'x';
    count++;
    if (count == men_size * 1024)
    {
      count = 0;
    }
  }

  return 0;
}
