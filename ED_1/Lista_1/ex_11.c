#include <stdio.h>

int main(){
    
    double val[6] = {}, a = 0, x = 0;
    int b = 0;

    for (int i = 0; i < 6; i++) {
        scanf("%lf", &val[i]);

        if (val[i] > 0) {
            b++;
            a+=val[i];
        };
    }

    x = a/b;

    printf("%d valores positivos\n",b);
    printf("%.1lf\n", x);
   
    return 0;
}