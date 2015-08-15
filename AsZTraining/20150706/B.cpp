#include <bits/stdc++.h>
#define MAXN 112345

using namespace std;

typedef unsigned long long ull;
const ull lim = 5LL * 1e18;

ull f[MAXN];
int base;
ull g[MAXN * 4];

void init()
{
    f[0] = 1;
    f[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        f[i] = f[i - 1] * 2;
        if (f[i] > lim) f[i] = lim + 1;
    }
}

ull add(ull A, ull B)
{
    ull tmp = A + B;
    if (tmp > lim) tmp = lim + 1;
}

ull ask(int l, int r)
{
    l += base - 1, r += base + 1;
    ull tmp = 0;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) tmp = add(tmp, g[l + 1]);
        if (r & 1) tmp = add(tmp, g[r - 1]);
    }
    return tmp;
}

int main()
{
    freopen("bubble.in", "r", stdin);
    freopen("bubble.out", "w", stdout);
    init();
    cout << lim << endl;
    for (;;)
    {
        int n;
        ull k;
        meset(g, 0, sizeof(g));
        for (base = 1; base <= n; base <<= 1);
        for (int i = 1; i <= n; ++i)
            g[i + base] = f[n - i];
        for (int i = base - 1; i >= 1; --i)
            g[i] = add(g[i << 1], g[i << 1 ^ 1]);
        cin >> n >> k;
        if (k + n == 0) break;
        for (int i = 1; i <= n; ++i)
        {
            int l = 1, r = n;
            for (; l < r; )
            {
                int mid = (l + r >> 1);
                ull tmp = ask(1, mid);
                if (tmp < k) l = mid + 1;
                else r = mid;
            }
            cout << l;
            change(l)      
            cout << " \n"[i == n];
        }
    }
    return 0;
}
