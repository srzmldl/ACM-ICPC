#include <bits/stdc++.h>
#define MAXN 1123456
using namespace std;

struct node
{
	int lmax, rmin;
	int amax, amin;
	int son[2];
}g[MAXN];

char st[10];
int n, c;

int dfs(int x, node &gf)
{
//	if (g[x].lmax >= g[x].rmin) return 0;
//	if (g[x].lmax <= x && g[x].lmax) return 0;
//	if (g[x].rmin <= x && g[x].rmin) return 0;
//	if (g[x].amax <= x) return 1;
	if (g[x].amax == g[x].amin && g[x].amax == x) return 1;
	if (g[x].lmax > x)
	{
		g[x].son[0] = x + 1;
		g[x + 1].amax = max(g[x + 1].amax, g[x].lmax);
		g[x + 1].amin = min(g[x + 1].amin, g[x].lmax);
		if (!dfs(x + 1, g[x])) return 0;
		if (g[x].amax > g[x + 1].amax)
		{
			g[x].son[1] = g[x + 1].amax + 1;
			int np = g[x].son[1];
			g[np].amax = max(g[np].amax, g[x].amax);
			g[np].amin = min(g[np].amin, g[x + 1].amax + 1);
			if (!dfs(g[x + 1].lmax + 1, g[x])) return 0;
		}
	} else 
	{
		if (g[x].amax > x)
		{
			g[x].son[1] = x + 1;
			int np = g[x].son[1];
			g[np].amax = max(g[np].amax, g[x].amax);
			g[np].amin = min(g[np].amin, g[x].amax);
			if (!dfs(x + 1, g[x])) return 0;
		}
	}
	int p = 0;
	if (gf.son[1] == x) p = 1;
	gf.amax = max(gf.amax, g[x].amax);
	gf.amin = min(gf.amin, g[x].amin);
	if (p == 0) gf.lmax = max(gf.lmax, g[x].amax);
	else gf.rmin = min(gf.rmin, g[x].amin);
	return 1;
}

void dfsInOrder(int x)
{
	if (g[x].son[0]) dfsInOrder(g[x].son[0]);
	printf("%d ", x);
	if (g[x].son[1]) dfsInOrder(g[x].son[1]);
}

void prtAns()
{
	dfsInOrder(1);
}

int main()
{
	freopen("D.in", "r", stdin);
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; ++i)
	{
		g[i].lmax = 0, g[i].rmin = n + 1;
		g[i].amax = 0, g[i].amin = n + 1;
	}
	for (int i = 1; i <= c; ++i)
	{
		int u, v;
		scanf("%d%d%s", &u, &v, st);
		if (st[0] == 'L')
			g[u].lmax = max(g[u].lmax, v);
		else g[u].rmin = min(g[u].rmin, v);
		g[u].amax = max(g[u].amax, v);
		g[u].amin = min(g[u].amin, v);
	}
	g[1].amax = n;
	g[1].amin = 1;
	if (dfs(1, g[0])) prtAns();
	else printf("IMPOSSIBLE\n");
	return 0;
}

