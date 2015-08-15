#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXN 1123
#define MST(a, b) memset((a), (b), sizeof(a))
//求出匹配之后，Ｘ中未匹配的顶开始增广。最后顶覆盖就是Ｙ中访问过的顶和Ｘ中未访问过的顶
using namespace std;

int n, m, tot, w[MAXN][MAXN], vis[MAXN], cok[MAXN], rok[MAXN], match[MAXN];

int dfs(int x)
{
	REPP(i, 1, n)
		if (w[x][i] && !vis[i])
		{
			vis[i] = 1; //容易忽略
			if (!match[i] || dfs(match[i])) 
			{
				match[i] = x;
				return 1;
			}
		}
	return 0;
}

void dfs2(int x)
{
	rok[x] = 1;
	REPP(i, 1, n)
		if (w[x][i] && !cok[i])
		{
			cok[i] = 1;
			dfs2(match[i]);
		}
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (;;)
	{
		scanf("%d%d%d", &n, &m, &tot);
		if (n + m + tot == 0) break;
		MST(w, 0);
		REPP(i, 1, tot)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			w[u][v] = 1;
		}
		MST(match, 0);
		int ans = 0;
		REPP(i, 1, n)
		{
			MST(vis, 0);
			if (dfs(i)) ++ans;
		}
		printf("%d", ans);
		MST(vis, 0);
		MST(rok, 0);
		MST(cok, 0);
		REPP(i, 1, n)
			vis[match[i]] = 1;
		REPP(i, 1, n)
			if (!vis[i])
				dfs2(i);
		REPP(i, 1, n)
			if (!rok[i])
				printf(" r%d", i);
		REPP(i, 1, n)
			if (cok[i])
				printf(" c%d", i);
		printf("\n");
	}
	return 0;
}
