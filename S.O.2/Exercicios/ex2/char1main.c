#include <stdio.h>

char firstChar(char *);
char nChar(char *, int);

int main()
{
  char *str = "you shall not pass";
  int poss = 4;
  printf("First char to string %s: %c\n", str, firstChar(str));
  printf("N char to string %s on position %d: %c\n", str,poss, nChar(str, poss));
  return 0;
}