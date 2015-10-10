#include <bits/stdc++.h>
#define MAXN 11234
#define MAXM 2123456

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, mcsOrder, label, col;
arrayM e, nxt;
int num, n, base, seg[MAXN * 4];
set <int> s;

void link(int u, int v) {
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

int maxLab(int u, int v) {
    return label[u] > label[v] ? u : v;
}

void change(int x, int val) {
    label[x] = val;
    x += base;
    for (x >>= 1; x; x >>= 1) {
        seg[x] = maxLab(seg[x << 1], seg[x << 1 ^ 1]); 
    }
}

void getMCS() {
    for (base = 1; base <= n + 1; base <<= 1);
    for (int i = 1; i <= n; ++i) seg[i + base] = i;
    label[0] = -1;
    for (int i = base - 1; i >= 1; --i)
        seg[i] = maxLab(seg[i << 1], seg[i << 1 ^ 1]);
    int tot = 0;
    for (int i = 1; i <= n; ++i) {
        int x = mcsOrder[++tot] = seg[1];
        change(x, -1);
        for (int p = fir[x]; p; p = nxt[p]) {
            if (label[e[p]] >= 0) change(e[p], label[e[p]] + 1);
        }
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v);
        link(v, u);
    }
    getMCS();
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        s.insert(i);
    for (int j = 1; j <= n; ++j)  {
        int i = mcsOrder[j];
        for (int p = fir[i]; p; p = nxt[p]) {
            set<int>::iterator it = s.find(col[e[p]]);
            if (it != s.end())
                s.erase(it);
        }
        col[i] = *s.begin();
        ans = max(ans, col[i]);
        for (int p = fir[i]; p; p = nxt[p]) {
            set<int>::iterator it = s.find(col[e[p]]);
            if (col[e[p]] && it == s.end())
                s.insert(col[e[p]]);
        }
    }
    printf("%d\n", ans);
    return 0;
}