#include <bits/stdc++.h>
#define MAXN 212345

using namespace std;

typedef int arrayN[MAXN];

int num, ans, now, ptCnt;
arrayN fir, e, nxt, c, vis;
int seg[MAXN * 4], base;

set <int> sss;

struct node
{
    int l, r, f[20], dep, sum;
} g[MAXN];

void link(int u, int v, int w)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, c[num] = w;
}

void dfs(int x, int fa, int sum, int dep)
{
    ++now;
    g[x].l = now;
    g[x].f[0] = fa;
    g[x].sum = sum;
    g[x].dep = dep;
    for (int p = fir[x]; p; p = nxt[p])
        if (e[p] != fa)
        {
            dfs(e[p], x, sum + c[p], dep + 1);
            ++now;
            g[x].r = now;
        }
}

void getDfsSeqInit(int n)
{
    now = 0;
    dfs(1, 0, 0, 1);
    for (base = 1; base <= now + 2; base <<= 1);
    memset(seg, 0, sizeof(seg));
    for (int i = 1; i < 20; ++i)
        for (int j = 1; j <= n; ++j)
            g[j].f[i] = g[g[j].f[i - 1]].f[i - 1];
}

void change(int x, int v)
{
    x += base;
    seg[x] += v;
}

int ask(int l, int r)
{
    l += base - 1;
    r += base + 1;
    int tmp = 0;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) tmp += seg[l + 1];
        if (r & 1) tmp += seg[r - 1];
    }
    return tmp;
}

int findFirSubCnt(int p, int subCnt)
{
    if (ask(g[p].l, g[p].r) >= subCnt) return p;
    for (int i = 19; i >= 0; --i)
        if (g[p].f[i] && ask(g[g[p].f[i]].l, g[g[p].f[i]].r) < subCnt)
            p = g[p].f[i];
    return g[p].f[0];
}

int findFirNoZero(int p)
{
    if (ask(g[p].l, g[p].r) != 0) return p;
    for (int i = 19; i >= 0; --i)
        if (g[p].f[i] && ask(g[g[p].f[i]].l, g[g[p].f[i]].r) == 0)
            p = g[p].f[i];
    return g[p].f[0];
}

void ins(int x)
{
    if (vis[x]) return ;
    vis[x] = 1;
    int subCnt = ask(g[x].l, g[x].r);
    int othCnt = ptCnt - subCnt;
    if (subCnt && othCnt)
    {
        //nothing
    } else
    if (subCnt + othCnt == 0)
    {
        //nothing
    } else
    if (othCnt == 0) // have sub
    {
        int p = *sss.begin();
        p = findFirSubCnt(p, ptCnt);
        ans += (g[p].sum - g[x].sum);

    } else
    {
        int p = findFirNoZero(x);
        ans += (g[x].sum - g[p].sum);
        if (ask(g[p].l, g[p].r) == ptCnt)
        {
            int q = *sss.begin();
            q = findFirSubCnt(q, ptCnt);
            ans += (g[q].sum - g[p].sum);
        } else
        {
            //nothing
        }
    }



    change(g[x].l, 1);
}


void del(int x)
{
    if (!vis[x]) return ;
    vis[x] = 0;
    change(g[x].l, -1);
    int subCnt = ask(g[x].l, g[x].r);
    int othCnt = ptCnt - subCnt;

    sss.erase(x);
    ptCnt--;
    if (sss.empty())
    {
        ans = 0;
        return;
    }
    if (subCnt && othCnt)
    { //nothing
    } else
    if (subCnt + othCnt == 0)
    { //nothing
    } else
    if (othCnt == 0) // only sub
    {
        int p = *sss.begin();
        p = findFirSubCnt(p, subCnt);
        ans -= (g[p].sum - g[x].sum);
    } else
    {
        int p = findFirNoZero(x);
        ans -= (g[x].sum - g[p].sum);
        if (ask(g[p].l, g[p].r) == ptCnt)
        {
            int q = *sss.begin();
            q = findFirSubCnt(q, ptCnt);
            ans -= (g[q].sum - g[p].sum);

        } else
        {
            //nothing
        }
    }
}

// sss.erase(x)
// sss.insert(x)
// *sss.begin()
void init(int n)
{
    num = 0;
    memset(fir, 0, sizeof(fir));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j < 20; ++j)
            g[i].f[j] = 0;
        g[i].sum = 0;
    }
    g[0].dep = 0;
    ans = 0;
    ptCnt = 0;
}

int main()
{
    freopen("i.in", "r", stdin);
    int t;
    scanf("%d", &t);
    for (int ca = 1; ca <= t; ++ca)
    {
        printf("Case #%d:\n", ca);
        int n, m;
        scanf("%d%d", &n, &m);
        init(n);
        for (int i = 1; i < n; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            link(u, v, w);
            link(v, u, w);
        }
        getDfsSeqInit(n);
        for (int i = 1; i <= m; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x == 1) ins(y);
            else del(y);

            printf("%d\n", ans);
        }
    }
    return 0;
}
