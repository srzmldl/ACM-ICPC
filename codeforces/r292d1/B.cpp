#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 4123

using namespace std;

typedef int arrayNN[MAXN * MAXN];

char st[MAXN][MAXN];
arrayNN f, vis, tot;
int n, m;
int gx[4] = {1, -1, 0, 0};
int gy[4] = {0, 0, 1, -1};

int check(int nx, int ny)
{
	return (nx >= 0 && ny >= 0 && nx < n && ny < m);
}

int getfa(int x)
{
	return f[x] == x ? x : (f[x] = getfa(f[x]));
}

int calc(int x, int y)
{
	return x * m + y;
}

void recover(int tmp, int &x, int &y)
{
	y = tmp % m;
	x = tmp / m;
}


int checkUnique()
{
	vector<int> sta;
//	REP(i, n)
//		REP(j, m)
	//	f[calc(i, j)] = calc(i, j);
//	MST(vis, 0);
	REP(i, n)
		REP(j, m)
		if (st[i][j] == '.')
		{
			int pu = calc(i, j);
			tot[pu] = 0;
			//	vis[pu] = 1;
			REP(p, 4)
			{
				int nx = i + gx[p];
				int ny = j + gy[p];
				if (check(nx, ny) && st[nx][ny] == '.')
				{
					++tot[pu];
					//	int pv = calc(nx, ny);
					//	int fu = getfa(pu);
					//	int fv = getfa(pv);
					//	if (fu == fv && !vis[pv]) return 0;
					//	else f[fv] = fu;
				}
			}
			if (tot[pu] == 1) sta.push_back(pu);
		}

	MST(vis, 0);
	
	for (; !sta.empty();)
	{
		int tmp = sta.back();
		sta.pop_back();
		if (vis[tmp]) continue;
		int x, y;
		recover(tmp, x, y);
		REP(p, 4)
		{
			int nx = x + gx[p], ny = y + gy[p];
			int pv = calc(nx, ny);
			if (check(nx, ny) && st[nx][ny] == '.' && !vis[pv])
			{
				if (p == 0)
				{
					st[x][y] = '^';
					st[nx][ny] = 'v';
				} else if (p == 1)
				{
					st[x][y] = 'v';
					st[nx][ny] = '^';
				} else if (p == 2)
				{
					st[x][y] = '<';
					st[nx][ny] = '>';
				} else 
				{
					st[x][y] = '>';
					st[nx][ny] = '<';
				}
				vis[tmp] = 1;
				vis[pv] = 1;
				REP(p1, 4)
				{
					int nnx = nx + gx[p1];
					int nny = ny + gy[p1];
					int npv = calc(nnx, nny);
					if (check(nnx, nny) && st[nnx][nny] == '.')
					tot[npv]--;
					if (tot[npv] == 1) sta.push_back(npv);
				}
			}
		}
	}

	REP(i, n)
		REP(j, m)
		if (st[i][j] == '.') return 0;
	
	REP(i, n)
	{
		printf("%s\n", st[i]);
	}
	return 1;
}

int main()
{
//	freopen("B.in", "r", stdin);
	scanf("%d%d", &n, &m);
	REP(i, n)
		scanf("%s", st[i]);
	if (!checkUnique())
		printf("Not unique\n");
	return 0;
}
