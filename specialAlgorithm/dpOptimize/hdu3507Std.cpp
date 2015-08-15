#include <deque>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define MAXN 512345

using namespace std;
typedef long long arrayN[MAXN];

arrayN sum, f;

long long sqr(long long x)
{
    return x * x;
}
int main()
{
    freopen("hdu3507.in", "r", stdin);
    int N, M;
    for (; scanf("%d%d", &N, &M) != EOF; )
    {
        int x;
        f[0] = 0;
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d", &x);
            sum[i] = sum[i - 1] + x;
            f[i] = sqr(sum[i]) + M;
            for (int j = 1; j < i; ++j)
                f[i] = min(f[i], f[j] + sqr(sum[i] - sum[j]) + M);
        }
        cout << f[N] << endl;
    }
    return 0;
}
