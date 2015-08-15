#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 55

using namespace std;


int f[MAXN][MAXN], c[MAXN][MAXN][MAXN][MAXN];
int n;


int main() {
	ios :: sync_with_stdio(0);
	freopen("D.in", "r", stdin);
	scanf("%d", &n);
	int limx = 50, limy = 50;
	REPP(i, 1, n)
	{
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		c[x1][y1][x2][y2] = 1;
	}
	REPP(i, 0, limx)
		REPP(j, 0, limy)
	{
		if (i > 0) f[i][j] = max(f[i][j], f[i - 1][j] + c[i - 1][j][i][j]);
		if (j > 0) f[i][j] = max(f[i][j], f[i][j - 1] + c[i][j - 1][i][j]);
	}
	printf("%d\n", f[limx][limy]);
	return 0;
}
