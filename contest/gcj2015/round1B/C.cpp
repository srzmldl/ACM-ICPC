#include <bits/stdc++.h>
#define MAXN 20

struct node
{
    double D, M;
    node(double d = 0, double m = 0) : D(d), M(m) {};
} g[MAXN];

using namespace std;
    
int main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int N;
        scanf("%d", &N);
        int tot = 0;
        for (int i = 1; i <= N; ++i)
        {
            int D, H, M;
            scanf("%d%d%d", &D, &H, &M);
            for (int j = 0; j < H; ++j)
                g[++tot] = node(1.0 * D, 1.0 * M + j);
        }
        int ans = 0;
        if (tot == 2)
        {
            if (g[1].D > g[2].D) swap(g[1], g[2]);
            if (g[1].M > g[2].M) //deer always follow g[1]
            {
                double t1 = (360 - g[1].D) * 1.0 / 360 * g[1].M;
                double t2 = (360 + 360 - g[2].D) * 1.0 / 360 * g[2].M;
                if (t2 <= t1) ans = 1;
            } else // deer follow g[2]
            {
                double comT = (g[2].D - g[1].D) * 1.0 / (360.0 / g[1].M + 360.0 / g[2].M);
                for (int i = 1; i <= 2; ++i)
                    g[i].D += comT * 360 / g[i].M;
                if (g[1].D < 360)
                {
                    swap(g[1], g[2]);
                    double t1 = (360 - g[1].D) * 1.0 / 360 * g[1].M;
                    double t2 = (360 + 360 - g[2].D) * 1.0 / 360 * g[2].M;
                    if (t2 <= t1) ans = 1;
        
                }
            }
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
