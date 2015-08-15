#include <bits/stdc++.h>
#define MAXN 33

using namespace std;
const int lim = 1123456;

int pri[lim], vis[lim];
long long ans[MAXN][MAXN];

int gcd(int u, int v)
{
    if (!u || !v) return u + v;
    return gcd(v, u % v);
}
int main()
{
    freopen("elegant.in", "r", stdin);
    freopen("elegant.out", "w", stdout);
    int tot = 0;
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= lim; ++i)
    {
        if (!vis[i]) pri[tot++] = i;
        for (int j = 0; j < tot && i * pri[j] < lim; ++j)
        {
            vis[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    int k1, k2;
    for (k1 = 2; gcd(k1, n) > 1; ++k1);
    if (n & 1)
    {
        for (k2 = k1 + 1; gcd(k2, n) > 1 || gcd(k2 - k1, n) > 1; ++k2);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int u = pri[(i + k1 * j) % n];
                int v = pri[(n + (i + k2 * j) % n)];
                printf("%d%c", u * v, " \n"[j == n - 1]);
            }
    }
    else
    {
        for (k2 = k1 + 1; gcd(k2, n) > 1; ++k2);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int u = pri[(i + j) % n];
                int v = pri[(n + (i - j + n) % n)];
                ans[i][j] = 1LL * u * v;
            }
        int m = n / 2;
        if (m & 1)
        {
            int base = n * 2, k3 = 2, k4;
            for (k4 = k3 + 1; gcd(k4, m) > 1 || gcd(k4 - k3, m) > 1; ++k4);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                {
                    ans[i][j] *= pri[base + (i + k3 * j) % m];
                    ans[i + m][j + m] *= pri[base + (i + k4 * j) % m];
                    ans[i][j + m] *= pri[base + m + (i + k3 * j) % m];
                    ans[i + m][j] *= pri[base + m + (i + k4 * j) % m];
                }
            base = n * 3;
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                {
                    int i1 = m - 1 - i;
                    int j1 = m - 1 - j;
                    ans[i1][j1] *= pri[base + (i + k3 * j) % m];
                    ans[i1 + m][j1 + m] *= pri[base + (i + k4 * j) % m];
                    ans[i1][j1 + m] *= pri[base + m + (i + k3 * j) % m];
                    ans[i1 + m][j1] *= pri[base + m + (i + k4 * j) % m];
                }
        } else
        {
            
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                {
                    int w;
                    if (i < n / 2) w = pri[n + n + ((i + j) & 1)];
                    else w = pri[n + n + (1 - ((i + j) & 1))];
                    ans[i][j] *= w;
                }
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                printf("%I64d%c", ans[i][j], " \n"[j == n - 1]);
    }
    return 0;
}
