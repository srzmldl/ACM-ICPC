#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 50
#define MAXM 300
#define MO 1000000007

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, col, pos;
arrayM nxt, e;
int num, n, m, tot[3];
int c[MAXM][2][2], w[2][2], g[2][MAXN];

void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num;
	REP(i, 2)
		REP(j, 2)
		c[num][i][j] = w[i][j];
}

void dye(int x, int bw)
{
	g[bw][++tot[bw]] = x;
	col[x] = bw;
	for (int p = fir[x]; p; p = nxt[p])
		if (col[e[p]] == -1)
			dye(e[p], 1 - bw);
}

int main() {
//	ios :: sync_with_stdio(0);
	freopen("B.in", "r", stdin);
	scanf("%d%d", &n, &m);
	if (m == 0)
	{
		printf("0\n");
		return 0;
	}
	num = 0;
	
	REPP(i, 1, m)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		REP(i, 2)
			REP(j, 2)
			scanf("%d", &w[i][j]);
		link(u, v);
		swap(w[0][1], w[1][0]);
		link(v, u);
	}
	MST(col, -1);
	REPP(i, 1, n)
		if (col[i] == -1)
			dye(i, 0);
	int L = 0, R = 1;
	if (tot[L] > tot[R]) swap(L, R);
	int ans = 0;
	REPP(i, 1, tot[L]) pos[g[L][i]] = i - 1;
	REP(i, (1 << tot[L]))
	{
		int tmp = 1;
		REPP(j, 1, tot[R])
		{
			int u = g[R][j];
			int t0 = 1, t1 = 1;
			for (int p = fir[u]; p; p = nxt[p])
			{
				int v = e[p];
				int bwL = ((1 << (pos[v])) & i) ? 1 : 0;
				t0 = (1LL * t0 * c[p][0][bwL]) % MO;
				t1 = (1LL * t1 * c[p][1][bwL]) % MO;
			}
			if (fir[u]) tmp = 1LL * tmp * ((t0 + t1) % MO) % MO;
		}
			
		ans = (ans + tmp) % MO;
	}

	REPP(i, 1, tot[R])
		if (fir[g[R][i]] == 0)
			ans = (ans * 2) % MO;
	printf("%d\n", ans);
	return 0;
}
