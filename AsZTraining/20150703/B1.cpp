#include <bits/stdc++.h>
#define MAXN 112
#define MO 175781251
#define ny2 ((MO + 1) / 2)

using namespace std;

long long f[MAXN][MAXN], c[MAXN][MAXN];
long long pow2[MAXN];

long long add(long long u, long long v)
{
    return (u + v) % MO;
}

long long mul(long long u, long long v)
{
    u %= MO;
    v %= MO;
    return u * v % MO;
}

void solve(int n)
{
    long long ans = 1;
    for (int a = 1; a <= n / 2; ++a)
    {
        memset(f, 0, sizeof(f));
        f[0][0] = 1;
        int b = n - a;
        for (int i = 0; i < a; ++i)
            for (int j = 0; j <= b; ++j)
            {
                for (int t = 1; t <= j; ++t)
                    f[i + 1][j] = add(f[i + 1][j], mul(f[i][j], mul(c[j][t], pow2[t])));
                long long tmp = 0;
                for (int t = 0; t <= j; ++t)
                    tmp = add(tmp, mul(pow2[t], c[j][t]));
                for (int k = 1; k <= b - j; ++k)
                {
                    f[i + 1][j + k] = add(f[i + 1][j + k], mul(mul(f[i][j], c[b - j][k]), mul(pow2[k], tmp)));
                }
            }
        long long tmp = 0;
        for (int i = a + 1; i <= b; ++i)
            tmp = add(tmp, f[a][i]);
        tmp = mul(tmp, c[n][a]);
        ans = add(ans, tmp);
        tmp = mul(c[n][a], mul(f[a][a], ny2));
        ans = add(ans, tmp);
    }
    cout << ans << ";" << endl;;
}

void init()
{
    pow2[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        pow2[i] = (pow2[i - 1] * 2LL) % MO;
    c[0][0] = 1;
    for (int i = 1; i < MAXN; ++i)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; ++j)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MO;
    }
}

int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    init();
    for (int n = 1; n <= 100; ++n)
    {
        //for (;;)
        // {
        //  int n;
        //  scanf("%d", &n);
        // if (n == 0) break;
        cout << "prt[" << n << "] = ";
        solve(n);
    }
    return 0;
}
