#include <bits/stdc++.h>
#define MAXN 3123

using namespace std;

struct point
{
    long long x, y;
} g[MAXN];

struct node
{
    long long a, b, c;
    int lab;
} d[MAXN * MAXN], a[MAXN];

int ans[MAXN];

long long sqr(long long x)
{
    return x * x;
}

int com(node u, node v)
{
    return (u.a < v.a) || (u.a == v.a && u.b < v.b) || (u.a == v.a && u.b == v.b && u.c < v.c);
}

int cmp(node u, node v)
{
    if (u.a < v.a) return -1;
    if (u.a > v.a) return 1;
    if (u.b < v.b) return -1;
    if (u.b > v.b) return 1;
    if (u.c < v.c) return -1;
    if (u.c > v.c) return 1;
    return 0;
}

int main()
{
    freopen("astronomy.in", "r", stdin);
    freopen("astronomy.out", "w", stdout);
    for (;;)
    {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        int tot = 0;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%I64d%I64d", &g[i].x, &g[i].y);
            for (int j = 1; j < i; ++j)
            {
                ++tot;
                d[tot].a = sqr(g[i].x) + sqr(g[i].y);
                d[tot].b = sqr(g[j].y) + sqr(g[j].x);
                if (d[tot].a > d[tot].b) swap(d[tot].a, d[tot].b);
                d[tot].c = sqr(g[i].x - g[j].x) + sqr(g[i].y - g[j].y);
            }
        }
        int m;
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
        {
            scanf("%I64d%I64d%I64d", &a[i].a, &a[i].b, &a[i].c);
            if (a[i].a > a[i].b) swap(a[i].a, a[i].b);
            a[i].lab = i;
        }
        sort(d + 1, d + tot + 1, com);
        sort(a + 1, a + m + 1, com);
        int pd = 0, pa;
        for (pa = 1; pa <= m; ++pa)
        {
            int j = pa;
            for (; j + 1<= m && cmp(a[j], a[j + 1]) == 0; ++j);
            for (; pd + 1 <= tot && cmp(d[pd + 1], a[pa]) == -1; ++pd);
            int k = pd;
            for (; k + 1 <= tot && cmp(d[k + 1], a[pa]) == 0; ++k);
            for (int h = pa; h <= j; ++h)
                ans[a[h].lab] = k - pd;
            pa = j;
            pd = k;
        }
        for (int i = 1; i <= m; ++i)
            printf("%d\n", ans[i]);
    }
    return 0;
}
