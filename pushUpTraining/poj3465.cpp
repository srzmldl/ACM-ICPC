#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define MAXN 112345

using namespace std;

int a[MAXN];

struct node
{
    int id, ma;
} seg[MAXN * 4];

int base;
const int INF = 112345;

void change(int x, int val)
{
    seg[x + base].id = x;
    x += base;
    seg[x].ma = val;
    for (x >>= 1; x; x >>= 1)
    {
        seg[x] = seg[x << 1];
        if (seg[x << 1 ^ 1].ma > seg[x].ma)
            seg[x] = seg[x << 1 ^ 1];
    }
}

int ask(int l, int r, int &id)
{
    if (l > r) return 0;
    l += base - 1, r += base + 1;
    int tmp = 0;
    id = 0;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1))
        {
            if (seg[l + 1].ma > tmp)
            {
                tmp = seg[l + 1].ma;
                id = seg[l + 1].id;
            }
        }
        if (r & 1)
        {
            if (seg[r - 1].ma > tmp)
            {
                tmp = seg[r - 1].ma;
                id = seg[r - 1].ma;
            }
        }
    }
    return tmp;
}

int main()
{
    //  freopen("in.txt", "r", stdin);
    int N, x, y, H1, H2;
    for (;scanf("%d%d%d%d%d", &N, &x, &y, &H1, &H2) != EOF;)
    {
        for (int i = 1; i <= N; ++i)
            scanf("%d", &a[i]);
        int attCnt = ((H2 - 1) / x) + 1;
        for (base = 1; base <= N + 2; base <<= 1);
        for (int i = 1; i <= N; ++i)
            change(i, -INF);
        int ans = 0;
        int lcnt = 0;
        int ans2 = 0;
        for (int i = 1; i <= N && attCnt; ++i)
        {
            H1 -= a[i];
            attCnt--;
            ++lcnt;
            ans2 = max(ans2, lcnt);
            if (attCnt == 0 || i == N)
            {
                ans = i;
                break;
            }
            change(i, max(a[i], y));
            if (H1 <= 0)
            {
                int id;
                int x = ask(1, i, id);
                H1 += x;
                change(id, -INF);
                ++attCnt;
                --lcnt;
            }
        }
        if (attCnt == 0)
        {
            printf("Win\n");
            printf("%d\n", ans);
        } else
        {
            printf("Lose\n");
            printf("%d\n", ans2 * x);
        }
    }
    return 0;
}
