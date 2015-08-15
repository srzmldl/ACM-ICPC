#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define memOO(a) memset((a), 12, sizeof(a))
#define mem(a) memset((a), 0, sizeof(a))
#define MAXN 600
#define MAXM 3000
#define INF 0x3f3f3f3f

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

int t, N, S, E, num, g[MAXN * 4];
arrayN fir, d, vis, dS, dE, preS, preE;
arrayM nxt, e, c;

void link(int u, int v, int w)
{
	e[++num] = v;
	nxt[num] = fir[u];
	c[num] = w;
	fir[u] = num;
}

int minLab(int u, int v)
{
	if (!u || !v) return u + v;
	return d[u] > d[v] ? v : u;
}

void change(int pos, int value)
{
	d[pos] = value;
	for (pos = (pos + t) >> 1; pos; pos >>= 1)
		g[pos] = minLab(g[pos << 1], g[pos << 1 ^ 1]);
}

void dij(int s, int* dist, int* pre)
{
	for (t = 1; t <= N + 2; t <<= 1);
	mem(vis);
	mem(g);
	memOO(d);
	REPP(i, 1, N) g[i + t] = i, dist[i] = d[0];
	change(s, 0);
	pre[s] = 0;
	for (;;)
	{
		int tmp = g[1];
		if (d[tmp] >= d[0]) break;
		dist[tmp] = d[tmp];
		change(tmp, d[0]);
		vis[tmp] = 1;
		for (int p = fir[tmp]; p; p = nxt[p])
			if (!vis[e[p]] && d[e[p]] > dist[tmp] + c[p])
			{
				pre[e[p]] = tmp;
				change(e[p], dist[tmp] + c[p]);
			}
	}
}

void printPath(int x, int kind)
{
	if (!x) return ;
	printPath(preS[x], 1);
	printf("%d", x);
	if (kind) printf(" ");
}

int main()
{
	freopen("in.txt", "r", stdin);
	int cnt = 0;
	for (; scanf("%d%d%d", &N, &S, &E) != EOF; )
	{
		int m;
		if (cnt) printf("\n");
		++cnt;
		scanf("%d", &m);
		num = 0;
		mem(fir);
		REP(i, m)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			link(u, v, w);
			link(v, u, w);
		}
		dij(S, dS, preS);
		dij(E, dE, preE);
		/*REPP(i, 1, N) 
			printf("%d%c", dS[i], " \n"[i == N]);
		REPP(i, 1, N) 
		printf("%d%c", dS[i], " \n"[i == N]);*/
		int k;
		scanf("%d", &k);
		int ans[4];
		mem(ans);
		ans[3] = dE[S];
		REP(i, k)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			if (dS[u] + dE[v] + w < ans[3]) //S-->u--w-->v-->E
			{
				ans[3] = dS[u] + dE[v] + w;
				ans[0] = 1;
				ans[1] = u;
				ans[2] = v;
			}
			if (dS[v] + dE[u] + w < ans[3]) //S-->v--w-->u-->E
			{
				ans[3] = dS[v] + dE[u] + w;
				ans[0] = 1;
				ans[1] = v;
				ans[2] = u;
			}
		}
		if (ans[0])
		{
			printPath(ans[1], 0);
			if (ans[1] != E) printf(" ");
			for (int tmp = ans[2]; tmp; tmp = preE[tmp])
				printf("%d%c", tmp, " \n"[tmp == E]);
			printf("%d\n", ans[1]);
		} else 
		{
			printPath(E, 0);
			printf("\n");
			printf("Ticket Not Used\n");
		}
		printf("%d\n", ans[3]);
	}
	return 0;
}
