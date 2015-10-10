#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 205
#define MAXM 21234

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];
int N, E, C, num;
const int INF = ~0U >> 1;
arrayN fir, d;
arrayM nxt, e;
long long c[MAXM], c0[MAXM];

struct edge
{
	int u, v, lab;
	edge(int u = 0, int v = 0, int lab = 0): u(u), v(v), lab(lab) {};
} g[MAXM], cand[MAXM];

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = 1LL * w;
}

void copy(long long cs[], long long cd[])
{
	REPP(i, 1, num) cd[i] = cs[i];
}

bool bfs(int s)
{
	MST(d, 0x3f);
	d[s] = 0;
	queue<int> que;
	que.push(s);
	for (; !que.empty();)
	{
		int u = que.front();
		que.pop();
		for (int p = fir[u]; p; p = nxt[p])
			if (c[p] && d[e[p]] > d[u] + 1)
			{
				d[e[p]] = d[u] + 1;
				que.push(e[p]);
			}
	}
	return d[N] < d[0];
}

long long dfs(int x, long long low)
{
	long long flow = 0;
	if (x == N) return low;
	for (int p = fir[x]; p; p = nxt[p])
		if (c[p] && d[e[p]] == d[x] + 1)
		{
			long long tmp = dfs(e[p], min(low, c[p]));
			if (!tmp) d[e[p]] = d[0];
			c[p] -= tmp, c[p ^ 1] += tmp;
			flow += tmp, low -= tmp;
			if (!low) break;
		}
	return flow;
}

int com(edge A, edge B)
{
	return A.u < B.u || (A.u == B.u && A.v < B.v);
}
void findCutEdge(long long base)
{
	int tot = 0;
	REPP(i, 1, N)
		if (d[i] < d[0])
			for (int p = fir[i]; p; p = nxt[p])
				if (d[e[p]] >= d[0] && (!(p & 1)))
					cand[++tot] = edge(i, e[p], p);
	copy(c, c0);

	int ansTot = 0;
	REPP(i, 1, tot)
	{
		copy(c0, c);
		c[cand[i].lab] = C;
		long long ans = base;
		for (; ans < C && bfs(1); ans += dfs(1, C));
		if (ans >= C) g[++ansTot] = cand[i];	
	}
	if (ansTot == 0) 
	{
		printf("not possible\n");
		return ;
	}
	sort(g + 1, g + ansTot + 1, com);
	printf("possible option:(%d,%d)", g[1].u, g[1].v);
	REPP(i, 2, ansTot)
		printf(",(%d,%d)", g[i].u, g[i].v);
	printf("\n");
}

int main()
{
	freopen("uva11248.in", "r", stdin);
	int task = 0;
	for (;;)
	{
		scanf("%d%d%d", &N, &E, &C);
		if (N + E + C == 0) break;
		num = 1;
		MST(fir, 0);
		REP(i, E)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			link(u, v, w);
			link(v, u, 0);
		}
		long long ans = 0;
		for (; ans < C && bfs(1); ans += dfs(1, C));
		++task;
		printf("Case %d: ", task);
		if (ans >= C)
		{
			printf("possible\n");
			continue;
		}
		findCutEdge(ans);
	}
	return 0;
}
