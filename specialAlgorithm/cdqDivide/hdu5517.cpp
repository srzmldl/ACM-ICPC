#include <bits/stdc++.h>
#define MAXN 112345

using namespace std;

struct node {
    int c, d, e;
    int f;
    long long cnt;
} g[MAXN], g1[MAXN];

int lab[MAXN], now = 0, cnt[MAXN], mx[MAXN];

int com(int u, int v) {
    node A = g[u], B = g[v];
    return A.c < B.c || (A.c == B.c && A.d < B.d) || (A.c == B.c && A.d == B.d && A.e < B.e);
}

int comd(int u, int v) {
    return g[u].d < g[v].d ;
}

const int eLim = 1123;
int base;
long long ti[eLim * 4], seg[eLim * 4];

void change(int pos, int f) {
    pos += base;
    if (ti[pos] != now) {
        seg[pos] = f;
        ti[pos] = now;
    } else seg[pos] += f;
    for (pos >>= 1; pos; pos >>= 1) {
        if (ti[pos << 1] != now) seg[pos << 1] = 0;
        if (ti[pos << 1 ^ 1] != now) seg[pos << 1 ^ 1] = 0;
        ti[pos] = now;
        seg[pos] = seg[pos << 1] + seg[pos << 1 ^ 1];
    }
}

int ask(int l, int r) {
    if (l > r) return 0;
    int tmp = 0;
    l += base - 1, r += base + 1;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1) {
        if (!(l & 1)) {
            if (ti[l + 1] == now) tmp += seg[l + 1];
        }
        if (r & 1) {
            if (ti[r - 1] == now) tmp += seg[r - 1];
        }
    }
    return tmp;
}

//after solve d increse
int tmpArr[MAXN];

void solve(int l, int r) {
    if (r <= l) return ;
    int mid = (r + l) >> 1;
    solve(mid + 1, r);

    for (int i = l; i <= mid; ++i)
        tmpArr[i] = lab[i];
    
    sort(lab + l, lab + mid + 1, comd);

   // prt(l, r);
    ++now;
    int j = r + 1;
    for (int i = mid; i >= l; --i) {
        for (; j - 1 >= mid + 1 && g[lab[j - 1]].d >= g[lab[i]].d; --j) {
            change(g[lab[j - 1]].e, 1);
        }
        g[lab[i]].f += ask(g[lab[i]].e, eLim - 100);
    }

    for (int i = l; i <= mid; ++i)
        lab[i] = tmpArr[i];
    solve(l, mid);

    
    j = r + 1;
    int pos = r;
    for (int i = mid; i >= l; --i) {
        for (; j - 1 >= mid + 1 && g[lab[j - 1]].d >= g[lab[i]].d; --j) {
            tmpArr[pos--] = lab[j - 1];
        }
        tmpArr[pos--] = lab[i];
    }
    for (; j - 1 >= mid + 1; j--)
        tmpArr[pos--] = lab[j - 1];
    for (int i = l; i <= r; ++i)
        lab[i] = tmpArr[i];
}

int equ(node A, node B) {
    return A.c == B.c && A.d == B.d && A.e == B.e;
}
int main() {
//#ifdef HOME
    //  freopen("1009.in", "r", stdin);
//#endif
    int T;
    scanf("%d", &T);
    for (int ca = 1; ca <= T; ++ca) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(cnt, 0, sizeof(cnt));
        memset(mx, 0, sizeof(mx));
        for (int i = 1; i <= n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            if (u > mx[v]) {
                mx[v] = u;
                cnt[v] = 1;
            } else if (u == mx[v]) {
                cnt[v]++;
            }
        }
        for (int i = 1; i <= m; ++i) {
            int c, d, e;
            scanf("%d%d%d", &c, &d, &e);
            g[i].d = c;
            g[i].e = d;
            g[i].c = mx[e];
            g[i].cnt = cnt[e];
            g[i].f = 0;
            lab[i] = i;
        }
        sort(lab + 1, lab + m + 1, com);
        int tot = 1;
        g1[1] = g[lab[1]];
        for (int i = 2; i <= m; ++i) {
            if (!equ(g[lab[i]], g[lab[i - 1]]))
                g1[++tot] = g[lab[i]];
            else g1[tot].cnt += g[lab[i]].cnt;
        }
        for (int i = 1; i <= tot; ++i)
            g[i] = g1[i];
        for (int i = 1; i <= tot; ++i)
            lab[i] = i;
        sort(lab + 1, lab + tot + 1, com);
        for (base = 1; base <= eLim - 100; base <<= 1);
      //  cout << tot << endl;
        solve(1, tot);
        long long ans = 0;
        for (int i1 = 1; i1 <= tot; ++i1) {
            int i = lab[i1];
         //   printf("%d : (%d, %d, %d) %d %d\n", i, g[i].c, g[i].d, g[i].e, g[i].f, g[i].cnt);
            if (!g[i].f) {
                ans += g[i].cnt;
            }
        }
        printf("Case #%d: %lld\n", ca, ans);
    }
    return 0;
}