#include <bits/stdc++.h>

#define MAXN 412

using namespace std;

int ans[5][100];
int vis[MAXN][MAXN];

int ok, n = 4;


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

void check(int lim)
{
    memset(vis, 0, sizeof(vis));
    ok = 1;
    for (int i = 0; i <= lim; ++i)
        dye(i, n);
}

int main()
{
    //  freopen("a.out", "w", stdout);
    n = 6;
    for (int i = 1; i <= n * 2; ++i)
    {
        ans[0][i] = i;
        ans[1][i] = i;
    }
    ok = 0;
    do{
        check(1);
        if (!ok)
        {
            ok = 0;
            continue;
        }
        for (int i = 1; i <= n * 2; ++i)
            ans[2][i] = i;
        do{
            check(2);
            if (ok) break;
        } while (next_permutation(ans[2] + 1, ans[2] + n * 2 + 1));
        // for (int i = 1; i <= 8; ++i)
        //    cout << ans[2][i] << endl;
        if (ok) break;
    } while ( next_permutation(ans[1] + 1, ans[1] + n * 2 + 1));
    for (int i = 0; i <= 2; ++i)
        for (int j = 1; j <= n * 2; ++j)
            cout << ans[i][j] << ' ';
    cout << ok << endl;
    return 0;
}
