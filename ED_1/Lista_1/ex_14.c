#include <stdio.h>

int main()
{

    int x=0, y=0, a=0;

    scanf("%d %d", &x, &y);
    if ((1 <= x <= 20) && (y < 100000))
    {
        for (int i = 1; i <= y; i++)
        {
            a++;
            if (a == x)
            {
                printf("%d\n", i);
                a = 0;
            }
            else
            {
                printf("%d ", i);
            }
        }
    }
    return 0;
}