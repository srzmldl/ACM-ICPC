#include <bits/stdc++.h>
#define MAXN 1123
#define MAXM 2123456

using namespace std;
const int len = 1000000;
typedef int arrayN[MAXN], arrayM[MAXM];

struct node
{
	int l, r;
	node (int l = 0, int r = 0) : l(l), r(r) {};
}g[MAXN];

arrayN fir, vis, f, fa;
arrayM e, nxt, c;
int a[MAXN][MAXN], num, n;
vector<int> slack, cost;

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

int getfa(int x)
{
	return f[x] == x ? x : (f[x] = getfa(f[x]));
}

void dfs(int x, int father, int co)
{
	vis[x] = 1;
	fa[x] = father;
	slack.push_back(x);
	cost.push_back(co);
	for (int p = fir[x]; p; p = nxt[p])
		if (!vis[e[p]]) dfs(e[p], x, c[p]);
}

int calc(int l1, int r1, int l2, int r2)
{
	int tl1 = max(l1, l2);
	int tr1 = min(r1, r2);
	if (tl1 >= tr1) return 0;
	return tr1 - tl1;
}

int check(int l, int r, int j)
{
	for (int i = 0; i < j; ++i)
		if (calc(l, r, g[slack[i]].l, g[slack[i]].r) != a[slack[j]][slack[i]])
			return 0;
	return 1;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			int x;
			scanf("%d", &x);
			a[i][j] = x;
			if (i != j && x > 0)
				link(i, j, x);
		}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
		{
			g[i].l = 0, g[i].r = len;
			slack.clear();
			cost.clear();
			dfs(i, 0, 0);
			int tot = slack.size();
			for (int j = 1; j < tot; ++j)
			{
				int u = fa[slack[j]];
				int v = slack[j];
				int co = cost[j];
				int lx = g[u].l, rx = g[u].r;
				if (check(rx - co, rx - co + len, j))
					g[v] = node(rx - co, rx - co + len);
				else if (check(lx + co - len, lx + co, j))
					g[v] = node(lx + co - len, lx + co);
				else 
				{
					printf("NO\n");
					return 0;
				}
			}
		}
	printf("YES\n");
	return 0;
}
