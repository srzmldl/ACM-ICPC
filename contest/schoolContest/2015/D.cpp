#include <bits/stdc++.h>
#define MAXN 111
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

double g[MAXN][MAXN], p[MAXN][MAXN];
int a[MAXN];

int main()
{
    freopen("D.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                p[i][j] = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a[i]);
            for (int j = 1; j <= a[i]; ++j)
                scanf("%lf", &g[i][j]);
            for (int j = 1; j <= a[i]; ++j)
            {
                for (int k = 1; k <= n; ++k)
                {
                    double x;
                    scanf("%lf", &x);
                    p[i][k] += g[i][j] * x;
                }
            }
        }
    }
    return 0;
}
