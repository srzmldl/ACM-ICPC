#include <bits/stdc++.h>
#define MO 100007
#define MAXN 3000

using namespace std;

struct node
{
    int l, r, w;
}g[MAXN];

int tot, b[MAXN];

int com(node A, node B)
{
    return A.l < B.l || (A.l == B.l && A.r < B.r);
}

double areaS(double x)
{
    return x / 2.0 * x / 2.0;
}

int flod(node A, node B)
{
    if (A.r <= B.l) return 0;
    return A.r - B.l;
}

int main()
{
    // freopen("B.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
        {
            int x, y, w;
            scanf("%d%d%d", &x, &y, &w);
            g[i].l = x - y;
            g[i].r = x + y;
            g[i].w = w;
        }
        sort(g, g + N, com);
        double ans = 0;
        for (int i = 1; i < (1 << N); ++i)
        {
            int tot = 0;
            int maxR = 0;
            double tmp = 0;
            for (int j = 0; j < N; ++j)
                if (i & (1 << j))
                {
                    tmp += g[j].w;
                    if (g[j].r <= maxR)
                        continue;
                    b[tot++] = j;
                    maxR = g[j].r;
                    tmp -= areaS(g[j].r - g[j].l);
                    if (tot >= 2)
                    {
                        tmp += areaS(flod(g[b[tot - 2]], g[j]));
                    }
                }
            ans = max(ans, tmp);
        }
        printf("Case #%d: %.2f\n", t, ans);
    }
    return 0;
}
