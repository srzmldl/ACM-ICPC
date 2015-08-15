#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 2222

using namespace std;
typedef int arrayN[MAXN];

arrayN fir, f, e, nxt;
double cost[MAXN][MAXN], w[MAXN];
int n, num;
vector<int> vec;
struct node 
{
	int x, y, p;
}a[MAXN];

struct edge
{
	int u, v;
	double w;
	edge() {};
	edge(int u1, int v1, double w1)
		{
			u = u1, v = v1, w = w1;
		}
} ed[MAXN * MAXN];

int getfa(int x)
{
	return f[x] == x ? x : (f[x] = getfa(f[x]));
}

void link(int u, int v, double co)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, w[num] = co;
}

int sqr(int x)
{
	return x * x;
}

double dist(node A, node B)
{
	return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

int com(edge A, edge B)
{
	return A.w < B.w;
}

void dfs(int x, int fa, double lastW)
{
	REP(i, vec.size())
		cost[vec[i]][x] = cost[x][vec[i]] = max(cost[fa][vec[i]], lastW);
	vec.push_back(x);
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa)
			dfs(e[p], x, w[p]);
}

int main()
{
	freopen("la5713.in", "r", stdin);
	int task;
	for (scanf("%d", &task); task; --task)
	{
		scanf("%d", &n);
		num = 0;
		MST(fir, 0);
		REP(i, n)
			scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].p);
		int tot = 0;
		REP(i, n)
			REPP(j, i + 1, n - 1)
			ed[++tot] = edge(i, j, dist(a[i], a[j]));
		sort(ed + 1, ed + tot + 1, com);
		REP(i, n) f[i] = i, cost[i][i] = 0;
		double allLen = 0;
		REPP(i, 1, tot)
		{
			int fu = getfa(ed[i].u);
			int fv = getfa(ed[i].v);
			if (fu != fv)
			{
				link(ed[i].u, ed[i].v, ed[i].w);
				link(ed[i].v, ed[i].u, ed[i].w);
				f[fu] = fv;
				allLen += ed[i].w;
			}
		}
		vec.clear();
		dfs(0, 0, 0);
		double ans = 0;
		REP(i, n)
			REPP(j, i + 1, n - 1)
			ans = max(ans, 1.0 * (a[i].p + a[j].p) / (allLen  -  cost[i][j]));
		printf("%.2f\n", ans);
			
	}
	return 0;
}
