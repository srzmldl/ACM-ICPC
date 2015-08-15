#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 12
#define MAXK 20
#define STALIM 40000

using namespace std;
typedef int twoArray[MAXN][MAXN];

twoArray inS, belong;
int n, task, tot, dp[MAXN][MAXN][STALIM];
char a[MAXN][MAXN];
int gx[4] = {0, 0, 1, -1};
int gy[4] = {1, -1, 0, 0};
int INF;

struct point
{
	int x, y;
	point(int x = 0, int y = 0) :x(x), y(y) {};
}fxy[MAXK];

vector<point> stac;

int illegal(int x, int y)
{
	return !(x >= 0 && x < n && y >= 0 && y < n);
}

void dfs(int x, int y)
{
	belong[x][y] = tot;
	REP(p, 4)
	{
		int nx = x + gx[p], ny = y + gy[p];
		if (illegal(nx, ny)) continue;
		if ((a[nx][ny] == '@') && !belong[nx][ny]) dfs(nx, ny);
	}
}

void updateMin(int &u, int v)
{
	u = min(u, v);
}

int main()
{
	freopen("zoj3837.txt", "r", stdin);
	for(scanf("%d\n", &task); task; --task)
	{
		scanf("%d\n", &n);
		REP(i, n) scanf("%s", a[i]);
		int center = n / 2;
		a[center][center] = '@';
		MST(belong, 0);
		tot = 0;
		REP(i, n)
			REP(j, n)
			if (!belong[i][j] && a[i][j] == '@')
			{
				++tot;
				dfs(i, j);
			}
		int limSta = (1 << tot) - 1;
		MST(dp, 0x3f);
		INF = dp[0][0][0];
		REP(i, n)
			REP(j, n)
		{
			if (a[i][j] != 'X')
				dp[i][j][0] = (a[i][j] == '@' ? 0 : a[i][j] - '0');
			if (a[i][j] == '@')
				dp[i][j][1 << (belong[i][j] - 1)] = 0;
		}
		REPP(sta, 1, limSta)
		{
			MST(inS, 0);
			REP(i, n)
				REP(j, n)
				if (a[i][j] != 'X')
				{
					int cost = a[i][j] == '@' ? 0 : a[i][j] - '0';
					for (int sub = sta & (sta - 1); sub; sub = sta & (sub - 1))
						updateMin(dp[i][j][sta], dp[i][j][sub] + dp[i][j][sta - sub] - cost);
					if (dp[i][j][sta] < INF)
					{
						if (!inS[i][j]) stac.push_back(point(i, j));
						inS[i][j] = 1;
					}
				}
			for (; !stac.empty();)
			{
				point tmp = stac.back();
				stac.pop_back();
				int x = tmp.x, y = tmp.y;
				inS[x][y] = 0;
				REP(p, 4)
				{
					int nx = x + gx[p], ny = y + gy[p];
					if (illegal(nx, ny)) continue;
					if (a[nx][ny] == 'X') continue;
					int cost = (a[nx][ny] == '@' ? 0 : a[nx][ny] - '0');
					if (dp[x][y][sta] + cost < dp[nx][ny][sta])
					{
						dp[nx][ny][sta] = dp[x][y][sta] + cost;
						if (!inS[nx][ny])
						{
							inS[nx][ny] = 1;
							stac.push_back(point(nx, ny));
						}
					}
				}
			}
		}
		int ans = dp[center][center][limSta];
		if (ans == INF) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}
