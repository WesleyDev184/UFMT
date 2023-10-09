#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SEQUENCE 4096

// seuqencia de collatz usando threads

typedef struct
{
  int *sequence;
  int size;
} collatz_sequence;

void *collatz(void *arg)
{
  collatz_sequence *cs = (collatz_sequence *)arg;
  int num = cs->sequence[0];
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
    cs->sequence[count] = num;
    count++;
  }
  cs->size = count;
  pthread_exit(NULL);
}

void *print_sequence(void *arg)
{
  collatz_sequence *cs = (collatz_sequence *)arg;
  int size = cs->size;
  int *sequence = cs->sequence;

  printf("Sequencia: ");
  for (int i = 0; i < size; i++)
  {
    printf("%d ", sequence[i]);
  }
  printf("\n");
  pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
  char buffer[MAX_SEQUENCE];
  printf("Digite um numero: ");
  fgets(buffer, MAX_SEQUENCE, stdin);

  pthread_t t1;

  collatz_sequence cs;
  cs.size = 0;
  cs.sequence = (int *)malloc(MAX_SEQUENCE * sizeof(int));
  cs.sequence[0] = atoi(buffer);

  pthread_create(&t1, NULL, collatz, &cs);

  pthread_join(t1, NULL);

  print_sequence(&cs);

  free(cs.sequence);

  return 0;
}