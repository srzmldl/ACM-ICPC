#include <bits/stdc++.h>

#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 162345
#define MST(a, b) memset((a), (b), sizeof(a))
#define INF 0x3f3f3f3f

using namespace std;

struct node
{
	int v, c;
} g[MAXN];

int com(node A, node B)
{
	return A.v < B.v;
}

int dp[MAXN][15];

int main()
{
//	freopen("in.txt", "r", stdin);
	int T;
	for (scanf("%d", &T); T; --T)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		REP(i, n)
			scanf("%d%d", &g[i].v, &g[i].c);
		sort(g, g + n, com);
		MST(dp, 0);
		dp[n][0] = INF; 
		for (int i = n - 1; i >= 0; --i)
			REP(j, k + 2)
				dp[i][j] = max(dp[i + 1][j], min(dp[i + 1][j - 1] - g[i].c, g[i].v - g[i].c));
		printf("%d\n", dp[0][k + 1]);
	}
	return 0;
}

