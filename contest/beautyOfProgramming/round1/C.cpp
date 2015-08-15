#include <bits/stdc++.h>
#define MO 100007
#define MAXN 30

using namespace std;

int a[MAXN], b[MAXN];
int isPrime[512345], pri[512345];

int main()
{
    // freopen("C.in", "r", stdin);
    int T;
    scanf("%d", &T);
    int lim = 500000;
    int priTot = 0;
    for (int i = 2; i <= lim; ++i)
    {
        if (!isPrime[i])
        {
            pri[priTot++] = i;
        }
        for (int j = 0; j < priTot; ++j)
            if (1LL * i * pri[j] <= 1LL * lim)
            {
                isPrime[i * pri[j]] = 1;
                if (i % pri[j] == 0) break;
            }
            else break;
    }
    for (int t = 1; t <= T; ++t)
    {
        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
            scanf("%d", a + i);
        int ans = 0;
        for (int i = 0; i < (1 << N); ++i)
        {
            int tot = 0;
            for (int j = 0; j < N; ++j)
                if (i & (1 << j)) b[tot++] = a[j];
            int ok = 1;
            for (int i1 = 0; i1 < tot && ok; ++i1)
                for (int j1 = i1 + 1; j1 < tot && ok; ++j1)
                {
                    int u = b[i1], v = b[j1];
                    if (u > v) swap(u, v);
                    if (v % u == 0)
                    {
                        if (!isPrime[v / u]) ok = 0;
                    }
                }
            if (ok) ans = max(ans, tot);
        }
        printf ("Case #%d: %d\n", t, ans);
    }
    return 0;
}
