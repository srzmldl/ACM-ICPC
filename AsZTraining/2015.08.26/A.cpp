#include <bits/stdc++.h>
#define MAXN 212

#define MO 1000000007

using namespace std;

long long a[MAXN], c[MAXN][MAXN], f[MAXN][MAXN], jc[MAXN];
char st[MAXN];

long long add(long long u, long long v)
{
    u %= MO;
    v %= MO;
    return (u + v) % MO;
}

long long sub(long long u, long long v)
{
    u %= MO;
    v %= MO;
    long long tmp = u - v;
    if (tmp < 0) tmp += MO;
    return tmp % MO;
}

long long mul(long long u, long long v)
{
    u %= MO;
    v %= MO;
    long long tmp = 1LL * u * v;
    return tmp % MO;
}

long long sum = 0;


long long tb[6];
char ts[6];

long long dfs(int l, int r)
{
    if (l == r) return tb[l];
    long long ptb[6];
    long long pts[6];
    long long tmp = 0;
    for (int i = 0; i < 6; ++i)
        ptb[i] = tb[i], pts[i] = ts[i];
    for (int i = l; i < r; ++i)
    {
        if (ts[i - 1] == '+')
            tb[i] = (tb[i] + tb[i + 1]) % MO;
        else if (ts[i - 1] == '-')
            tb[i] = (tb[i] - tb[i + 1] + MO) % MO;
        else tb[i] = (tb[i] * tb[i + 1] % MO);
        for (int j = i + 1; j < r; ++j)
            tb[j] = tb[j + 1];
        for (int j = i - 1; j < 6; ++j)
            ts[j] = ts[j + 1];
        tmp = add(tmp, dfs(l, r - 1));
        for (int j = 0; j <6; ++j)
            tb[j] = ptb[j], ts[j] = pts[j];
    }
    return tmp;
}

long long calc(int l, int r)
{
    for (int i = 0; i < 6; ++i)
        ts[i] = st[i];
    for (int i = l; i <= r; ++i)
        tb[i] = (a[i] % MO + MO) % MO;
    return dfs(l, r);
}

int main()
{
	//freopen("in.txt", "r", stdin);
    int n;
    for ( ; scanf("%d", &n) != EOF; )
    {
        memset(f, 0, sizeof(f));
        for (long long i = 1; i <= n; ++i)
        {
            scanf("%I64d", &a[i]);
            f[i][i] = a[i] % MO;
            f[i][i] = add(f[i][i], MO);
        }
        scanf("%s", st);
        jc[0] = 1;
        for (long long i = 1; i <= n; ++i)
            jc[i] = mul(jc[i - 1], i);
        memset(c, 0, sizeof(c));
        c[0][0] = 1;
        for (int i = 1; i <= n * 2; ++i)
        {
            c[i][0] = 1;
            for (int j = 1; j <= i; ++j)
                c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
        }
        for (long long len = 2; len <= n; ++len)
            for (long long l = 1; l + len - 1 <= n; ++l)
            {
                long long r = l + len - 1;
                for (long long k = l; k < r; ++k)
                {
                    long long ch = st[k - 1];
                    long long tmp;
                    long long lcnt = jc[k - l];
                    long long rcnt = jc[r - k - 1];
                    long long lf = mul(rcnt, f[l][k]);
                    long long rf = mul(lcnt, f[k + 1][r]);
                    if (ch == '+')
                        tmp = add(lf, rf);
                    else if (ch == '-')
                        tmp = sub(lf, rf);
                    else
                        tmp = mul(f[l][k], f[k + 1][r]);
                    tmp = mul(tmp, c[k - l + r - k - 1][k - l]);
                    f[l][r] = add(f[l][r], tmp);
                }
            }
        printf("%I64d\n", f[1][n]);
        /*      for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; ++j)
            printf("f[%d][%d] = %lld; %lld\n", i, j, f[i][j], calc(i, j));*/
    }
	return 0;
}
