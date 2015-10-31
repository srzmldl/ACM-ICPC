#include <bits/stdc++.h>
#define MAXN 112345
#define MAXLEN 123
#define ll long long

using namespace std;

char st[MAXLEN];
int a[MAXN], len, cntAll[MAXLEN][MAXLEN][30], cnt[30];
ll g[MAXLEN][MAXLEN];

int getPos(ll u) {
    ll x = 63 - __builtin_clzll(u);
   // cout << l << ' ' <<  (1LL << (63 - x)) << endl;
    ll bef = 1LL << x;
    if (bef < u) return x + 1;
    else return x;
}

ll getAll(int l, int r) {
    if (l > r) return 0;
    else return g[l][r];
}

ll ask(ll rl, ll rr, int x) {
    if (rl < 1) rl = 1;
    if (rl > rr) return 0;
    if (rr <= len) {
        return 1LL * cntAll[rl][rr][x];
    }
    ll l = (rl - 1) / len + 1;
    ll r = (rr - 1) / len + 1;
    if (l > r) return 0;
    int pl = getPos(l);
    int pr = getPos(r);
    ll tmp = getAll(pl + 1, pr - 1) * cnt[x];
    if (pl < pr) {
        tmp += ask(rl, (1LL << pl) * len, x);
        rl = ((1LL << (pr - 1))) * len + 1;
        pl = pr;
    }
    if (pl == pr && (rr == ((1LL << pr) * len)) && (rl == ((1LL << (pr - 1))) * len + 1)) {
        tmp += getAll(pr, pr) * cnt[x];
        return tmp;
    }
    //map l, r
    ll lenBef = (1LL << (pr - 1)) * len;
    rl -= lenBef;
    rr -= lenBef;
    int k = a[pr] % lenBef;
    rl -= k;
    rr -= k;
    if (rl >= 1) tmp += ask(1, rr, x) - ask(1, rl - 1, x);
    else if (rr <= 0) tmp += ask(1, rr + lenBef, x) - ask(1, rl + lenBef - 1, x);
    else {
        tmp += (ask(1, rr, x) + ask(1, lenBef, x) - ask(1, rl + lenBef - 1, x));
    }
    return tmp;
}

void init() {
    for (int i = 0; i < len; ++i)
        cnt[st[i] - 'a']++;
    for (int i = 1; i <= 63; ++i)
        for (int j = 1; j <= 63; ++j)
        {
            g[i][j] = 0;
            for (int k = i; k <= j; ++k)
                g[i][j] += (1LL << (k - 1));
        }
    for (int i = 0; i < len; ++i)
        for (int j = i; j < len; ++j) {
            for (int k = i; k <= j; ++k)
                cntAll[i + 1][j + 1][st[k] - 'a']++;
        }
}

int main() {
//#ifdef HOME
    freopen("C.in", "r", stdin);
//#endif
    scanf("%s", st);
    len = strlen(st);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
   // n = 100000;
   // for (int i = 1; i <= n; ++i)
     //   a[i] = 5;
    init();
    for (int i = 1; i <= m; ++i) {
        ll l, r;
        char c;
        scanf("%lld%lld %c\n", &l, &r, &c);
       // l = 1; r = 1e18;
        cout << ask(1, r, c - 'a') - ask(1, l - 1, c - 'a') << endl;
    }
    return 0;
}