#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    for ( ;; )
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            g[i].a = x;
            g[i].b = y - x;
            g[i].c = z - x;
        }
    }
    return 0;
}
