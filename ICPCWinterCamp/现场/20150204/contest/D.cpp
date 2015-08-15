#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 812345

using namespace std;

int tot = 0, n, lab[MAXN], t, d[MAXN * 4];

struct node
{
	node(int A1 = 0, int B1 = 0, int f1 = 0, int go1 = 0)
		{
			A = A1, B = B1, f = f1, go = go1;
		}
	int A, B, f, go;
}g[MAXN];

int com(int u, int v)
{
	return (g[u].A < g[v].A || (g[u].A == g[v].A && g[u].B < g[v].B) || (g[u].A == g[v].A && g[u].B == g[v].B && (g[u].go < g[v].go)));
}

int ask(int l, int r)
{
	l++, r++;
	if (l > r) return 0;
	l += t - 1, r += t + 1;
	int tmp = 0;
	for (; (l ^ r) != 1; l >>= 1, r >>= 1)
	{
		if (!(l & 1)) tmp = max(tmp, d[l + 1]);
		if (r & 1) tmp = max(tmp, d[r - 1]);
	}
	return tmp;
}

void change(int x, int value)
{
	x++;
	x += t;
	d[x] = max(d[x], value);
	for (x >>= 1; x; x >>= 1)
		d[x] = max(d[x], value);
}

void solve()
{
	sort(lab + 1, lab + tot + 1, com);
/*	REPP(i, 1, tot)
		printf("%d\n", lab[i]);
	REPP(j, 1, tot)
	{
		int i = lab[j];
		printf("%d : %d %d %d\n", i, g[i].A, g[i].B, g[i].go);
		}*/
	int ans = 0, maxB = 0;
	REPP(i, 1, tot)
		maxB = max(maxB, g[i].B);
	for (t = 1; t <= maxB + 1; t <<= 1);
	
	REPP(i, 1, tot)
	{
		int now = lab[i];
		int lft = ask(0, g[now].B);
		g[now].f = max(g[now].f, lft);
		if (g[now].go)
			g[g[now].go].f = max(g[g[now].go].f, g[now].f + 1);
		change(g[now].B, g[now].f);
	}
	REPP(i, 1, tot)
		ans = max(ans, g[i].f);
	cout << ans << endl;
}

void addPointA(int i, int x, int y)
{
	int A = x, B = i - 1 - x;
	if (A >= 0 && B >= 0)
	{
		++tot;
		g[tot] = node(A, B, 0, tot + 1);
		++tot;
		int nA = x + 1, nB = i - 1 - x;
		g[tot] = node(nA, nB, 0, 0);
	}
	A = y, B = i - 1 - y;
	if (A >= 0 && B >= 0)
	{	
		++tot;
		g[tot] = node(A, B, 0, tot + 1);
		++tot;
		int nA = y, nB = i - y;
		g[tot] = node(nA, nB, 0, 0);	
	}
}

void addPointB(int i, int x, int y)
{
	int A = i - 1 - x, B = x;
	if (A >= 0 && B >= 0)
	{
		++tot;
		g[tot] = node(A, B, 0, tot + 1);
		++tot;
		int nA = i - x, nB = x;
		g[tot] = node(nA, nB, 0, 0);
	}
	A = i - 1 - y, B = y;
	if (A >= 0 && B >= 0)
	{
		++tot;
		g[tot] = node(A, B, 0, tot + 1);
		++tot;
		int nA = i - y - 1, nB = y + 1;
		g[tot] = node(nA, nB, 0, 0);
	}
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("D.in", "r", stdin);
	scanf("%d\n", &n);
	tot = 0;
	REPP(i, 1, n)
	{
		char ch;
		int x, y;
		scanf("%c%d%d\n", &ch, &x, &y);
		if (ch == 'A')
			addPointA(i, x, y);
		else addPointB(i, x, y);
	}
/*	REPP(i, 1, n)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		++tot;
		g[tot] = node(x1, y1, 0, tot + 1);
		++tot;
		g[tot] = node(x2, y2, 0, 0);
		}*/

	REPP(i, 1, tot)
		lab[i] = i;
	solve();
	return 0;
}
