#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset(a, (b), sizeof(a))
#define MAXN 112

using namespace std;
int task, m, n;
int leg[MAXN][MAXN][4];
int poi[1000];
int d[MAXN * MAXN * 5], vis[MAXN * MAXN * 5];
deque<int> sta;
int gx[4] = {0, 0, 1, -1};
int gy[4] = {1, -1, 0, 0};
char st[MAXN][MAXN];

int check(int x, int y, int k)
{
	REPP(i, y + 1, n - 1)
		if (poi[st[x][i]] >= 0 && ((poi[st[x][i]] + k) % 4 == 3))
			return 0;
	REPP(i, 0, y - 1)
		if (poi[st[x][i]] >= 0 && ((poi[st[x][i]] + k) % 4 == 1))
			return 0;
	REPP(i, x + 1, m - 1)
		if (poi[st[i][y]] >= 0 && ((poi[st[i][y]] + k) % 4 == 0))
			return 0;
	REPP(i, 0, x - 1)
		if (poi[st[i][y]] >= 0 && ((poi[st[i][y]] + k) % 4 == 2))
			return 0;
	return 1;
}

int calc(int x, int y, int k)
{
	return x * 4 * n + y * 4 + k;
}

void recover(int su, int &x, int &y, int &k)
{
	k = su % 4;
	su /= 4;
	y = su % n;
	su /= n;
	x = su;
}

int legal(int x, int y, int k)
{
	if (x < 0 || y < 0 || x >= m || y >= n) return 0;
	return (leg[x][y][k] == 0);
}

int main()
{
	freopen("in3.txt", "r", stdin);
	freopen("out3.txt", "w", stdout);
	scanf("%d", &task);
	MST(poi, -1);
	poi['^'] = 0;
	poi['>'] = 1;
	poi['v'] = 2;
	poi['<'] = 3;
	REPP(t, 1, task)
	{
		printf("Case #%d: ", t);
		scanf("%d%d\n", &m, &n);
		REP(i, m)
			scanf("%s", st[i]);
		MST(leg, 0);
		sta.clear();
		MST(vis, 0);
		int sx, sy, tx, ty;
		REP(i, m)
			REP(j, n)
		{
			if (st[i][j] == 'S' || st[i][j] == 'G' || st[i][j] == '.')
				REP(k, 4)
					leg[i][j][k] = check(i, j, k);
			if (st[i][j] == 'S')
				sx = i, sy = j;
			if (st[i][j] == 'G')
				tx = i, ty = j;
		}
		MST(d, 0x3f);
		
		int tmp = calc(sx, sy, 0);
		d[tmp] = 0;
		sta.push_back(tmp);
		vis[tmp] = 1;

		int flag = 1;
		for (;!sta.empty();)
		{
			int tmp = sta.front();
			sta.pop_front();
			int lx, ly, lk;
			recover(tmp, lx, ly, lk);
			if (lx == tx && ly == ty)
			{
				printf("%d\n", d[tmp]);
				flag = 0;
				break;
			}
			REP(p, 4)
			{
				int rx = lx + gx[p];
				int ry = ly + gy[p];
				int rk = (lk + 1) % 4;
				if (legal(rx, ry, rk))
				{
					int rt = calc(rx, ry, rk);
					if (vis[rt]) continue;
					d[rt] = d[tmp] + 1;
					sta.push_back(rt);
					vis[rt] = 1;
				}
			}
		}
		if (flag) printf("impossible\n");
	}
	return 0;
}
