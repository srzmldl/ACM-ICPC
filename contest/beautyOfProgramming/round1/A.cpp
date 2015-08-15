#include <bits/stdc++.h>
#define MO 100007
#define MAXN 210000
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

arrayN fir, nxt, e, col;
int num;

void link(int u, int v)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

int main()
{
    //freopen("A.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n;
        scanf("%d", &n);
        MST(fir, 0);
        MST(col, 0);
        num = 0;
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            link(u, v);
            link(v, u);
        }
        int q;
        int ans = 1;
        printf ("Case #%d:\n", t);
        for (scanf("%d", &q); q; --q)
        {
            int k;
            scanf("%d", &k);
            if (k == 1) printf("%d\n", ans);
            else
            {
                int x, y;
                scanf("%d%d", &x, &y);
                for (int p = fir[x]; p; p = nxt[p])
                {
                    if (col[e[p]] == col[x] && y != col[x])
                        ans++;
                    else if (col[e[p]] != col[x] && y == col[e[p]])
                        ans--;
                }
                col[x] = y;
            }
        }
    }
    return 0;
}
