#include <bits/stdc++.h>

#define MAXN 412

using namespace std;

int ans[3][MAXN], g[MAXN], vis[MAXN][MAXN];

int ok, n, flag[MAXN];

void color(int u, int v)
{
    if (u > n * 2 || v > n * 2) ok = 0;
    if (vis[u][v] + vis[v][u]) ok = 0;
    vis[u][v] = vis[v][u] = 1;
}


void dye(int k, int n)
{
    for (int i = 2; i <= n + 1; ++i)
    {
        color(ans[k][i], ans[k][i - 1]);
        if (i <= n) color(ans[k][i], ans[k][i + n]);
    }
}

int main()
{
    freopen("embedding.in", "r", stdin);
    freopen("embedding.out", "w", stdout);
    for (;;)
    {
        scanf("%d", &n);
        if (n == 0) break;
    // for (n = 3; n <= 100; ++n)
    // {
        if (n == 3)
        {
            printf("1 2 3 4 5 6\n1 4 5 3 2 6\n2 6 1 3 4 5\n");
            continue;
        }
        else if (n == 4)
        {
            printf("1 2 3 4 5 6 7 8\n1 7 2 8 3 6 4 5\n1 3 5 7 4 6 2 8 \n");
            continue;
        } else if (n == 5)
        {
            printf("1 2 3 4 5 6 7 8 9 10\n1 3 5 2 4 6 7 8 9 10\n1 4 7 6 3 9 8 5 2 10\n");
        }
        else
        {
            ok = 1;
            memset(vis, 0, sizeof(vis));
            for (int i = 1; i <= 2 * n; ++i)
                ans[0][i] = i;
        
            ans[1][1] = 1;
            ans[1][n + 1] = n + 1;
            for (int i = 2; i <= n; ++i)
                ans[1][i] = n + i;
            for (int i = n + 2; i < n * 2; ++i)
                ans[1][i] = i - n + 1;
            ans[1][n * 2] = 2;
        
            dye(0, n);
            dye(1, n);
            for (int i = 1; i <= (n + 1) / 2; ++i)
            {
                ans[2][i * 2 - 1] = i;
                ans[2][i * 2] = (i + 2 + n);
            }
            if ((n + 1) % 2)
                ans[2][n + 1] = (n + 1) / 2 + 1;
        
            for (int i = 2; i <= n + 1; ++i)
                color(ans[2][i], ans[2][i - 1]);

            ans[2][n + 3] = n + 1;
            color(ans[2][3], n + 1);
            int tot = 0;
            int sta = (n + 1) / 2 + 1;
            if ((n + 1) % 2)
            {
                g[++tot] = ((n + 1) / 2 + 1 + 2 + n);
                sta++;
            }
            for (int i = sta; i <= n - 2; ++i)
            {
                g[++tot] = i;
                g[++tot] = i + 2 + n;
            }
            g[++tot] = n - 1;
            g[++tot] = n;
            g[++tot] = n + 2;
            memset(flag, 0, sizeof(flag));
            for (int i = 2; i <= n; ++i)
                if (i != 3)
                {
                    int tmp = 0;
                    for (int j = 1; j <= tot; ++j)
                        if (!flag[j] && !vis[ans[2][i]][g[j]])
                        {
                            tmp = 1;
                            ans[2][i + n] = g[j];
                            color(ans[2][i], g[j]);
                            flag[j] = 1;
                            break;
                        }
                    if (!tmp) ok = 0;
                }
            for (int i = 0; i <= 2; ++i)
                for (int j = 1; j <= 2 * n; ++j)
                    printf("%d%c", ans[i][j], " \n"[j == 2 * n]);
            
            if (ok == 0) printf("!!!\n");
        }
        
    }
    return 0;
}
