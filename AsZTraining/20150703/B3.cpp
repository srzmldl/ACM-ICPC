#include <bits/stdc++.h>
#define MAXN 112
#define MO 175781251
#define ny2 ((MO + 1) / 2)

using namespace std;

long long f[MAXN][MAXN], c[MAXN][MAXN];
long long pow3[MAXN];

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
    long long ans = 0;
    for (int a = 1; a <= n; ++a)
    {
        long long tmp = (pow3[n - a] - 1 + MO) % MO;
        long long t1 = tmp;
        for (int i = 2; i <= a; ++i)
            tmp = mul(tmp, t1);
        tmp = mul(tmp, c[n][a]);
        ans = add(ans, tmp);
    }
    ans = mul(ans, ny2);
    ans = add(ans, 1);
    cout << ans << ";" << endl;
}

void init()
{
    pow3[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        pow3[i] = (pow3[i - 1] * 3LL) % MO;
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
        // for (;;)
        // {
        //   int n;
        // scanf("%d", &n);
        // if (n == 0) break;
        cout << "prt[" << n << "] = ";
        solve(n);
    }
    return 0;
}
