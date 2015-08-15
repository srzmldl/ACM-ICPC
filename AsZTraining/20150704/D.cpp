#include <bits/stdc++.h>
#define MAXN 110

using namespace std;

int vis[MAXN][MAXN];

struct node
{
    int tot, son[3];
} g[MAXN * 5];

int gcd(int u, int v)
{
    if (!u || !v) return u + v;
    return gcd(v, u % v);
}

int main()
{
    freopen("drunkard.in", "r", stdin);
    freopen("drunkard.out", "w", stdout);
    for (;;)
    {
        int p, q;
        scanf("%d%d", &p, &q);
        if (p + q == 0) break;
        int tmp = gcd(p, q);
        p /= tmp;
        q /= tmp;
        memset(vis, 0, sizeof(vis));
        memset(g, 0, sizeof(g));
        int lab = 1;
        vis[p][q] = 1;
        for (;;)
        {
            p *= 2;
            if (p >= q)
            {
                g[lab].son[++g[lab].tot] = -1;
                p -= q;
            }
            if (p == 0) break;
            int tmp = gcd(p, q);
            p /= tmp;
            q /= tmp;
            if (vis[p][q])
            {
                g[lab].son[++g[lab].tot] = vis[p][q];
                break;
            }
            g[lab].son[++g[lab].tot] = lab + 1;
            vis[p][q] = ++lab;
        }
        printf("%d\n", lab + 2);
        for (int i = 1; i <= lab; ++i)
        {
            int tmp = 1;
            for (int j = 1; j <= g[i].tot; ++j)
            {
                int ans = g[i].son[j];
                if (ans == -1) ans =  lab + 1;
                printf("%d", ans);
                if (tmp == 2) printf("\n");
                else printf(" ");
                ++tmp;
            }
            for (int j = tmp; j <= 2; ++j)
            {
                printf("%d", lab + 2);
                if (j == 2) printf("\n");
                else printf(" ");
            }
        }
    }
    return 0;
}
