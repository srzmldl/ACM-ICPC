#include <bits/stdc++.h>
#define MAXN 1010
#define MAXM 212345

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];

arrayN a;

struct node
{
    int u, v, ans;
} g[MAXM];

struct point
{
    int edge;
    int lab;
} b[MAXN];

int com(point A, point B)
{
    return A.edge < B.edge;
}
int main()
{
    //  srand(clock() % time(0));
    freopen("flights.in", "r", stdin);
    freopen("flights.out", "w", stdout);
    for (;;)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n + m == 0) break;
        int tot = 0;
        memset(b, 0, sizeof(b));
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d%d", &g[i].u, &g[i].v);
            if (g[i].u > g[i].v) swap(g[i].u, g[i].v);
            if (g[i].u != 1)
            {
                g[i].ans = ++tot; 
                b[g[i].u].edge += tot;
                b[g[i].v].edge += tot;
            } else
            {
                a[g[i].v] = i;
            }
        }
        for (int i = 1; i <= n; ++i)
            b[i].lab = i;
        sort(b + 2, b + n + 1, com);
        for (int i = 2; i <= n; ++i)
            g[a[b[i].lab]].ans = m - (n - i);
        printf("Yes\n");
        for (int i = 1; i <= m; ++i)
            printf("%d%c", g[i].ans, " \n"[i == m]);
    }
    return 0;
}
