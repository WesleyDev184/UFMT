#include <stdio.h>

int subfunc(int, int);

int main() {
    int a;
    a = subfunc(3, 2);
    printf("A subtracao dos numeros e: %d\n", a);
    return 0;
}