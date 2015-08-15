#include <bits/stdc++.h>
#define MAXN 112
#define MO 175781251
#define ny2 ((MO + 1) / 2)

using namespace std;

long long f[MAXN + 1][MAXN + 1], c[MAXN + 1][MAXN + 1];
long long pow2[MAXN + 1];

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
vo
void solve(int n)
{
    long long ans = 0;
    for (int i = 0; i <= n; ++i)
        for (int j = i + 1; j <= n - i; ++j)
            ans = add(ans, mul(f[i][j], mul(c[n][i], c[n - i][j])));
    ans = add(ans, 1);
    for (int i = 1; i <= n / 2; ++i)
        ans = add(ans, mul(mul(f[i][i], mul(c[n][i], c[n - i][i])), ny2));
    cout << ans << endl;
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

    
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j <= MAXN - i - 1; ++j)
        {
            for (int t = 1; t <= j; ++t)
                f[i + 1][j] = add(f[i + 1][j], mul(f[i][j], mul(c[j][t], pow2[t])));
            long long tmp = 0;
            for (int t = 0; t <= j; ++t)
                tmp = add(tmp, mul(pow2[t], c[j][t]));
            for (int k = 1; k <= MAXN - (i + 1) - j; ++k)
            {
                f[i + 1][j + k] = add(f[i + 1][j + k], mul(mul(f[i][j], 1), mul(pow2[k], tmp)));
            }
        }
    
    /*   long long tmp = 0;
    for (int i = 0; i <= 6; ++i)
        tmp = add(tmp, mul(pow2[i], c[6][i]));
        cout << tmp << endl; */
}

int main()
{
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    init();
    for (;;)
    {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        solve(n);
    }
    return 0;
}
