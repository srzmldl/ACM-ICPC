#include <bits/stdc++.h>

using namespace std;

int random(int x)
{
    return abs(rand() * rand()) % x;
}

int main()
{
    freopen("hdu3507.in", "w", stdout);
    int t = 3;
    srand(time(0) % clock());
    for (int T = 1; T <= t; ++T)
    {
        int limN = 5, limM = 5;
        int limElem = 5;
        int n = random(limN);
        int m = random(limM);
        printf("%d %d\n", n, m);
        for (int i = 1; i <= n; ++i)
            printf("%d ", random(limElem));
        printf("\n");
    }
    return 0;
}
