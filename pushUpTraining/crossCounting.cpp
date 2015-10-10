#include<cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAXN 112

using namespace std;

struct node
{
    int l, r, u, d;
    int val;
} g[MAXN][MAXN];

int ans[MAXN];

int calc(int x, int y)
{
    return min(min(g[x][y].r - y, g[x][y].d - x), min(y - g[x][y].l, x - g[x][y].u));
}

int main()
{
    int n, m, C, Q;
    //  freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d", &n, &m, &C, &Q);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            scanf("%d", &g[i][j].val);
            g[i][j].l = g[i][j].r = j;
            g[i][j].u = g[i][j].d = i;
            if (g[i][j].val == g[i][j - 1].val)
                g[i][j].l = g[i][j - 1].l;
            if (g[i][j].val == g[i - 1][j].val)
                g[i][j].u = g[i - 1][j].u;
        }
    scanf("\n");
    for (int i = n; i >= 1; --i)
        for (int j = m; j >= 1; --j)
        {
            if (g[i][j].val == g[i][j + 1].val)
                g[i][j].r = g[i][j + 1].r;
            if (g[i][j].val == g[i + 1][j].val)
                g[i][j].d = g[i + 1][j].d;
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            ans[g[i][j].val] += calc(i, j);

    for (;Q; --Q)
    {
        char k;
        scanf("%c", &k);
        if (k == 'Q')
        {
            int c;
            scanf("%d\n", &c);
            printf("%d\n", ans[c]);
        } else
        {
            int x, y, c;
            scanf("%d%d%d\n", &x, &y, &c);
            for (int i = 1; i <= m; ++i)
                ans[g[x][i].val] -= calc(x, i);
            for (int i = 1; i <= n; ++i)
                if (i != x)
                    ans[g[i][y].val] -= calc(i, y);
            g[x][y].val = c;
            for (int i = 1; i <= n; ++i)
                g[i][y].u = (g[i][y].val == g[i - 1][y].val ? g[i - 1][y].u : i);
            for (int i = n; i >= 1; --i)
                g[i][y].d = (g[i][y].val == g[i + 1][y].val ? g[i + 1][y].d : i);
            for (int i = 1; i <= m; ++i)
                g[x][i].l = (g[x][i].val == g[x][i - 1].val ? g[x][i - 1].l : i);
            for (int i = m; i >= 1; --i)
                g[x][i].r = (g[x][i].val == g[x][i + 1].val ? g[x][i + 1].r : i);
            
            for (int i = 1; i <= m; ++i)
                ans[g[x][i].val] += calc(x, i);
            for (int i = 1; i <= n; ++i)
                if (i != x)
                    ans[g[i][y].val] += calc(i, y);
        }
    }
    return 0;
}