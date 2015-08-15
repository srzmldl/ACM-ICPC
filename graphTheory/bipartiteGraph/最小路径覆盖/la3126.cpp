#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 512

using namespace std;
typedef int arrayN[MAXN];

struct node
{
	int t, ua, ub, va, vb;
} a[MAXN];

arrayN vis, match, w[MAXN];
int n, task;

int dfs(int x)
{
	REPP(i, 1, n)
		if (w[x][i] && !vis[i])
		{
			vis[i] = 1;
			if (!match[i] || dfs(match[i]))
			{
				match[i] = x;
				return 1;}
		}
	return 0;
}

int dist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}
int main()
{
	freopen("in.txt", "r", stdin);
	for (scanf("%d", &task); task; --task)
	{
		scanf("%d", &n);
		REPP(i, 1, n)
		{
			int hh, mm;
			scanf("%d:%d%d%d%d%d", &hh, &mm, &a[i].ua, &a[i].ub, &a[i].va, &a[i].vb);
			a[i].t = hh * 60 + mm;
		}
		REPP(i, 1, n)
			REPP(j, 1, n)
			if (a[i].t + dist(a[i].ua, a[i].ub, a[i].va, a[i].vb) + dist(a[i].va, a[i].vb, a[j].ua, a[j].ub) + 1 <= a[j].t)
				w[i][j] = 1;
			else w[i][j] = 0;
		MST(match, 0);
		int ans = 0;
		REPP(i, 1, n)
		{
			MST(vis, 0);
			if (dfs(i)) ++ ans;
		}
		printf("%d\n", n - ans);
	}
	return 0;
}
