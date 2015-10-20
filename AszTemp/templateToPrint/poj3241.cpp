#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 60000, maxzb = 1000;
struct node{int x, y, k[2];} a[maxn];
struct point{int a, b, c;} b[maxn * 16];
struct treepoint{int k[2];} d[maxzb * 10];
int i, n, tot, f[maxn], lim, h, bh[maxn], kkk;
int comx(int p, int q) {return a[p].x < a[q].x;}
int comy(int p, int q) {return a[p].y < a[q].y;}
int com1(const point &p, const point &q) {return p.c < q.c;}
int getfa(int x) {if (f[x] != x) f[x] = getfa(f[x]); return f[x];}
int dist(int p, int q) {return abs(a[p].x - a[q].x) + abs(a[p].y - a[q].y);}
int minbh(int p, int q, int k) {return a[p].k[k] < a[q].k[k] ? p : q;}
int maxbh(int p, int q, int k) {return a[p].k[k] > a[q].k[k] ? p : q;}
void addx(int x)
{
    int mid = h + a[x].k[1];
    d[mid].k[0] = minbh(d[mid].k[0], x, 0);
    for (mid >>= 1; mid; mid >>= 1)
	d[mid].k[0] = minbh(d[mid << 1].k[0], d[mid << 1 ^ 1].k[0], 0);
    mid = h + a[x].k[0];
    d[mid].k[1] = maxbh(d[mid].k[1], x, 1);
    for (mid >>= 1; mid; mid >>= 1)
	d[mid].k[1] = maxbh(d[mid << 1].k[1], d[mid << 1 ^ 1].k[1], 1);
}
void addy(int x)
{
    int mid = h + a[x].k[1];
    d[mid].k[0] = minbh(d[mid].k[0], x, 0);
    for (mid >>= 1; mid; mid >>= 1)
	d[mid].k[0] = minbh(d[mid << 1].k[0], d[mid << 1 ^ 1].k[0], 0);
    mid = h + a[x].k[0];
    d[mid].k[1] = minbh(d[mid].k[1], x, 1);
    for (mid >>= 1; mid; mid >>= 1)
	d[mid].k[1] = minbh(d[mid << 1].k[1], d[mid << 1 ^ 1].k[1], 1);
}
int ask(int l, int r, int k, int boss)
{
    int mid = 0;
    if (l > r) return 0;
    for (l += h - 1, r += h + 1; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) mid = boss ? maxbh(mid, d[l + 1].k[k], k) : minbh(mid, d[l + 1].k[k], k);
        if (r & 1) mid = boss ? maxbh(mid, d[r - 1].k[k], k) : minbh(mid, d[r - 1].k[k], k);
    } return mid;
}
void link()
{
    for (i = 1; i <= n; ++i) bh[i] = i;
    a[0].k[0] = maxzb * 3, a[0].k[1] = -1;
    sort(bh + 1, bh + n + 1, comx);
    for (addx(bh[n]), i = n - 1; i; addx(bh[i]), --i) 
    {
        b[++tot].a = bh[i], b[tot].b = ask(a[bh[i]].k[1], lim, 0, 0);
        b[tot].c = dist(b[tot].a, b[tot].b);
        if (b[tot].b == 0) --tot;
        b[++tot].a = bh[i], b[tot].b = ask(1, a[bh[i]].k[0], 1, 1);
        b[tot].c = dist(b[tot].a, b[tot].b);
        if (b[tot].b == 0) --tot;
    }
    sort(bh + 1, bh + n + 1, comy);
    memset(d, 0, sizeof(d));
    a[0].k[1] = a[0].k[0];
    for (addy(bh[n]), i = n - 1; i; addy(bh[i]), --i)
    {
        b[++tot].a = bh[i], b[tot].b = ask(1, a[bh[i]].k[1], 0, 0);
        b[tot].c = dist(b[tot].a, b[tot].b);
        if (b[tot].b == 0) --tot;
        b[++tot].a = bh[i], b[tot].b = ask(1, a[bh[i]].k[0], 1, 0);
        b[tot].c = dist(b[tot].a, b[tot].b);
        if (b[tot].b == 0) --tot;
    }
}
void kruskal()
{
    int ans = n;
    sort(b + 1, b + tot + 1, com1);
    for (i = 1; i <= n; ++i) f[i] = i;
    for (i = 1; i <= tot; ++i)
    {
        int f1 = getfa(b[i].a), f2 = getfa(b[i].b);
        if (f1 != f2) 
        {
            --ans;
            if (ans == kkk) break;
            f[f1] = f2;
        }
    }
    printf("%d\n", b[i].c);
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%d%d", &n, &kkk);
    for (i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].k[0] = a[i].x + a[i].y + maxzb;
        a[i].k[1] = a[i].y - a[i].x + maxzb;
        lim = max(max(lim, a[i].k[0]), a[i].k[1]);
    }
    for (h = 1; h <= lim; h <<= 1);
    link();
    kruskal();
    return 0;
}
