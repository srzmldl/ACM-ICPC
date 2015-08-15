#include <bits/stdc++.h>

#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 312
#define MST(a, b) memset((a), (b), sizeof(a))
#define INF 0x3f3f3f3f

using namespace std;

struct node
{
	int a, b, d;
} g[MAXN];

int com(node A, node B)
{
	return A.a < B.a || (A.a == B.a && A.b < B.b);
}

int dp[MAXN][MAXN], R[MAXN], L[MAXN];

void minRep(int &u, int v)
{
	if (v < u) u = v;
}

void findLR(int n)
{
	REP(i, n)
	{
		R[i] = n;
		REPP(j, i + 1, n - 1)
			if (g[j].a > g[i].a)
			{
				R[i] = j;
				break;
			}
		L[i] = -1;
		for (int j = i - 1; j >= 0; --j)
			if (g[j].b < g[i].a)
			{
				L[i] = j;
				break;
			}
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int T;
	for (scanf("%d", &T); T; --T)
	{
		int n;
		scanf("%d", &n);
		REP(i, n)
			scanf("%d%d%d", &g[i].a, &g[i].b, &g[i].d);
		MST(dp, 0x3f);
		sort(g, g + n, com);
		findLR(n);
		REP(i, n)
			dp[i][1] = g[i].d;
		REPP(k, 2, n)
			REPP(i, 0, n - k)
			REPP(j, i, i + k - 1)
		{
			int l = L[j];
			int r = R[j];
			int tmp = g[j].d;
			if (r <= i + k - 1)
				tmp += dp[r][i + k - r];
			if (l >= i)
				tmp += dp[i][l - i + 1];
			minRep(dp[i][k], tmp);
		}
		printf("%d\n", dp[0][n]);
	}
	return 0;
}
