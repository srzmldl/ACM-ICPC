#include <bits/stdc++.h>
#define MAXN 2000000

int g[MAXN][2];
int d[MAXN];

using namespace std;

int reverse(int x)
{
    int t = 0, a[10];
    for (; x; x /= 10)
        a[++t] = x % 10;
    int tmp = 0;
    for (int i = 1; i <= t; ++i)
        tmp = tmp * 10 + a[i];
    return tmp;
}

int main()
{
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n, lim = 1000000;
        scanf("%d", &n);
        for (int i = 1; i <= lim; ++i)
        {
            g[i][0] = i + 1;
            g[i][1] = reverse(i);
            d[i] = MAXN;
        }
        d[1] = 1;
        deque<int> deq;
        deq.push_back(1);
        for (; !deq.empty();)
        {
            int u = deq.front();
            if (u == n) break;
            deq.pop_front();
            for (int i = 0; i <= 1; ++i)
            {
                int v = g[u][i];
                if (d[v] > d[u] + 1)
                {
                    if (d[v] == MAXN) deq.push_back(v);
                    d[v] = d[u] + 1;
                }
            }
        }
        printf("Case #%d: %d\n", t, d[n]);
    }
    return 0;
}
