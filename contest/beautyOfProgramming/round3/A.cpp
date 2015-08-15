#include <bits/stdc++.h>
#define MAXN 1123456
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];


int main()
{
    freopen("A.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n, S;
        scanf("%d%d", &n, &S);
        num = 0;
        for (int i = 1; i <= n; ++i)
        {
            fir[i] = 0;
            cnt[i] = 0;
            vis[i] = 0;
            d[i] = 0;
        }
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            link(u, v);
            link(v, u);
        }
    }
    return 0;
}
