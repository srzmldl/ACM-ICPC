#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) n; ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 61234
#define MAXM 212345
#define LIMTWO 19

using namespace std;

struct edge
{
	int u, v, w;
	edge(int u = 0, int v = 0, int w = 0) : u(u), v(v), w(w) {};
} ed[MAXM];

typedef int arrayN[MAXN], arrayM[MAXM];

int n, num, m;
arrayN fir, dep;
arrayM nxt, e, c, f;
int big[MAXN][LIMTWO], ff[MAXN][LIMTWO];

int comEd(edge A, edge B)
{
	return A.w < B.w;
}

int getfa(int x)
{
	return (x == f[x]) ? x : (f[x] = getfa(f[x]));
}

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

void dfs(int u, int fa, int depth)
{
	ff[u][0] = fa;
	dep[u] = depth;
	for (int p = fir[u]; p; p = nxt[p])
		if (e[p] != fa)
		{
			big[e[p]][0] = c[p];
			dfs(e[p], u, depth + 1);
		}
}

int main()
{
	freopen("uva11354.in", "r", stdin);
	int flag = 0;
	for (; scanf("%d%d", &n, &m) != EOF; )
	{
		if (flag) printf("\n");
		else flag =1;
		REP(i, m)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			ed[i] = edge(u, v, w);
		}
		sort(ed, ed + m, comEd);
		REPP(i, 1, n) f[i] = i;
		num = 0;
		MST(fir, 0);
		REP(i, m)
		{
			int fu = getfa(ed[i].u);
			int fv = getfa(ed[i].v);
			if (fu != fv)
			{
				link(ed[i].u, ed[i].v, ed[i].w);
				link(ed[i].v, ed[i].u, ed[i].w);
				f[fu] = fv;
			}
		}
		MST(big, 0);
		MST(ff, 0);
		REPP(i, 1, n)
			if (ff[i][0] == 0)
				dfs(i, 0, 1);
		REPP(j, 1, LIMTWO - 1)
			REPP(i, 1, n)
		{
			big[i][j] = max(big[i][j - 1], big[ff[i][j - 1]][j - 1]);
			ff[i][j] = ff[ff[i][j - 1]][j - 1];
		}
		int task;
		for (scanf("%d", &task); task; --task)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			int ans = 0;
			if (dep[u] < dep[v]) swap(u, v);
			int tmp = dep[u] - dep[v];
			for (int i = LIMTWO - 1; i >= 0; --i)
				if ((1 << i) <= tmp)
				{
					ans = max(ans, big[u][i]);
					tmp -= (1 << i);
					u = ff[u][i];
				}
			for (int i = LIMTWO - 1; i >= 0; --i)
				if (ff[u][i] != ff[v][i])
				{
					ans = max(ans, max(big[u][i], big[v][i]));
					u = ff[u][i];
					v = ff[v][i];
				}
			if (u != v)
				ans = max(ans, max(big[u][0], big[v][0]));
			printf("%d\n", ans);
		}
	}
	return 0;
}
