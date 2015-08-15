#include <bits/stdc++.h>
#define MAXN 112345

using namespace std;

typedef unsigned long long ull;
const ull lim = 5LL * 1e18;

int segBase, ans[MAXN];
ull f[MAXN], g[MAXN * 4];


ull add(ull A, ull B)
{
    ull tmp = A + B;
    if (tmp > lim) tmp = lim + 1;
    return tmp;
}

void change(int x, ull value)
{
    x++;
    x += segBase;
    g[x] = value;
    for (x >>= 1; x; x >>= 1)
        g[x] = add(g[x << 1], g[x << 1 ^ 1]);
}

ull ask(int l, int r)
{
    l++, r++;
    if (l > r) return 0;
    l += segBase - 1, r += segBase + 1;
    ull tmp = 0;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) tmp = add(tmp, g[l + 1]);
        if (r & 1) tmp = add(tmp, g[r - 1]);
    }
    return tmp;
}

void init()
{
    
    f[0] = 1;
    f[1] = 1;
    int lim = 100100;
    
    for (segBase = 1; segBase <= lim; segBase <<= 1);
    for (int i = 2; i <= lim; ++i)
        f[i] = add(f[i - 1], f[i - 1]);
    for (int i = 0; i <= lim; ++i)
        change(i, f[i]);
}


void solve(int n, ull k, int base)
{
    if (n == 0) return ;
    int l = 1, r = n;
    for (; l < r; )
    {
        int mid = l + r >> 1;
        int d = n - mid;
        int u = n - 1;
        ull tmp = ask(d, u);
        if (tmp >= k) r = mid;
        else l = mid + 1;
    }
    int d = n - l + 1;
    int u = n - 1;
    ull tmp = ask(d, u);
    ans[base + 1] = l + base;
    for (int i = 1; i < l; ++i)
        ans[base + 1 + i] = i + base;
    solve(n - l, k - tmp, base + l);
}

int main()
{
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    init();
    //   cout << lim << endl;
    for (;;)
    {
        int n;
        ull k;
        cin >> n >> k;
        //cout << n << k<< endl;
        if (k + n == 0) break;
        solve(n, k, 0);
        for (int i = 1; i <= n; ++i)
            cout << ans[i] << " \n"[i == n];
    }
    return 0;
}
