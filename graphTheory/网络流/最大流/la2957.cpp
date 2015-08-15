#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 11234
#define MAXM 112345

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];
arrayN fir, d, pos;
arrayM e, nxt, c;
const int INF = 0x3f3f3f3f;
int N, M, K, S, T, day, num;

struct edge
{int u, v;} ed[MAXM];

struct node
{
	node(int a = 0, int b = 0): a(a), b(b) {};
	int a, b;
} g[MAXM];
void link(int u, int v, int w)
{
	e[++num] = v;
	nxt[num] = fir[u];
	fir[u] = num;
	c[num] = w;
}
bool bfs(int s)
{
	MST(d, 0x3f);
	queue<int> que;
	que.push(s);
	d[s] = 0;
	for (;!que.empty();)
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
	REPP(i, 0, day) if (d[T + i * N] < d[MAXN - 1]) return true;
	return false;
}

int dfs(int x, int low)
{
	if (x % N == T) return low;
	int flow = 0;
	for (int p = fir[x]; p; p = nxt[p])
		if (c[p] && d[e[p]] == d[x] + 1)
		{
			int tmp = dfs(e[p], min(low, c[p]));
			if (tmp == 0) d[e[p]] = d[MAXN - 1];
			c[p] -= tmp, c[p ^ 1] += tmp;
			flow += tmp, low -= tmp;
		}
	return flow;
}

int main()
{
	freopen("la2957.in", "r", stdin);
	for (; scanf("%d%d%d%d%d", &N, &M, &K, &S, &T) != EOF; )
	{
		S--, T--;
		REP(i, M)
		{
			scanf("%d%d", &ed[i].u, &ed[i].v);
			ed[i].u--, ed[i].v--;
		}
		day = 0;
		num = 1;
		MST(fir, 0);
		int ship = 0;
		for (;;)
		{
			++day;
			REP(i, M)
			{
				link(ed[i].u + (day - 1) * N, ed[i].v + day * N, 1);
				link(ed[i].v + day * N, ed[i].u + (day - 1) * N, 0);
				link(ed[i].v + (day - 1) * N, ed[i].u + day * N, 1);
				link(ed[i].u + day * N, ed[i].v + (day - 1) * N, 0);
			}
			REPP(i, 0, N)
			{
				link((day - 1) * N + i, day * N + i, K * 2);
				link(day * N + i, (day - 1) * N + i, 0);
			}
			for (; bfs(S); ship += dfs(S, INF));
			if (ship >= K) break;
		}
		printf("%d\n", day);
		REPP(i, 1, K) pos[i] = S;
		REPP(i, 1, day)
		{
			int tot = 0;
			REPP(j, 1, K)
			{
				int flag = 1;
				for (int p = fir[pos[j]]; p; p = nxt[p])
					if (e[p] / N == i && c[p] == 0)
					{
						g[++tot] = node(j, e[p] % N + 1);
						pos[j] = e[p];
						c[p] ++;
						flag = 0;
						break;
					}
				if (flag) pos[j] += N;
				
			}
			printf("%d", tot);
			REPP(j, 1, tot)
			{
				printf(" %d %d", g[j].a, g[j].b);
			}
			printf("\n");
		}
	}
	return 0;
}
