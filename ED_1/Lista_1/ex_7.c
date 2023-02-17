#include <stdio.h>

int main(){

    int A,B;
    double X;

    double menu[5] = {4.00, 4.50, 5.00, 2.00, 1.50};

    printf("Digite o codigo do produto: \n");
    scanf("%d", &A);
    printf("Digite a quantidade: \n");
    scanf("%d", &B);

    X = menu[A-1] * B;

    printf("Total: R$ %.2lf \n", X);

    return 0;

}