#include <bits/stdc++.h>
#define MAXN 301234

using namespace std;

int a[MAXN];
char st[MAXN];

int convert(char x)
{
    if (x == 'i') return 2;
    else if (x == 'j') return 3;
    else return 4;
}

int calc[5][5] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4},
        {0, 2, -1, 4, -3},
        {0, 3, -4, -1, 2},
        {0, 4, 3, -2, -1}
    };
int main()
{
    freopen("dij.in", "r", stdin);
    freopen("dij.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int L;
        long long X;
        scanf("%d%lld", &L, &X);
        scanf("%s", st);
        int lim = min(10LL, X), asum = 1, sig = 1;
        for (int i = 0; i < L; ++i)
        {
            a[i] = convert(st[i]);
            asum = calc[asum][a[i]];
            if (asum < 0)
            {
                asum = -asum;
                sig *= -1;
            }
            for (int j = 2; j <= lim; ++j) a[i + (j - 1) * L] = a[i];
        }
        int n = L * lim;
        int sum = 1, p2 = -1, sig2 = 1;
        for (int i = 0; i < n; ++i)
        {
            sum = calc[sum][a[i]];
            if (sum < 0)
            {
                sum = -sum;
                sig2 *= -1;
            }
            if (sum * sig2 == 2)
            {
                p2 = i;
                break;
            }
        }
        int p4 = -1, sig4 = 1;
        sum = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            sum = calc[a[i]][sum];
            if (sum < 0)
            {
                sum = -sum;
                sig4 *= -1;
            }
            if (sum * sig4 == 4)
            {
                p4 = i;
                break;
            }
        }
        printf("Case #%d: ", t);
        if (p4 < 0 || p2 < 0 || asum * sig == 1 || (1LL * p2 + 1 + n - p4 > 1LL * X * L))
        {
            printf("NO\n");
            continue;
        }
        X %= 4;
        int fsum = asum, fsig = sig;
        for (int i = 2; i <= X; ++i)
        {
            fsum = calc[fsum][asum];
            fsig *= sig;
            if (fsum < 0)
            {
                fsum = -fsum;
                fsig *= -1;
            }
        }
        if (fsum * fsig == -1) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
