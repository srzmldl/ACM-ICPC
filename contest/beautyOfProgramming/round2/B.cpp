#include <bits/stdc++.h>
#define MO 100007
#define MAXN 1123456
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

arrayN f, lab, c;

int getfa(int x)
{
    if (x == f[x]) return f[x];
    return f[x] = getfa(f[x]);
}

int com(int u, int v)
{
    return c[u] < c[v];
}

int main()
{
    freopen("B.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n, m, k;
        cout << "Case #" << t << ": ";
        scanf("%d%d%d", &n, &m, &k);
        //    n = 1000000;
        //m = 0;
        //k = 1000000;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", c + i);
            //  c[i] = 100000000;
            f[i] = i;
            lab[i] = i;
        }
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            int fu = getfa(u);
            int fv = getfa(v);
            if (fu == fv) continue;
            if (c[fu] < c[fv])
                f[fv] = fu;
            else f[fu] = fv;
        }
        sort(lab + 1, lab + n + 1, com);
        long long ans = 0;
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (f[i] == i)
            {
                ans += c[i];
                cnt++;
            }
        int neededge = n - cnt;
        k -= (m - neededge);
        for (int i = 1; i <= n && k >= 1; ++i)
            if (f[lab[i]] != lab[i])
            {
                k--;
                ans += c[lab[i]];
            }
        cout << ans << endl;
    }
    return 0;
}
