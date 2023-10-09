#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static int counter = 0;
// mutex
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread1(void *arg)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 1e6; i++)
    {
        counter++;
    }
    pthread_mutex_unlock(&mutex);
    printf("%s: pronto\n", (char *)arg);
    return NULL;    
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    printf("counter = %d\n", counter);
    pthread_create(&t1, NULL, thread1, "t1");
    pthread_create(&t2, NULL, thread1, "t2");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("counter = %d\n", counter);
    return 0;
}