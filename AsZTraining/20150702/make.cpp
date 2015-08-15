#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("jinxiety.in", "w", stdout);
    int t = 5;
    for (; t; t--)
    {
        int h = 2000;
        int w = 2000;
        printf("%d %d\n", h, w);
        for (int i = 1; i <= h; ++i)
        {
            for (int j = 1; j <= w; ++j)
                printf("#");
            printf("\n");
        }
    }
    printf("0 0\n");
    return 0;
}
