//图上动态添边求桥数目
//注意图不联通的情况,此题不考虑
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#define MAXN 412345

using namespace std;
typedef int arrayN[MAXN];
arrayN fir0, e0, nxt0, fir1, e1, nxt1, f, faT;
arrayN vis, isBri, belong, dfn, low, par, dep;
int now, tot, num, briCnt;

void link0(int u, int v) {
    e0[++num] = v, nxt0[num] = fir0[u];
    fir0[u] = num, vis[num] = isBri[num] = 0;
}
void link1(int u, int v) {
    e1[++num] = v, nxt1[num] = fir1[u];
    fir1[u] = num;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++now;
    for (int p = fir0[u]; p; p = nxt0[p])
        if (!vis[p]) {
            vis[p] = vis[p ^ 1] = 1;
            int v = e0[p];
            if (!dfn[v]) {
                tarjan(v);
                par[v] = p;
                low[u] = min(low[u], low[v]);
            } else low[u] = min(low[u], dfn[v]);
        }
}

void dfs(int x, int bel) {
    belong[x] = bel;
    for (int p = fir0[x], q; p; p = nxt0[p])
        if (!isBri[p] && !belong[q = e0[p]]) dfs(q, bel);
}
void compressAndBuildTree(int n) {
    memset(belong, 0, sizeof(belong));
    tot = 0;
    for (int i = 1; i <= n; ++i)
        if (!belong[i]) dfs(i, ++tot);
    num = 1;
    memset(fir1, 0, sizeof(fir1));
    for (int i = 1; i <= n; ++i)
        for (int p = fir0[i]; p; p = nxt0[p])
            if (isBri[p]) link1(belong[i], belong[e0[p]]);
}
void bcc_edge(int n) {
    memset(dfn, 0, sizeof(dfn));
    now = 0;
    for (int i = 1; i <= n; ++i)
        if (!dfn[i]) tarjan(i);

    //getbrige
    briCnt = 0;
    for (int i = 2; i <= n; ++i) {
        int p = par[i] ^ 1;
        int u = e0[p], v = i;
        if (dfn[u] < low[v]) {
            ++briCnt;
            isBri[p] = isBri[p ^ 1] = 1;
        }
    }
    compressAndBuildTree(n);
}

void dfsGetfaTree(int u, int fa, int depth) {
    faT[u] = fa;
    dep[u] = depth;
    for (int p = fir1[u], q; p; p = nxt1[p])
        if ((q = e1[p]) != fa)
            dfsGetfaTree(q, u, depth + 1);
}

int getfa(int x) {
    return x == f[x] ? x : (f[x] = getfa(f[x]));
}
int ask(int u, int v) {
    int tu = belong[u], tv = belong[v];
    tu = getfa(tu), tv = getfa(tv);
    for (; tu != tv;) {
        if (dep[tu] < dep[tv]) swap(tu, tv);
        briCnt--;
        f[tu] = faT[tu];
        tu = getfa(faT[tu]);
    }
    return briCnt;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    for (int ca = 1; scanf("%d%d", &n, &m) != EOF; ++ca) {
        if (n + m == 0) break;
        printf("Case %d:\n", ca);
        num = 1;
        memset(fir0, 0, sizeof(fir0));
        for (int i = 1; i <= m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            link0(u, v), link0(v, u);
        }
        bcc_edge(n);
        dfsGetfaTree(1, 0, 1);
        for (int i = 1; i <= tot; ++i)
            f[i] = i;
        int q;
        scanf("%d", &q);
        for (; q; --q) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", ask(u, v));
        }
        printf("\n");
    }
}