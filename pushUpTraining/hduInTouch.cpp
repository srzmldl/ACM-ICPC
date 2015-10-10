#include <bits/stdc++.h>
#define MAXN 212345

typedef int arrayN[MAXN];

using namespace std;

int base, high;
arrayN a, b, c;
long long ans[MAXN];

struct segment
{
    int id;
    long long mi, lazy;
} seg[MAXN * 4];

const long long INF = (long long) 1e18;

void makeLazy(int x, long long val)
{
    if (seg[x].mi == INF) return ;
    if (val < seg[x].mi)
    {
        seg[x].mi = min(seg[x].mi, val);
    }
    if (seg[x].lazy)
        seg[x].lazy = min(seg[x].lazy, val);
    else seg[x].lazy = val;
}

void pushdown(int p)
{
    for (int i = high - 1; i >= 1; --i)
    {
        int x = p >> i;
        if (seg[x].lazy)
        {
            makeLazy(x << 1, seg[x].lazy);
            makeLazy(x << 1 ^ 1, seg[x].lazy);
            seg[x].lazy = 0;
        }
    }
}
void update(int x)
{
    for (x >>= 1; x; x >>= 1)
    {
        if (seg[x << 1].mi < seg[x << 1 ^ 1].mi)
            seg[x].id = seg[x << 1].id;
        else seg[x].id = seg[x << 1 ^ 1].id;
        seg[x].mi = min(seg[x << 1].mi, seg[x << 1 ^ 1].mi);
    }
}

void change(int x, long long val)
{
    x += base;
    pushdown(x);
    seg[x].id = x - base;
    seg[x].mi = val;
    update(x);
}


void dye(int l, int r, long long val)
{
    if (l > r) return ;
    l += base - 1, r += base + 1;
    int tl = l, tr = r;
    pushdown(l), pushdown(r);
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) makeLazy(l + 1, val);
        if (r & 1) makeLazy(r - 1, val);
    }
    update(tl), update(tr);
}

int main()
{
    ///  freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int ca;
    for (scanf("%d", &ca); ca; --ca)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i <= n; ++i)
            scanf("%d", b + i);
        for (int i = 1; i <= n; ++i)
            scanf("%d", c + i);
        for (base = 1, high = 1; base <= n + 2; base <<= 1, ++high);
        change(0, INF);
        for (int i = base + 1; i < base * 2; ++i)
        {
            int tmp = i - base;
            long long tval = INF;
            if (tmp <= n) tval--;
            change(i - base, tval);
        }
        change(1, 0);
        for (int i = 1; i <= n; ++i)
            ans[i] = -1;
        for (;;)
        {
            if (seg[1].mi >= INF - 1) break;
            int id = seg[1].id;
            ans[id] = seg[1].mi;
            long long tmp = ans[id] + c[id];
            change(id, INF);
            int l = max(id - b[id], 1);
            int r = max(id - a[id], 0);
            if (r == id) r--;
            if (l <= r) dye(l, r, tmp);
            l = min(id + a[id], n + 1);
            r = min(id + b[id], n);
            if (l == id) l++;
            if (l <= r) dye(l, r, tmp);
        }
        for (int i = 1; i <= n; ++i)
            printf("%lld%c", ans[i], " \n"[i == n]);
    }
    return 0;
}
