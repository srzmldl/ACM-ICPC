#include <bits/stdc++.h>
#define MAXN 112

using namespace std;

char a[MAXN][MAXN];

int vis[MAXN][MAXN], haveTo[MAXN][MAXN];
int main()
{
    freopen("a1.in", "r", stdin);
    freopen("a1.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        int R, C;
        scanf("%d%d", &R, &C);
        memset(vis, 0, sizeof(vis));
        memset(haveTo, 0, sizeof(haveTo));
        for (int i = 0; i < R; ++i)
            scanf("%s", a[i]);
        for (int i = 0; i < R; ++i)
        {
            for (int j = 0; j < C; ++j)
                if (a[i][j] != '.')
                {
                    vis[i][j]++;
                    if (a[i][j] == '<') haveTo[i][j] = 1;
                    break;
                }
            for (int j = C - 1; j >= 0; --j)
                if (a[i][j] != '.')
                {
                    vis[i][j]++;
                    if (a[i][j] == '>') haveTo[i][j] = 1;
                    break;
                }
        }

        for (int j = 0; j < C; ++j)
        {
            for (int i = 0; i < R; ++i)
                if (a[i][j] != '.')
                {
                    vis[i][j]++;
                    if (a[i][j] == '^') haveTo[i][j] = 1;
                    break;
                }
            for (int i = R - 1; i >= 0; --i)
                if (a[i][j] != '.')
                {
                    vis[i][j]++;
                    if (a[i][j] == 'v') haveTo[i][j] = 1;
                    break;
                }
        }

        int flag = 1, ans = 0;
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (haveTo[i][j])
                {
                    ans++;
                    if (vis[i][j] == 4) flag = 0;
                }
        if (flag) printf("%d\n", ans);
        else printf("IMPOSSIBLE\n");
    }
    return 0;
}
