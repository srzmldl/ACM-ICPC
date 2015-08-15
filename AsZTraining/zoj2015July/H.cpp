#include <bits/stdc++.h>
#define MAXN 51234

using namespace std;
typedef int arrayN[MAXN];

arrayN fir, e, nxt, ans;
int g[MAXN * 4], num;

void link(int u, int v)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

int base;

void add(int x, int val)
{
    x += base;
    g[x] += val;
    for (x >>= 1; x; x >>= 1)
        g[x] = g[x << 1] + g[x << 1 ^ 1];
}

int ask(int l, int r)
{
    l += base - 1;
    r += base + 1;
    int tmp = 0;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) tmp += g[l + 1];
        if (r & 1) tmp += g[r - 1];
    }
    return tmp;
}

int main()
{
    //  freopen("H.in", "r", stdin);
    // freopen("H.out", "w", stdout);
    int n, m, q;
    for (; scanf("%d%d%d", &n, &m, &q) != EOF; )
    {
        num = 0;
        for (int i = 0; i <= n; ++i)
        {
            ans[i] = i;
            fir[i] = 0;
        }
        memset(g, 0, sizeof(g));
        for (base = 1; base <= n + 1; base <<= 1);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u > n || v > n) continue;
            link(v, u);
        }
        int l = 0;
        for (int r = 2; r <= n; ++r)
        {
            for (; l < r && ask(r, n) < 2;)
            {
                ++l;
                for (int p = fir[l]; p; p = nxt[p])
                    add(e[p], 1);
            }
            ans[r] = l;
        }

        for (int i = 1; i <= q; ++i)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", x - ans[x]);
        }
    }
    return 0;
}
