#include <bits/stdc++.h>
#define MAXN 111
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

const double esp = 1e-8;

double g[MAXN][MAXN], p[MAXN][MAXN], b[MAXN][MAXN], crt[MAXN][MAXN];
int a[MAXN];
double ansX[MAXN];

int cmp(double x)
{
    if (x > esp) return 1;
    if (x < -esp) return -1;
    return 0;
}
void gauss(int n)
{
    for (int i = 1; i <= n - 1; ++i)
    {
        int flag = 0;
        for (int j = i; j <= n; ++j)
            if (cmp(b[j][i]) != 0)
            {
                if (flag == 0) flag = j;
                else if (fabs(b[j][i]) > fabs(b[flag][i]))
                    flag = j;
            }
        for (int k = 1; k <= n; ++k)
            swap(b[i][k], b[flag][k]);
        double txs = b[i][i];
        for (int j = i; j <= n; ++j)
            b[i][j] /= txs;
        for (int j = 1; j <= n; ++j)
            if (cmp(b[j][i]) != 0 && i != j)
            {
                double xs = -1.0 * b[j][i];
                for (int k = i; k <= n; ++k)
                    b[j][k] += b[i][k] * xs;
            }
    }
}

int main()
{
    freopen("els.in", "r", stdin);
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
            scanf("%d", &a[i]);
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
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
                b[i][j] = p[j][i];
            b[i][i] -= 1.0;
            b[i][n + 1] = 0;
        }
        for (int i = 1; i <= n + 1; ++i)
            b[n + 1][i] = 1.0;
        for (int i = 1; i <= n + 1; i++)
            for (int j = 1; j <= n + 1; j++)
                crt[i][j] = b[i][j];
        gauss(n + 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= a[i]; ++j)
                printf("%.6f%c", fabs(b[i][n + 1] / b[i][i] * g[i][j]), " \n"[j == a[i]]);
    }
    return 0;
}
