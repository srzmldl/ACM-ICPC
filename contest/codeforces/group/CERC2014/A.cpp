#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 2123
#define MAXM 1123456
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;

int num, f[MAXN][12], sonNum[MAXN], dep[MAXN];
int n, m, son[MAXN][12], ancestor[MAXN][MAXN];
int firAs[MAXN], fir[MAXN], e[MAXN], nxt[MAXN];
int eAs[MAXM], nxtAs[MAXM], dp[MAXN][MAXN];

struct edge
{
	int u, v;
	int lca;
	int chSta, oku, okv;
	void findChild()
		{
			chSta = 0;
			oku = 0, okv = 0;
			REP(i, sonNum[lca])
				if (ancestor[son[lca][i]][u] || ancestor[son[lca][i]][v])
				{
					chSta |= (1 << i);
					if (ancestor[son[lca][i]][u])
						oku = 1;
					if (ancestor[son[lca][i]][v])
						okv = 1;
				}
		}
} ed[MAXM];

void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num;
}

void prepareForLCA()
{
	REPP(i, 1, 10)
		REPP(j, 1, n)
		f[j][i] = f[f[j][i - 1]][i - 1];
}

void dfsOne(int x, int fa, int depth)
{
	dep[x] = depth;
	f[x][0] = fa;
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa)
		{
			son[x][sonNum[x]++] = e[p];
			dfsOne(e[p], x, depth + 1);
		}
}

void getAncestor(int ances, int x)
{
	ancestor[ances][x] = 1;
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != f[x][0])
			getAncestor(ances, e[p]);
}

void linkAsk(int u, int v)
{
	eAs[++num] = v, nxtAs[num] = firAs[u];
	firAs[u] = num;
}

void maxRep(int &u, int v)
{
	if (v > u) u = v;
}

int bst[1123], upSum[MAXN], trans[110];


void dfsupSum(int x, int ances, int lab)
{
	if (x == ances) 
		upSum[x] = dp[x][(1 << sonNum[x]) - 1];
	else 
	{
		int fa = f[x][0];
		upSum[x] = upSum[fa] - dp[fa][(1 << sonNum[fa]) - 1] + dp[fa][((1 << sonNum[fa]) - 1) ^ (1 << lab)] + dp[x][(1 << sonNum[x]) - 1];
	}
	REP(i, sonNum[x])
		dfsupSum(son[x][i], ances, i);
}

void dfsDP(int x)
{
	if (sonNum[x] == 0) return ;
	REP(p, sonNum[x])
		dfsDP(son[x][p]);

	MST(upSum, 0);
	REP(i, sonNum[x])
		dfsupSum(son[x][i], son[x][i], i);

	MST(bst, 0);
	for (int p = firAs[x]; p; p = nxtAs[p])
	{
		int lab = eAs[p];
		int tmp = 1;
		int u = ed[lab].u;
		int v = ed[lab].v;
		int sta = ed[lab].chSta;
		if (ed[lab].oku) tmp += upSum[u];
		if (ed[lab].okv) tmp += upSum[v];
		maxRep(bst[sta], tmp);
	}

	int tot = 0;
	REP(i, (1 << sonNum[x]))
		if (bst[i]) trans[tot++] = i;
	
	dp[x][0] = 0;
	REP(i, (1 << sonNum[x]))
	{
		REP(j, tot)
		if (!(i & trans[j]))
			maxRep(dp[x][i | trans[j]], dp[x][i] + bst[trans[j]]);
		REP(j, sonNum[x])
			if (!(i & (1 << j)))
				maxRep(dp[x][i | (1 << j)], dp[x][i] + dp[son[x][j]][(1 << sonNum[son[x][j]]) - 1]);
				
	}
}

int getLCA(int u, int v)
{
	if (dep[u] < dep[v]) swap(u, v);
	int tmp = dep[u] - dep[v];
	for (int i = 10; i >= 0; --i)
		if (tmp >= (1 << i))
		{
			u = f[u][i];
			tmp -= (1 << i);
		}
	for (int i = 10; i >= 0; --i)
		if (f[u][i] != f[v][i])
		{
			u = f[u][i];
			v = f[v][i];
		}
	if (u != v) return f[u][0];
	else return u;
}

int main()
{
	freopen("all.in", "r", stdin);
	int T;
	for (scanf("%d", &T); T; --T)
	{
		scanf("%d", &n);
		MST(fir, 0);
		MST(sonNum, 0);
		MST(ancestor, 0);
		num = 0;
		REP(i, n - 1)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			link(u, v);
			link(v, u);
		}
		dfsOne(1, 0, 1);
		REPP(i, 1, n)
			getAncestor(i, i);
		prepareForLCA();

		scanf("%d", &m);	
		num = 0;
		MST(firAs, 0);
		REP(i, m)
		{
			scanf("%d%d", &ed[i].u, &ed[i].v);
			ed[i].lca = getLCA(ed[i].u, ed[i].v);
			ed[i].findChild();
			linkAsk(ed[i].lca, i);
		}
		MST(dp, 0);
		dfsDP(1);
		printf("%d\n", dp[1][(1 << sonNum[1]) - 1]);
	}
	return 0;
}

