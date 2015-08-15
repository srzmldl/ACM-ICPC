#include <bits/stdc++.h>
#define MAXN 2123
#define INF 512345
#define MAXM 2123456

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, col, vis, match, a;
arrayM nxt, e;
int num, isPrime[INF], prime[INF];

void link(int u, int v)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

void sievePrime()
{
    int tot = 0;
    for (int i = 2; i < INF; ++i)
    {
        if (!isPrime[i]) prime[tot++] = i;
        for (int j = 0; j < tot; ++j)
            if (1LL * prime[j] * i < INF)
            {
                isPrime[i * prime[j]] = 1;
                if ( i % prime[j] == 0) break;
            }
            else break;
    }
}

void dye(int x, int co)
{
    col[x] = co;
    for (int p = fir[x]; p; p = nxt[p])
        if (col[e[p]] == -1)
            dye(e[p], 1 - co);
        else continue;
}

int dfs(int x)
{
    for (int p = fir[x]; p; p = nxt[p])
        if (!vis[e[p]])
        {
            vis[e[p]] = 1;
            if (!match[e[p]] || dfs(match[e[p]]))
            {
                match[e[p]] = x;
                return 1;
            }
        }
    return 0;
}

int main()
{
    freopen("1158.in", "r", stdin);
    int T;
    scanf("%d", &T);
    sievePrime();
    // for (int i = 1; i <= 100; ++i)
    //   printf("%d\n", isPrime[i]);
    for (int t = 1; t <= T; ++t)
    {
        int N;
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i)
            scanf("%d", a + i);
        sort(a + 1, a + N + 1);
        num = 0;
        memset(fir, 0, sizeof(fir));
        for (int i = 1; i < N; ++i)
            for (int j = i + 1; j <= N; ++j)
                if (a[j] % a[i] == 0 && isPrime[a[j] / a[i]] == 0)
                {
                    link(i, j);
                    link(j, i);
                }
        memset(col, -1, sizeof(col));
        memset(match, 0, sizeof(match));
        for (int i = 1; i <= N; ++i)
            if (col[i] == -1)
                dye(i, 0);
        int ans = N;
        for (int i = 1; i <= N; ++i)
            if (col[i])
            {
                memset(vis, 0, sizeof(vis));
                if (dfs(i)) ans--;
            }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}