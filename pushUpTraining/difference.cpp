#include<cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define MAXN 201234
#define MAXNUM 1123456

using namespace std;

struct node
{
    int val, l;
} g[MAXN];
int seg[MAXN * 4], base, a[MAXNUM * 2 + 10];

void change(int x, int val)
{
    x += base;
    seg[x] = val;
    for (x >>= 1; x; x >>= 1)
        seg[x] = max(seg[x << 1], seg[x << 1 ^ 1]);
}

int ask(int l, int r)
{
    if (l > r) return 0;
    l += base - 1;
    r += base + 1;
    int tmp = 0;
    for ( ; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) tmp = max(tmp, seg[l + 1]);
        if (r & 1) tmp = max(tmp, seg[r - 1]);
    }
    return tmp;
}
int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    for (base = 1; base <= n + 1; base <<= 1);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &g[i].val);
        g[i].val += MAXNUM;
        g[i].l = min(i - a[g[i].val], g[i - 1].l + 1);
        a[g[i].val] = i;
        change(i, g[i].l);
    }
    for (;m; m--)
    {
        int L, R;
        scanf("%d%d", &L, &R);
        L++, R++;
        int l = 1, r = R - L + 1;
        for (; l < r; )
        {
            int mid = (l + r + 1) >> 1;
            int segl = L + mid - 1;
            int segr = R;
            int tmp = ask(segl, segr);
            if (tmp >= mid) l = mid;
            else r = mid - 1;
        }
        printf("%d\n", l);
    }
    return 0;
}