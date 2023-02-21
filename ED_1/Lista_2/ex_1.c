#include <stdio.h>


int main(){
    double a=0, M[12][12];
    char T;
    int C,x,y,z,p=1;
    scanf("%s", &T);
    for(x=0;x<=11;x++)
    {
        for(y=0; y<=11; y++)
            scanf("%lf", &M[x][y]);
    }
    for(z=0; z<=11;z++)
    {
        for(C=p; C<=11;C++)
            a+=M[z][C];
        p++;
    }
    if(T =='S')
        printf("%.1lf\n",a);
    else if(T =='M')
    {
        a=a/66.0;
        printf("%.1lf\n",a);
    }
    return 0;
}