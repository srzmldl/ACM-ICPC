#include <bits/stdc++.h>
#define MAXN 111
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;

int a[MAXN], vis[MAXN];
int f[40], g[40];

int main()
{
    freopen("c1.in", "r", stdin);
    freopen("c1.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int C, D, V;
        scanf("%d%d%d", &C, &D, &V);
        for (int i = 1; i <= D; ++i)
            scanf("%d", a + i);
        int ans = 0;
        long long lim = 0;
        lim = 0;
        if (lim < V)
            for (int i = 1 ; i <= D; ++i)
            {
                if (a[i] <= lim + 1) lim = 1LL * C * a[i] + lim;
                else
                {
                    ans++;
                    lim = 1LL * C * (lim + 1) + lim;
                    --i;
                }
                if (lim >= V) break;
            }
        for (; lim < V;)
        {
            ans++;
            lim += 1LL * C * (lim + 1);
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
