#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset(a, (b), sizeof(a))
#define MAXN 11111

using namespace std;
typedef int arrayN[MAXN *2];

arrayN fir, nxt, e, c, sizeN, vis;
int n, k, ans, num;
vector<int> stRoot, stEp;


void link(int u, int v, int w)
{
    e[++num] = v, nxt[num] = fir[u], fir[u] = num;
    c[num] = w;
}

int dfsSize(int x, int fa)
{
    sizeN[x] = 1;
    for (int p = fir[x]; p; p = nxt[p])
        if (e[p] != fa && !vis[e[p]])
            sizeN[x] += dfsSize(e[p], x);
    return sizeN[x];
}

int getRoot(int x, int fa, int totN)
{
    int maxSize = totN - sizeN[x];
    for (int p = fir[x]; p; p = nxt[p])
        if (e[p] != fa && !vis[e[p]])
        {
            maxSize = max(maxSize, sizeN[e[p]]);
            int tmp = getRoot(e[p], x, totN);
            if (tmp) return tmp;
        }
    if (maxSize <= totN / 2) return x;
    return 0;
}

void dfsSt(int x, int fa, int len)
{
    stEp.push_back(len);
    for (int p = fir[x]; p; p = nxt[p])
        if (!vis[e[p]] && e[p] != fa)
            dfsSt(e[p], x, len +c[p]);
}

int calc(vector<int> &st)
{
    int tmp = 0;
    sort(st.begin(), st.end());
    int L = 0, R = st.size() - 1;
    for (;L < R;)
    {
        if (st[L] +st[R] <= k) tmp += R - L, L++;
        else --R;
    }
    return tmp;
}

void solve(int x)
{
    int root = getRoot(x, x, dfsSize(x, x));
    vis[root] = 1;
    stRoot.clear();
    stRoot.push_back(0);
    for (int p = fir[root]; p; p = nxt[p])
        if (!vis[e[p]])
        {
            stEp.clear();
            dfsSt(e[p], root, c[p]);
            ans -= calc(stEp);
            REP(i, stEp.size())
                stRoot.push_back(stEp[i]);
        }
    ans += calc(stRoot);
    for (int p = fir[root]; p; p = nxt[p])
        if (!vis[e[p]]) solve(e[p]);
    vis[root] = 0;
}

int main()
{
    freopen("in.txt", "r", stdin);
    for (;;)
    {
        scanf("%d%d", &n, &k);
        if (n + k == 0) break;
        ans = 0;
        num = 0;
        MST(fir, 0);
        REPP(i, 1, n - 1)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            link(u, v, w);
            link(v, u, w);
        }
        MST(vis, 0);
        ans = 0;
        solve(1);
        printf("%d\n", ans);
    }
    return 0;
}
