//每个边有编号,求字典序最小的欧拉回路,每次走小边即可. 起点时第一条边中小的节点
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
#define MAXN 2000

using namespace std;
typedef int arrayN[MAXN];

vector <int> ans;
vector < pair <int, int> > vec[MAXN];
int n, m, vis[MAXN * MAXN], S;
arrayN pos, f, deg;

int getfa(int x) {
    return f[x] == x ? x : (f[x] = getfa(f[x]));
}

void link(int u, int v, int id) {
    vec[u].push_back(make_pair(id, v));
    vec[v].push_back(make_pair(id, u));
    int fu = getfa(u), fv = getfa(v);
    if (fu != fv) f[fu] = fv;
    deg[u]++, deg[v]++;
    n = max(n, max(u, v));
    vis[id] = 0;
}

void dfs(int x) {
    for (; pos[x] < vec[x].size(); ) {
        int p = pos[x]++;
        int id = vec[x][p].first;
        int v = vec[x][p].second;
        if (!vis[id]) {
            vis[id] = 1;
            dfs(v);
            ans.push_back(id);
        }
    }
}

void getEulerPath() {
    for (int i = 1; i <= n; ++i) {
        sort(vec[i].begin(), vec[i].end()); // only this problem
        pos[i] = 0;
    }
    ans.clear(); // 记得清空
    dfs(S);
    for (int i = ans.size() - 1; i >= 0; --i)
        printf("%d%c", ans[i], " \n"[i == 0]);
}
bool checkEuler() {
    int block = 0;
    for (int i = 1; i <= n; ++i) {
        if (getfa(i) == i && deg[i]) ++block;
        if (deg[i] & 1) return false;
    }
    if (block && deg[S] == 0) return false; // only for this problem
    return block <= 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    for (int u, v, id;scanf("%d%d", &u, &v) != EOF;) {
        if (u + v == 0) break;
        if (u > v) swap(u, v);
        S = u;
        scanf("%d", &id);
        for (int i = 1; i < MAXN; ++i) {
            vec[i].clear();
            deg[i] = 0;
            f[i] = i;
        }
        link(u, v, id);
        for (;;) {
            scanf("%d%d", &u, &v);
            if (u + v == 0) break;
            scanf("%d", &id);
            link(u, v, id);
        }
        if (!checkEuler()) printf("Round trip does not exist.\n");
        else getEulerPath();
    }
}