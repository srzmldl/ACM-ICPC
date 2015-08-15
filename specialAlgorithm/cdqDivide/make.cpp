#include <bits/stdc++.h>

using namespace std;

int random(int x)
{
    return rand() *rand() * rand() % x +1;
}

int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(0));
    int ca = 3;
    int lim = 10;
    printf("%d\n", ca);
    for (int ttt = 0; ttt < ca; ttt++)
    {
        int n = 5;
        printf("%d\n", n);
        for (int i = 0; i < n; i++)
            printf("%d %d %d\n", rand() % lim, rand() % lim, rand() % lim);
    }
}
