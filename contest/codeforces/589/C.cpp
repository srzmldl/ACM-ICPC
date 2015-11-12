#include <bits/stdc++.h>
#define MAXN 112345
#define MAXLEN 123
#define ll long long

using namespace std;

char st[MAXLEN];
int a[MAXN], len, cntAll[MAXLEN][30], cnt[30];
ll g[100][200][30];

int getPos(ll u) {
    if (u == 0) return 0;
    ll x = 63 - __builtin_clzll(u);
   // cout << l << ' ' <<  (1LL << (63 - x)) << endl;
    ll bef = 1LL << x;
    if (bef == u) return x;
    else return x + 1;
}

int askLast100(int pr, int tot, int x) {
    return g[pr][tot][x];
}

ll ask(ll rr, int x, int pr) {
    if (rr <= 0) return 0;
    if (pr == 0) {
        return 1LL * cntAll[rr][x];
    }
    ll lenBef = (1LL << (pr - 1)) * len;
    ll tmp;
    ll allX = (1LL << (pr - 1)) * cntAll[len][x];
    if (rr <= lenBef) return ask(rr, x, pr - 1);
    else {
        tmp = allX;
        rr -= lenBef;
    }
    int k = a[pr] % lenBef;
    ll tl = 1 - k, tr = rr - k;
    tl += lenBef;
    if (tr >= 1) {
        tmp += ask(tr, x, pr - 1);
        tmp += askLast100(pr - 1, lenBef - tl + 1, x);
    } else {
        tr += lenBef;
        tmp += (allX - ask(tl - 1, x, pr - 1) - askLast100(pr - 1, lenBef - tr, x));
    }
    return tmp;
}

void init() {
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < 26; ++j)
            cntAll[i + 1][j] = cntAll[i][j];
        cntAll[i + 1][st[i] - 'a'] = cntAll[i][st[i] - 'a'] + 1;
    }
}

char stLast[31234];

void initLast100() {
    int lastLen = len;
    for (int i = 0; i < len; ++i)
        stLast[i] = st[i];
    int flag = 0;
    int lim = 6400;
    if (lastLen >= lim) flag = 1;
    for (int i = 0; i <= 64; ++i) {
        for (int j = 1; j <= min(100, lastLen); ++j) {
            for (int k = 0; k < 26; ++k)
                g[i][j][k] = g[i][j - 1][k];
            g[i][j][stLast[lastLen - j] - 'a'] = g[i][j - 1][stLast[lastLen - j] - 'a'] + 1;
        }
        if (flag == 1) {
            lastLen -= a[i + 1];
        } else {
            for (int j = 0; j < lastLen; ++j)
                stLast[lastLen + (j + a[i + 1]) % lastLen] = stLast[j];
            lastLen *= 2;
            if (lastLen >= lim)
                flag = 1;
        }
    }
}

int main() {
#ifdef HOME
    freopen("C.in", "r", stdin);
#endif
    scanf("%s", st);
    len = strlen(st);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    initLast100();
    init();
    for (int i = 1; i <= m; ++i) {
        ll l, r;
        char c;
        scanf("%lld%lld %c\n", &l, &r, &c);
       // l = 1; r = 1e18;
        ll pr = getPos((r - 1) / len + 1);
        ll pl = (l - 1 >= 1 ? getPos((l - 1 - 1) / len + 1) : 0);
        cout << ask(r, c - 'a', pr) - ask(l - 1, c - 'a', pl) << endl;
    }
    return 0;
}