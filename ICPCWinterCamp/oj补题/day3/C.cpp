#include <bits/stdc++.h>
#define MST(a, b) memset(a, (b), sizeof(a));

#define MAXN 212345
#define MAXM 212345 * 3

using namespace std;
typedef int arrayN[MAXN];
typedef int arrayM[MAXM];
const int INF = ~0U>>1;

int n, m, k, num;
arrayN pre, fir, vis, inS, d, bobo;
arrayM e, nxt, c;

struct node
{
	int d, lab;
	node (int d = 0, int lab = 0) : d(d), lab(lab) {};
}g[MAXN];
	
void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	c[num] = w, fir[u] = num;
}

void update(int su, int tv, int dist)
{
	if (dist < g[su].d || (dist == g[su].d && tv < g[su].lab))
		g[su] = node(dist, tv);
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 0; i < m; ++i)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		link(u, v, w);
		link(v, u, w);
	}
	MST(inS, 0);
	MST(vis, 0);
	MST(d, 0);
	MST(pre, 0);
	deque<int> q;
	for (int i = 1; i <= k; ++i)
	{
		int x;
		scanf("%d", &bobo[i]);
		x = bobo[i];
		q.push_back(x);
		pre[x] = x;
		vis[x] = 1;
		inS[x] = 1;
	}
	for (; !q.empty(); )
	{
		int x = q.back();
		q.pop_back();
		inS[x] = 0;
		for (int p = fir[x]; p; p = nxt[p])
			if (!vis[e[p]] || d[e[p]] > d[x] + c[p] || (d[e[p]] == d[x] + c[p] && pre[e[p]] > pre[x]))
			{
				d[e[p]] = d[x] + c[p];
				pre[e[p]] = pre[x];
				vis[e[p]] = 1;
				if (!inS[e[p]])
				{
					if (q.empty() || d[e[p]] < d[q.back()]) q.push_back(e[p]);
					else q.push_front(e[p]);
					inS[e[p]] = 1;
				}
			}
	}
	for (int i = 1; i <= n; ++i)
		g[i].d = INF;
	for (int i = 1; i <= n; ++i)
		for (int p = fir[i]; p; p = nxt[p])
			if (pre[i] != pre[e[p]])
			{
				int dist = d[i] + d[e[p]] + c[p];
				update(pre[i], pre[e[p]], dist);
				update(pre[e[p]], pre[i], dist);
			}
	for (int i = 1; i <= k; ++i)
		printf("%d\n", g[bobo[i]].lab);
	return 0;
}
