//指定小写字母元音/辅音
//给出第i个位置是元音/辅音蕴涵j位置元音/辅音
//给定字符串st,求字典序不小于它的最小的合法2-sat方案
#include <bits/stdc++.h>
#define MAXN 500
#define MAXM 512345

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

char g[30], st[MAXN];
arrayN fir0, low, dfn, inVec, cnt, belong;
arrayN deg, con0, con1, fir1, topOrder, col;
arrayM e0, nxt0, e1, nxt1;
int num, now, tot, nextAlp[30][2], firAlp[2];
vector<int> vec;

int getKind(char ch) {
    if (ch == 'V') return 0;
    else return 1;
}

void link0(int u, int v) {
    e0[++num] = v, nxt0[num] = fir0[u];
    fir0[u] = num;
}

void link1(int u, int v) {
    e1[++num] = v, nxt1[num] = fir1[u];
    fir1[u] = num;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++now;
    vec.push_back(x);
    for (int p = fir0[x], q; p; p = nxt0[p])
        if (!inVec[q = e0[p]])
            if (!dfn[e0[p]]) {
                tarjan(e0[p]);
                low[x] = min(low[x], low[e0[p]]);
            } else low[x] = min(low[x], dfn[e0[p]]);
    if (low[x] == dfn[x]) {
        cnt[belong[x] = ++tot] = 1;
        inVec[x] = 1;
        for (; vec.back() != x; vec.pop_back()) {
            int q = vec.back();
            inVec[q] = 1;
            cnt[belong[q] = tot]++;
        }
        vec.pop_back();
    }
}

void topSort() {
    int l = 1, r = 0;
    for (int i = 1; i <= tot; ++i)
        if (deg[i] == 0) topOrder[++r] = i;
    for (; l <= r; ++l) {
        int u = topOrder[l];
        for (int p = fir1[u]; p; p = nxt1[p]) {
            --deg[e1[p]];
            if (deg[e1[p]] == 0) topOrder[++r] = e1[p];
        }
    }
}
int getDAG(int n) {
    for (int i = 1; i <= n * 2; ++i)
        dfn[i] = low[i] = belong[i] = inVec[i] = deg[i] = 0;
    now = tot = num = 0;
    for (int i = 1; i <= n * 2; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; ++i)
        if (belong[i] == belong[con0[i]]) return 0;
    for (int i = 1; i <= 2 * n; ++i) {
        for (int p = fir0[i]; p; p = nxt0[p]) {
            int q = e0[p];
            if (belong[i] == belong[q]) continue;
            link1(belong[q], belong[i]);
            deg[belong[i]]++;
        }
        con1[belong[i]] = belong[con0[i]];
        con1[belong[con0[i]]] = belong[i];
    }
    topSort();
    return 1;
}

int dye(int x, int co) {
    if (col[x]) {
        return (co == col[x]);
    }
    col[x] = co;
    for (int p = fir1[x]; p; p = nxt1[p])
        if (!dye(e1[p], co)) return 0;
    return 1;
}

int originDye(int p, int n) {
    int all = -1;
    if (firAlp[0] > 'z') all = 0;
    if (firAlp[1] > 'z') all = 1;
    if (all >= 0)
        for (int i = 1; i <= n; ++i) {
            int pos1 = i + all * n;
            int pos0 = con1[pos1];
            if (col[pos0] == 2) return 0;
            col[pos0] = 1;
            if (!dye(pos1, 2)) return 0;
        }
    for (int i = 1; i <= p + 1; ++i) {
        int pos = belong[i];
        if (getKind(g[st[i - 1] - 'a'])) pos = con1[pos];
        if (col[pos] == 2) return 0;
        col[pos] = 1;
        if (!dye(con1[pos], 2)) return 0;
    }
    return 1;
}
int DAGDye(int n) {
    for (int i = 1; i <= n; ++i) {
        int x = topOrder[i];
        if (!col[x]) {
            col[x] = 1;
            if (!dye(con1[x], 2)) return 0;
        }
    }
    return 1;
}

int finalCheck(int n, int p) {
    for (int i = 1; i <= n; ++i) {
        if (col[belong[i]] != 1 && col[belong[con0[i]]] != 1) return 0;
    }
    return 1;
}

int solve(int n, int p) {
    memset(col, 0, sizeof(col));
    if (!originDye(p, n)) return 0;
    if (!DAGDye(tot)) return 0;
    return finalCheck(n, p);
}

void getNextAlp() {
    int len = strlen(g);
    firAlp[1] = firAlp[0] = 'z' + 1;
    for (int i = 0; i < len; ++i) {
        nextAlp[i][0] = nextAlp[i][1] = 'z' + 1;
        int k = getKind(g[i]);
        firAlp[k] = min(firAlp[k], i + 'a');
        for (int j = i + 1; j < len; ++j) {
            int k = getKind(g[j]);
            nextAlp[i][k] = min(nextAlp[i][k], 'a' + j);
        }
        if (nextAlp[i][0] > nextAlp[i][1])
            swap(nextAlp[i][0], nextAlp[i][1]);
    }
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%s", g);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        con0[i] = i + n;
        con0[i + n] = i;
    }
    num = 0;
    for (int i = 1; i <= m; ++i) {
        char t1, t2;
        int pos1, pos2;
        scanf("%d %c %d %c\n", &pos1, &t1, &pos2, &t2);
        //  if (i == 50 && n == 50 && m == 50) printf("%d %c %d %c\n", pos1, t1, pos2, t2);
        int k1 = getKind(t1);
        int k2 = getKind(t2);
        pos1 += k1 * n;
        pos2 += k2 * n;
        link0(pos1, pos2);
        link0(con0[pos2], con0[pos1]);
    }
    scanf("%s", st);
    // if (n == 50 && m == 50) printf("%s\n", st);
    getNextAlp();
    if (getDAG(n) == 0) {
        printf("-1\n");
        return 0;
    }
    int flag = solve(n, n - 1);
    for (int i = n - 1; i >= 0 && !flag; --i) {
        int tmp = st[i] - 'a';
        for (int j = 0; j <= 1 && !flag; ++j)
            if (nextAlp[st[i] - 'a'][j] <= 'z') {
                st[i] = nextAlp[tmp][j];
                flag = solve(n, i);
                if (flag) {
                    for (int k = i + 1; k <= n - 1; ++k) {
                        int u = firAlp[0];
                        int v = firAlp[1];
                        if (u > v) swap(u, v);
                        st[k] = u;
                        if (solve(n, k)) continue;
                        st[k] = v;
                    }
                }
            }
    }
    if (!flag) printf("-1\n");
    else printf("%s\n", st);
    return 0;
}
