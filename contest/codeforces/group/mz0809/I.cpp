#include <bits/stdc++.h>
#define MAXN 2123
#define MAXM 8123456
#define oo 12345678

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, d, cnt;
int n, k, num;
arrayM c, nxt, e;
deque <int> deq;
int S, T, SS, TT;

void link(int u, int v, int wei)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, c[num] = wei;
}

int bfs(int s)
{
    deq.clear();
    memset(d, 0x3f, sizeof(d));
    d[s] = 0;
    deq.push_back(s);
    for (;!deq.empty();)
    {
        int x = deq.front();
        deq.pop_front();
        for (int p = fir[x]; p; p = nxt[p])
            if (d[e[p]] > d[x] + 1 && c[p])
            {
                d[e[p]] = d[x] + 1;
                deq.push_back(e[p]);
                if (e[p] == TT) return 1;
            }
    }
    return 0;
}

int dfs(int x, int low)
{
    int flow = 0;
    if (x == TT) return low;
    for (int p = fir[x]; p; p = nxt[p])
        if (c[p] && d[e[p]] == d[x] + 1)
        {
            int tmp = dfs(e[p], min(c[p], low));
            flow += tmp, low -= flow;
            c[p] -= tmp, c[p ^ 1] += tmp;
            if (flow == 0) d[e[p]] = oo;
            if (!low) break;
        }
    return flow;
}

int ans[MAXN];

void prtAns()
{
    printf("YES\n");
    for (int i = 1; i <= k; ++i)
    {
        int u = i + 3 * n;
        for (int p = fir[u]; p; p = nxt[p])
            if (e[p] != S)
            {
                if (e[p] <= n)
                {
                    if (c[p]) ans[e[p]] = 0;
                    else ans[e[p]] = 1;
                } else
                {
                    if (c[p]) ans[e[p] - n] = 1;
                    else ans[e[p] - n] = 0;
                }
            }
    }
    for (int i = 1; i <= n; ++i)
        printf("%d%c", ans[i], " \n"[i == n]);
}

int main()
{
    freopen("sat.in", "r", stdin);
    freopen("sat.out", "w", stdout);
    scanf("%d%d", &n, &k);
    S = 0;
    T = k + n * 3 + 1;
    SS = T + 1, TT = SS + 1;
    num = 1;
    link(T, S, oo);
    link(S, T, 0);
    for (int i = 1; i <= n; ++i)
    {
        //  link(i + 2 * n, T, 1);
        // link(T, i + 2 * n, 0);
        link(i, i + 2 * n, 1);
        link(i + 2 * n, i, 0);
        link(i + n, i + 2 * n, 1);
        link(i + 2 * n, i + n, 0);
    }
    for (int i = 1; i <= k; ++i)
    {
        int s;
        scanf("%d", &s);
        //  link(S, 3 * n + i, 1);
        // link(3 * n + i, S, 0);
        int tv = 3 * n + i;
        link(SS, tv, 1);
        link(tv, SS, 0);
        link(S, TT, 1);
        link(TT, S, 0);
        for (int j = 0; j < s; ++j)
        {
            int x;
            scanf("%d", &x);
            cnt[abs(x)]++;
            if (x < 0) x = -x + n;
            link(3 * n + i, x, 1);
            link(x, 3 * n + i, 0);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        int tv = 2 * n + i;
        if (cnt[i] == 2)
        {
            link(SS, T, 1);
            link(T, SS, 0);
            link(tv, TT, 1);
            link(TT, tv, 0);
        } else
        {
            link(tv, T, 1);
            link(T, tv, 0);
        }
    }
    int ans = 0;
    for (; bfs(SS);)
        ans += dfs(SS, oo);
    for (int p = fir[SS]; p; p = nxt[p])
        if (c[p])
        {
            printf("NO\n");
            return 0;
        }
    prtAns();
    return 0;
}
