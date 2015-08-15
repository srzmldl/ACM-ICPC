#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXN 20

using namespace std;

const int oo = 112345678;

struct node
{
    int value;
    int pre;
} g[MAXN];

double f[212][40000];

int main()
{
    // freopen("bzoj1076.in", "r", stdin);
    int k, n;
    scanf("%d%d", &k, &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &g[i].value);
        g[i].pre = 0;
        for (;;)
        {
            int x;
            scanf("%d", &x);
            if (x == 0) break;
            g[i].pre |= 1 << (x - 1);
        }
    }
    int lim = 1 << n;
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j < lim; ++j)
            f[i][j] = 0;
    for (int i = k - 1; i >= 0; --i)
        for (int sta = 0; sta < lim; ++sta)
        {
            for (int j = 1; j <= n; ++j)
                if ((sta & g[j].pre) == g[j].pre)
                    f[i][sta] += max(f[i + 1][sta], f[i + 1][sta | (1 << (j - 1))] + g[j].value);
                else f[i][sta] += f[i + 1][sta];
            f[i][sta] /= 1.0 * n;
        }
    printf("%.6lf", f[0][0]);
    return 0;
}