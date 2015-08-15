#include <bits/stdc++.h>
#define MAXN 212345

using namespace std;
typedef int arrayN[MAXN];
typedef long long ll;

int num;
arrayN fir ,e, nxt, p, c;

struct node
{
    int p, fa;
    ll dps, dpf, psum;
} g[MAXN];

void link(int u, int v, int w)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, c[num] = w;
}

void dfs(int x, int fa)
{
    g[x].psum = g[x].p;
    g[x].fa = fa;
    g[x].dps = g[x].dpf = 0;
    for (int p = fir[x]; p; p = nxt[p])
        if (e[p] != fa)
        {
            dfs(e[p], x);
            g[x].dps += g[e[p]].dps + 1LL * c[p] * g[e[p]].psum;
            g[x].psum += g[e[p]].psum;
        }
}

void dfsdpf(int x, int fa, int w)
{
    if (fa != 0)
    {
        g[x].dpf = g[fa].dpf + g[fa].dps - (g[x].dps + 1LL * w * g[x].psum);
        g[x].dpf += (g[1].psum - g[x].psum) * w;
    }
    for (int p = fir[x]; p; p = nxt[p])
        if (e[p] != fa)
            dfsdpf(e[p], x, c[p]);
}

int main()
{
    freopen("house.in", "r", stdin);
    freopen("house.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &g[i].p);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        link(u, v, w);
        link(v, u, w);
    }
    dfs(1, 0);
    dfsdpf(1, 0, 0);
    int lab = 1;
    ll ans = g[1].dps + g[1].dpf;
    for (int i = 2; i <= n; ++i)
        if (g[i].dps + g[i].dpf < ans)
        {
            lab = i;
            ans = g[i].dps + g[i].dpf;
        }
    cout << lab << ' ' << ans << endl;
    return 0;
}
