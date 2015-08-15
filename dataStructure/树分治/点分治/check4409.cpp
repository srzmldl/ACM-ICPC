#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include <bitset>
#include <numeric>
#include <climits>
#include <string>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <vector>
#include <queue>
#include <list>
#include <map>
#include <set>

#define mm(a, b) memset(a, b, sizeof(a))
#define mp make_pair
#define pb push_back

using namespace std;

const int maxn = 31111;
const int maxm = 61111;
const int maxd = 17;
const int INF = 0x3f3f3f3f;
const double eps = 1e-8;

int n, m;

int cnte, head[maxn], node[maxm], nxt[maxm], cost[maxm], dist[maxm];
int cut[maxn], height[maxn], sumdis[maxn], sumcos[maxn], father[maxn][maxd], size[maxn];
int TiM, tim[maxn];

map<int, int>::iterator it;

void addline(int a, int b, int c, int d) {
    int t = ++ cnte;
    node[t] = b;
    cost[t] = c;
    dist[t] = d;
    nxt[t] = head[a];
    head[a] = t;
}

int go(int v, int h) {
    for (int i = 0; i < maxd; ++i)
        if (h & (1 << i))
            v = father[v][i];
    return v;
}

int lca(int a, int b) {
    if (height[a] > height[b]) swap(a, b);
    b = go(b, height[b] - height[a]);
    if (a == b) return a;
    for (int i = maxd - 1; i >= 0; --i)
        if (father[a][i] != father[b][i]) {
            a = father[a][i];
            b = father[b][i];
        }
    return father[a][0];
}

void dfs(int v, int p) {
    father[v][0] = p;
    height[v] = height[p] + 1;
    for (int i = head[v]; i; i = nxt[i]) {
        int t = node[i];
        if (t == p) continue;
        sumdis[t] = sumdis[v] + dist[i];
        sumcos[t] = sumcos[v] + cost[i];
        dfs(t, v);
    }
}

void prework() {
    dfs(1, 0);
    for (int j = 1; j < maxd; ++j) 
        for (int i = 1; i <= n; ++i)
            father[i][j] = father[father[i][j - 1]][j - 1];
}

queue<int> q;
vector<pair<int, int> > stk;

void getsum(int a, int b, int &d, int &l) {
    int c = lca(a, b);
    d = sumcos[a] + sumcos[b] - sumcos[c] * 2;
    l = sumdis[a] + sumdis[b] - sumdis[c] * 2;
}

pair<int, int> findmid(int v, int p, int tot) {
    pair<int, int> ret(INF, 0);
    int lar = 0;
    size[v] = 1;
    for (int i = head[v]; i; i = nxt[i]) {
        if (node[i] == p || cut[node[i]]) continue;
        ret = min(ret, findmid(node[i], v, tot));
        size[v] += size[node[i]];
        lar = max(lar, size[node[i]]);
    }
    ret = min(ret, mp(max(tot - size[v], lar), v));        
    return ret;
}

int gettot(int v, int p) {
    int ret = 1;
    for (int i = head[v]; i; i = nxt[i]) {
        if (node[i] == p || cut[node[i]]) continue;
        ret += gettot(node[i], v);
    }
    return ret;
}

int findmid(int v) {
    int sum = gettot(v, 0);
    return findmid(v, 0, sum).second; 
}

int calc(int v) {
    int rt = findmid(v); 
    cut[rt] = 1;
    int ret = 0;
    map<int, int> G;
    G.clear();
    G[0] = 0;
    for (int i = head[rt]; i; i = nxt[i]) {
        if (cut[node[i]]) continue;
        ret = max(ret, calc(node[i]));

        TiM++;
        tim[node[i]] = TiM;
        q.push(node[i]);
        stk.clear();
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            int d, l;
            getsum(x, rt, d, l);
            stk.pb(mp(d, l));
            if (d <= m) {
                ret = max(ret, (--G.upper_bound(m - d)) -> second + l);
            }
            for (int j = head[x]; j; j = nxt[j]) {
                if (cut[node[j]] || tim[node[j]] == TiM) continue;
                q.push(node[j]);
                tim[node[j]] = TiM;
            }
        }

        for (int j = 0; j < (int)stk.size(); ++j) {
            if (stk[j].first > m) continue;
            if (G.upper_bound(stk[j].first) != G.begin() && (--G.upper_bound(stk[j].first)) -> second >= stk[j].second) continue;
            G[stk[j].first] = stk[j].second;
            while (1) {
                it = G.upper_bound(stk[j].first);
                if (it == G.end()) break;
                if (it -> second <= stk[j].second) {
                    G.erase(it);
                }
                else break;
            }
        }
    }
    cut[rt] = 0;
    return ret;
}

void solve(){
    scanf("%d%d", &n, &m);
    memset(head, 0, sizeof(head));
    memset(cut, 0, sizeof(cut));
    mm(father, 0);
    mm(height, 0);
    mm(sumdis, 0);
    mm(sumcos, 0);
    cnte = 0;
    for (int i = 1; i < n; ++i) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        addline(a, b, c, d);
        addline(b, a, c, d);
    }
    prework();
    printf("%d\n", calc(1));
}

int main(){
	freopen("la4409.in", "r", stdin);
    freopen("out1.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i) {
        printf("Case %d: ", i);
        solve();
    }
}
