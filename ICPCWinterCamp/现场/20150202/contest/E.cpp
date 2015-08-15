#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 200000

using namespace std;

int L, S, tot;

struct node
{
	int l, r, len, h;
}g[MAXN];

struct point
{int x, y;} a[MAXN];

int main() {
//	ios :: sync_with_stdio(0);
//	freopen("E.in", "r", stdin);
	scanf("%d%d", &L, &S);
	if ((L & 1) || (L > S * 2 + 2))
	{
		printf("-1\n");
		return 0;
	}
	g[0].l = 0, g[0].r = S, g[0].h = 1, g[0].len = S;
	int plus = 2 * S + 2 - L;
	tot = 0;
	for (;plus;)
	{
		if (g[tot].l + 1 == g[tot].r) break;
		int x = plus / 2 + g[tot].h;
		
		if (x > g[tot].len / 2)
			x = g[tot].len / 2;
		
		plus += 2 * g[tot].h - 2 * x;
		
		++tot;
		g[tot].l = g[tot - 1].l + x;
		g[tot].r = g[tot].l + x;
		g[tot].len = x;
		g[tot].h = g[tot - 1].h * 2;
	}
	if (plus)
	{
		printf("-1\n");
		return 0;
	}
	int n = 0;
	int y = 0;
	REPP(i, 0, tot)
	{
		if (i == 0 || (g[i].r != g[i - 1].r))
		{
			a[++n].x = g[i].r;
			a[n].y = y;
		}
		y = g[i].h;
		if (i == tot || (g[i].r != g[i + 1].r))
		{
			a[++n].x = g[i].r;
			a[n].y = y;
		}
	}
	a[++n].x = g[tot].l;
	a[n].y = y;
	a[++n].x = g[tot].l;
	a[n].y = 0;
	printf("%d\n", n);
	REPP(i, 1, n)
		printf("%d %d\n", a[i].x, a[i].y);

	return 0;
}
