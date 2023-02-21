#include <stdio.h>

int main(){
    int N;

    do{
        scanf("%d", &N);

        if(N != 0)
        {
            int ara[N][N];

            for(int a = 0; a < N; a++)
            {
                for(int b = 0; b < N; b++)
                {
                    ara[a][b] = 1;
                }
            }

            int f = 1, g = 2, I = N - 1;

            for(int e = 0; e < I; e++)
            {
                for(int c = 0, d = f; d < N; d++, c++)
                {
                    ara[c][d] = g;
                }
                f++;
                g++;
            }

            for(int e = 0; e < I; e++)
            {
                for(int c = f, d = 0; c < N; d++, c++)
                {
                    ara[c][d] = g;
                }
                f++;
                g++;
            }

            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    if(j == 0)
                    {
                        printf("%3d", ara[i][j]);
                    }
                    else
                    {
                        printf(" %3d", ara[i][j]);
                    }
                }
                printf("\n");
            }

            printf("\n");
        }

    } while(N != 0);

    return 0;
}
