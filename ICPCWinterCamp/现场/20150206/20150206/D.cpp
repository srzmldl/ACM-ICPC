#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 212345

using namespace std;
int d[MAXN];

struct node
{
	int a, b;
} g[MAXN];

int com(node A, node B)
{
	return A.a < B.a || (A.a == B.a && A.b < B.b);
}

int findfa(int fir, int h, int w, int i)
{
	if (i & 1)
	{
		
	} else 
	{
	}
	// int tmp = h % (2 * (w + 1));
	// if (!tmp) return i;
	// if (tmp < w)
	// {
	// 	if (i % 2)
	// 		return (i + tmp > w ? (w - (i + tmp - w) + 1) : (i + tmp));
	// 	else return (i - tmp > 0 ? (i - tmp): (-(i - tmp) + 1));
	// } else 
	// {
		
	// }
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("D.in", "r", stdin);
	int h, w, n;
	scanf("%d%d%d", &h, &w, &n);
	REPP(i, 1, n)
	{
		scanf("%d%d", &g[i].a, &g[i].b);
	}
	sort(g + 1, g + n + 1, com);
	REPP(i, 1, w)
	{
		int son = findSon(1, h, w, i);
		d[son] = i;
	}
	
	for (int i = 1; i <= n; --i)
	{
		int u = g[i].b, v = g[i].b + 1;
		int su = findSon(g[i].a, h - g[i].a, w, u);
		int sv = findSon(g[i].a, h - g[i].a, w, v);
		swap(d[su], d[sv]);
	}
	for (int i = 1; i <= w; ++i)
		printf("%d\n", d[i]);
	return 0;
}
