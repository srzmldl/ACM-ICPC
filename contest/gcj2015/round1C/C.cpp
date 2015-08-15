#include <bits/stdc++.h>
#define MAXN 111
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;

int a[MAXN], vis[MAXN];
int f[40], g[40];

int check(int V)
{
    MST(f, 0);
    MST(g, 0);
    f[0] = 1;
    vector<int> vec;
    for (int j = 1; j <= V; ++j)
        if (vis[j]) vec.push_back(j);
    for (int j = 0; j < vec.size(); ++j)
    {
        for (int i = 0; i <= V; ++i)
            g[i] = f[i];
        for (int i = 0; i <= V; ++i)
        {
            if (f[i] && i + vec[j] <= V)
                g[i + vec[j]] = 1;
        }
        for (int i = 0; i <= V; ++i)
            f[i] = g[i];
    }
    for (int i = 1; i <= V; ++i)
        if (f[i] == 0) return 0;
    return 1;
}

int dfs(int deep, int nowdp, int last, int V)
{
    if (nowdp == deep)
    {
        if (check(V)) return 1;
        return 0;
    }
    for (int i = last + 1; i <= V; ++i)
        if (!vis[i])
        {
            vis[i] = 1;
            if (dfs(deep, nowdp + 1, i, V))
                return 1;
            vis[i] = 0;
        }
    return 0;
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int C, D, V;
        scanf("%d%d%d", &C, &D, &V);
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= D; ++i)
        {
            scanf("%d", a + i);
            vis[a[i]] = 1;
        }
        int ans = 0;
        for (int i = 1; i <= min(V, 2); ++i)
            if (!vis[i])
            {
                vis[i] = 1;
                ans++;
            }
        int flag = 0;
        for (int deep = 0; deep <= 3 && !flag; ++deep)
        {
            flag = dfs(deep, 0, 0, V);
            if (flag) ans += deep;
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
