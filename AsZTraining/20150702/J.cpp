#include <bits/stdc++.h>
#define MAXN 2123

using namespace std;

char a[MAXN][MAXN];
struct node
{
    int l, r;
} segr[MAXN];

struct node0
{
    int u, d;
} segc[MAXN];

struct point
{
    int x, y;
    point(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};

struct node1
{
    int tot;
    point pt[MAXN];
} grt, gr0, gct, gc0;

struct node2
{
    int f[MAXN];

    int getfa(int x)
    {
        if (f[x] == x) return f[x];
        else return f[x] = getfa(f[x]);
    }
    
    void init(int n)
    {
        for (int i = 0; i <= n; ++i)
            f[i] = i;
    }
} lkr, lkc;

int work(int x, int y, int h, int w)
{
    lkr.init(h);
    lkc.init(w);
    int tmp = -1;
    gr0.tot = 1;
    gr0.pt[0] = point(x, y);
    gc0.tot = 1;
    gc0.pt[0] = point(x, y);
    lkc.f[y] = y + 1;
    lkr.f[x] = x + 1;
    for (;gc0.tot && gr0.tot;)
    {
        gct.tot = grt.tot = 0;
        for (int i = 0; i < gr0.tot; ++i)
        {
            int u = segc[gr0.pt[i].y].u;
            int d = segc[gr0.pt[i].y].d;
            for (int p = lkr.getfa(u); p <= d; p++)
            {
                gct.pt[gct.tot++] = point(p, gr0.pt[i].y);
                lkr.f[p] = p + 1;
            }
        }
        for (int i = 0; i < gc0.tot; ++i)
        {
            int l = segr[gc0.pt[i].x].l;
            int r = segr[gc0.pt[i].x].r;
            for (int p = lkc.getfa(l); p <= r; p++)
            {
                grt.pt[grt.tot++] = point(gc0.pt[i].x, p);
                lkc.f[p] = p + 1;
            }
        }
        ++tmp;
        gc0.tot = gct.tot;
        for (int i = 0; i < gc0.tot; ++i)
            gc0.pt[i] = gct.pt[i];
        gr0.tot = grt.tot;
        for (int i = 0; i < gr0.tot; ++i)
            gr0.pt[i] = grt.pt[i];
    }
    return tmp - 1;
}

void solve(int h, int w)
{
    int cnt = 0;
    for (int i = 0; i < h; ++i)
    {
        scanf("%s", a[i]);
        for (int j = 0; j < w; ++j)
            if (a[i][j] == '#') ++cnt;
        int j;
        for (j = 0; j < w; ++j)
            if (a[i][j] == '#') break;
        segr[i].l = j;
        for (j = w - 1; j >= 0; --j)
            if (a[i][j] == '#') break;
        segr[i].r = j;
    }
    for (int j = 0; j < w; ++j)
    {
        int i;
        for (i = 0; i < h; ++i)
            if (a[i][j] == '#') break;
        segc[j].u = i;
        for (i = h - 1; i >= 0; --i)
            if (a[i][j] == '#') break;
        segc[j].d = i;
    }

    int ans = 0;
    if (cnt > 1)
    {
        for (int i = 0; i < h; ++i)
        {
            if (segr[i].l >= 0)
            {
                ans = max(ans, work(i, segr[i].l, h, w));
                if (segr[i].r > segr[i].l)
                    ans = max(ans, work(i, segr[i].r, h, w));
            }
        }
        for (int j = 0; j < w; ++j)
        {
            if (segc[j].u >= 0)
            {
                ans = max(ans, work(segc[j].u, j, h, w));
                if (segc[j].d > segc[j].u)
                    ans = max(ans, work(segc[j].d, j, h, w));
            }
        }
    }
    printf("%d\n", ans);
}
int main()
{
	freopen("jinxiety.in", "r", stdin);
    freopen("jinxiety.out", "w", stdout);

    for (;;)
    {
        int h, w;
        scanf("%d%d", &h, &w);
        if (h + w == 0) break;
        solve(h, w);
    }
    return 0;
}
