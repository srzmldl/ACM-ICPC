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
    freopen("b.in", "r", stdin);
    freopen("bbig.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        int N;
        double X, V;
        scanf("%d%lf%lf", &N, &V, &X);
        double H = 0;
        double minC = 1e6;
        double maxC = -1e6;
        for (int i = 1; i <= N; ++i)
        {
            scanf("%lf%lf", &g[i].R, &g[i].C);
            minC = min(minC, g[i].C);
            maxC = max(maxC, g[i].C);
            H += g[i].R * g[i].C;
        }
        int u1 = cmp(minC, X);
        int u2 = cmp(maxC, X);
        if ((u1 == u2) && (u1 != 0))
        {
            printf("IMPOSSIBLE\n");
            continue;
        }
        else printf("%.8lf\n", X * V / H);
        //for (int i = 1; i <= N; ++i)
        // {
            
        //}
    }
    return 0;
}
