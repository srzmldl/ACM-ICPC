#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#define MAXN 1123

using namespace std;

struct node
{
    int x, y;
}g[MAXN];

int vis[MAXN], have[MAXN];

int com(node u, node v)
{
    return u.x < v.x;
}

int main()
{
    freopen("1003.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        int N, M;
        scanf("%d%d", &N, &M);
        int tot, ans = 0;
        scanf("%d", &tot);
        for (int i = 1; i <= tot; ++i)
            scanf("%d%d", &g[i].x, &g[i].y);
        memset(vis, 0, sizeof(vis));
        sort(g + 1, g + tot + 1, com);
        int tmp = 1;
        for (int i = 1; i <= tot; ++i)
            if (!vis[i])
            {
                int l = g[i].y, r = g[i].y;
                int last = g[i].x;
                int lans = l, rans = r;
                int lastAns = last;
                memset(have, 0, sizeof(have));
                for (int j = i + 1; j <= tot; ++j)
                {
                    if (g[j].x > last + 1) break;
                    have[g[j].y] = 1;
                    if (g[j].x == last + 1) last++;
                    for (; l > 1 && have[l - 1]; l--);
                    for (; r < M && have[r + 1]; r++);
                    int tt = (last - g[i].x + 1) * (r - l + 1);
                    if (tt > tmp)
                    {
                        tmp = tt;
                        lans = l, rans = r;
                        lastAns = last;
                    }
                }
                ans += tmp;
                for (int j = 1; j <= tot; ++j)
                    if (g[j].x >= g[i].x && g[j].x <= lastAns && g[j].y >= l && g[j].y <= r)
                        vis[j] = 1;
            }
        printf("%d\n", ans);
    }
    return 0;
}
