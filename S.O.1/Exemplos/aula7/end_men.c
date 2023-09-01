#include <stdio.h>
#include <stdlib.h>

int main()
{
  int x;
  char *p = (char *)malloc(10);

  printf("Endereço do heap: %p\n", p);
  printf("Endereço do stack: %p\n", &x);
  printf("Endereço do código: %p\n", main);
  return 0;
}
