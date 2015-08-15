#include <bits/stdc++.h>
#define MAXN 1123456
#define MAXM 2123456

typedef int arrayN[MAXN], arrayM[MAXM];

using namespace std;

arrayN fir, cost, t, pre, vis;
arrayM e, nxt, c;
long long ans, dst[MAXN];
int num, now, visNow;

void link(int u, int v, int w)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, c[num] = w;
}

vector <int> bfsFindCycle(int x)
{
    ++now;
    vector <int> cyc;
    deque <int> deq;
    int pt = 0, ph = 0, last;
    deq.push_back(x);
    t[x] = now;
    for (; !deq.empty() && !pt;)
    {
        int u = deq.front();
        deq.pop_front();
        for (int p = fir[u]; p && !pt; p = nxt[p])
            if (e[p] != pre[u])
                if (t[e[p]] == now)
                {
                    pt = u, ph = e[p];
                    last = c[p];
                }
                else
                {
                    t[e[p]] = now;
                    pre[e[p]] = u;
                    cost[e[p]] = c[p];
                    deq.push_back(e[p]);
                }
    }
    vector <int> cycTmp;
    if (pt)
    {
        ++now;
        int tmp = pt;
        for (; tmp != x; tmp = pre[tmp])
            t[tmp] = now;
        t[x] = now;
        int lca = ph;
        for (; t[lca] != now; lca = pre[lca]);
        for (tmp = pt; tmp != lca; tmp = pre[tmp])
        {
            swap(last, cost[tmp]);
            cyc.push_back(tmp);
        }
        cyc.push_back(lca);
        cost[lca] = last;

        for (tmp = ph; tmp != lca; tmp = pre[tmp])
            cycTmp.push_back(tmp);
        for (; !cycTmp.empty(); cycTmp.pop_back())
            cyc.push_back(cycTmp.back());
    } else cyc.push_back(x);
    
    ++now;
    for (int i = 0; i < cyc.size(); ++i)
        t[cyc[i]] = now;
    return cyc;
}

struct node
{
    long long w;
    long long lst, f;
}g[MAXN * 2];

long long bfsLongest(int rt, int &nrt)
{
    long long lst = 0;
    deque <int> deq;
    deq.push_back(rt);
    nrt = rt;
    vis[rt] = ++visNow;
    dst[rt] = 0;
    for (; !deq.empty(); )
    {
        int u = deq.front();
        deq.pop_front();
        for (int p = fir[u]; p; p = nxt[p])
            if (vis[e[p]] != visNow && t[e[p]] != now)
            {
                vis[e[p]] = visNow;
                dst[e[p]] = dst[u] + c[p];
                if (dst[e[p]] > lst)
                {
                    lst = dst[e[p]];
                    nrt = e[p];
                }
                deq.push_back(e[p]);
            }
    }
    return lst;
}

long long solve(int x)
{
    long long ans = 0;
    vector <int> cyc = bfsFindCycle(x);
    int n = cyc.size();
    for (int i = 0; i < n; ++i)
    {
        int pt, pp;
        t[cyc[i]] = 0;
        g[i].lst = bfsLongest(cyc[i], pt);
        ans = max(ans, bfsLongest(pt, pp));
        t[cyc[i]] = now;
        if (n == 1) return g[i].lst;
        g[i].w = cost[cyc[i]];
        g[i].f = 0;
        g[i + n] = g[i];
    }
    g[0].w = 0;
    for (int i = 1; i < 2 * n; ++i)
		g[i].w += g[i - 1].w;
    g[0].f = g[0].lst;
    deque <int> deq;
    deq.push_back(0);
    for (int i = 1; i < 2 * n; ++i)
    {
        for (; deq.front() + n <= i; deq.pop_front());
        g[i].f = g[i].lst + g[i].w + g[deq.front()].lst - g[deq.front()].w;
        for (; !deq.empty() && g[deq.back()].lst - g[deq.back()].w <= g[i].lst - g[i].w; deq.pop_back());
        deq.push_back(i);
    }
    for (int i = 0; i < 2 * n; ++i)
        ans = max(ans, g[i].f);
    return ans;
}

int main()
{
    freopen("island.in", "r", stdin);
    int n;
    num = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int v, len;
        scanf("%d%d", &v, &len);
        link(i, v, len);
        link(v, i, len);
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            ans += solve(i);
    printf("%lld\n", ans);
    return 0;
}
