#include <bits/stdc++.h>
#define MAXN 112

using namespace std;

struct node
{
    double R, C;
}g[MAXN];

const double esp = 1e-8;

int cmp(double u, double v)
{
    if (fabs(u - v) < esp) return 0;
    if (u < v) return -1;
    return 1;
}

int main()
{
    freopen("bsmall.in", "r", stdin);
    freopen("bsmall.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        int N;
        double X, V;
        scanf("%d%lf%lf", &N, &V, &X);
        for (int i = 1; i <= N; ++i)
            scanf("%lf%lf", &g[i].R, &g[i].C);
        //small
        if (N == 1)
        {
            if (cmp(g[1].C, X) == 0)
                printf("%.8lf\n", V / g[1].R);
            else printf("IMPOSSIBLE\n");
        } else
        {
            if (cmp(g[1].C, g[2].C) == 0)
            {
                if (cmp(g[1].C, X) == 0)
                    printf("%.8lf\n", V / (g[1].R + g[2].R));
                else  printf("IMPOSSIBLE\n");
            } else
            {
                double V2 = V * (X - g[1].C) / (g[2].C - g[1].C);
                double V1 = V - V2;
                if (cmp(V1, 0) == -1 || cmp(V2, 0) == -1)
                    printf("IMPOSSIBLE\n");
                else printf("%.8lf\n", max(V1 / g[1].R, V2 / g[2].R));
            }
        }
    }
    return 0;
}
