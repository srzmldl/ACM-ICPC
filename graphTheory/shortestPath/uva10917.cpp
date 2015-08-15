#include <bits/stdc++.h>
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MAXN 1100
#define MAXM 2200000
#define INF 0x3f3f3f3f

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

int n, m, g[MAXN * 4], t, num;
arrayM e, nxt, c;
arrayN fir, vis, d, ans, inD;
vector<int> slack;

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

int minLab(int u, int v)
{
	if (vis[u] || !u) return v;
	if (vis[v] || !v) return u;
	return d[u] < d[v] ? u : v;
}

void change(int pos, int value)
{
	d[pos] = value;
	for (pos = (pos + t) >> 1; pos; pos >>= 1)
		g[pos] = minLab(g[pos << 1], g[pos << 1 ^ 1]);
}

void dij(int s)
{
	mem(vis);
	mem(g);
	d[0] =INF;
	for (t = 1; t <= n + 2; t <<= 1);
	REPP(i, 1, n) g[i + t] = i, d[i] = INF;
	d[s] = 0;
	change(s, 0);
	for(;;)
	{
		int tmp = g[1];
		if (vis[tmp]) break;
		vis[tmp] = 1;
		change(tmp, d[tmp]);
		for (int p = fir[tmp]; p; p = nxt[p])
			if (!vis[e[p]] && d[e[p]] > d[tmp] + c[p])
				change(e[p], d[tmp] + c[p]);
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (;;)
	{
		scanf("%d", &n);
		if (!n) break;
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
		dij(2);
		mem(ans);
		ans[1] = 1;
		{
			mem(inD);
			REPP(i, 1, n)
				for (int p = fir[i]; p; p = nxt[p])
					if (d[e[p]] < d[i])
						inD[e[p]]++;
			slack.clear();
			REPP(i, 1, n)
				if (!inD[i]) slack.push_back(i);
			for (; !slack.empty();)
			{
				int tmp = slack.back();
				slack.pop_back();
				for (int p = fir[tmp]; p; p = nxt[p])
					if (d[e[p]] < d[tmp])
					{ 
						ans[e[p]] += ans[tmp];
						--inD[e[p]];
						if (!inD[e[p]])
							slack.push_back(e[p]);
					}
			}
			printf("%d\n", ans[2]);
		}
	}
	return 0;
}
