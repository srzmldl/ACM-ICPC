#include <bits/stdc++.h>

#define MAXN 21234
#define BITCNT 32
#define MAXM 112345

using namespace std;

bitset<BITCNT> inD[MAXN][MAXN / BITCNT];
bitset<BITCNT> go[MAXN][MAXN / BITCNT];
int cnt, num;
typedef int arrayN[MAXN];
typedef int arrayM[MAXM];

arrayN fir, vis, topSeq, deg;
arrayM nxt, e;

pair <int, int> calcPos(int u) {
    return {(u - 1) / BITCNT + 1, (u - 1) % BITCNT + 1};
}

void addInd(int u, int v) {
    pair <int, int> p = calcPos(u);
    inD[v][p.first - 1].set(p.second - 1);
}

void link(int u, int v) {
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, deg[v]++;
    addInd(u, v);
}

void topSort(int n) {
    int l = 1, r = 0;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0) topSeq[++r] = i;
    for (; l <= r; ++l) {
        int u = topSeq[l];
        for (int p = fir[u]; p; p = nxt[p]) {
            int v = e[p];
            --deg[v];
            if (deg[v] == 0) topSeq[++r] = v;
        }
    }
}

int getGo(int n) {
    int ans = 0;
    for (int i = n; i >= 1; --i) {
        int u = topSeq[i];
        for (int p = fir[u]; p; p = nxt[p]) {
            int v = e[p];
            pair <int, int> pos = calcPos(v);
            go[u][pos.first - 1].set(pos.second - 1);
            for (int j = 0; j < cnt; ++j) {
                go[u][j] |= go[v][j];
            }
        }

        for (int p = fir[u]; p; p = nxt[p]) {
            int v = e[p];
            int flag = 0;
            for (int j = 0; j < cnt; ++j)
                if ((go[u][j] & inD[v][j]).any()) {
                    flag = 1;
                }
            ans += flag;
        }
        
    }
    return ans;
}

int main() {
#ifdef HOME
    freopen("in.txt", "r", stdin);
#endif
    int T;
    for (scanf("%d", &T); T; --T) {
        int n, m;
        scanf("%d%d", &n, &m);
        cnt = (n - 1)/ BITCNT + 1;
        for (int i = 1; i <= n; ++i) {
            fir[i] = vis[i] = 0;
            for (int j = 0; j < cnt; ++j) {
                inD[i][j].reset();
                go[i][j].reset();
            }
        }
        num = 0;
        
        for (int i = 1; i <= m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            link(u, v);
        }
        topSort(n);
        cout << getGo(n) << endl;
        
    }
    return 0;
}