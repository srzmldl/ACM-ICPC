#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 111
#define MAXM 2123
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];

int clk, num, vis[1 << 16], bits[1 << 16];
arrayN fir, sg, K;
arrayM nxt, e;
vector<int> od[MAXN];

void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, od[u].push_back(v);
}

void dfsSG(int x)
{
	for (int p = fir[x]; p; p = nxt[p])
		if (sg[e[p]] == -1) dfsSG(e[p]);
	sg[x] = 0;
	if (!fir[x]) return ;
	++clk;
	REP(i, 1 << od[x].size())
		if (bits[i] <= K[x] && ((bits[i] & 1) == (K[x] & 1)))
		{
			int tmp = 0;
			REP(j, od[x].size())
				if (i & (1 << j))
					tmp ^= sg[od[x][j]];
			vis[tmp] = clk;
		}
	int i;
	for (i = 0; ; ++i)
		if (vis[i] != clk)
		{
			sg[x] = i;
			break;
		}
}
void calcSG(int n)
{
	MST(sg, -1);
	REP(i, 1 << 16)
	{
		bits[i] = 0;
		for (int x = i; x; x >>= 1)
			bits[i] += x & 1;
	}
	REP(i, n)
		if (sg[i] < 0)
			dfsSG(i);
}

int main()
{
	freopen("la4411.in", "r", stdin);
	int task;
	scanf("%d", &task);
	for (int T = 1; T <= task; ++T)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		MST(fir, 0);
		num = 0;
		REP(i, n) od[i].clear();
		REP(i, m)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			link(u, v);
		}
		REP(i, n)
			scanf("%d", &K[i]);
		calcSG(n);
		printf("Game#%d:\n", T);
		int q;
		scanf("%d", &q);
		REPP(i, 1, q)
		{
			int ans = 0;
			REP(j, n)
			{
				int v;
				scanf("%d", &v);
				if (v & 1) ans ^= sg[j];
			}
			printf("Round#%d: ", i);
			printf(ans ? "WINNING\n" : "LOSING\n");
		}
		printf("\n");
	}
	return 0;
}
