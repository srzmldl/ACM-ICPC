#include <bits/stdc++.h>
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define memInf(a) memset(a, 60, sizeof(a))
#define mem(a) memset(a, 0, sizeof(a))
#define MAXN 1111111
#define INF 0x3f3f3f3f

using namespace std;

int R, C, r1, c1, r2, c2, d[MAXN], inD[MAXN];
deque<int> deq;
int w[111][111][6];
int gx[4] = {0, 1, -1, 0};
int gy[4] = {1, 0, 0, -1};

int calc(int x, int y, int p, int mul)
{
	return x * (C + 1) * 4 * 2 + y * 4 * 2 + p * 2 + mul;
}

int legal(int x, int y)
{
	return (x >= 1) && (x <= R) && (y >= 1) && (y <= C);
}

void recovery(int t, int &x, int &y, int &p, int &mul)
{
	x = t / ((C + 1) * 8);
	t %= (C + 1) * 8;
	y = t / 8;
	t %= 8;
	p = t / 2;
	t %= 2;
	mul = t;
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (int task = 1; ; ++task)
	{
		scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2);
		if (R + C == 0) break;
		printf("Case %d: ", task);
		mem(w);
		REPP(row, 1, R)
		{
			REPP(i, 1, C - 1)
			{
				int cost;
				scanf("%d", &cost);
				w[row][i][0] = w[row][i + 1][3] = cost;
			}
			if (row < R)
				REPP(i, 1, C)
				{
					int cost;
					scanf("%d", &cost);
					w[row][i][1] = w[row + 1][i][2] = cost;
				}
		}
		deq.clear();
		memInf(d);
		mem(inD);
		REP(k, 4)
			if (w[r1][c1][k])
			{
				int nx = r1 + gx[k];
				int ny = c1 + gy[k];
				int tmp = calc(nx, ny, k, 1);
				d[tmp] = w[r1][c1][k] * 2;
				inD[tmp] = 1;
				deq.push_back(tmp);
			}
		for (;!deq.empty();)
		{
			int j = deq.back(), x, y, k, mul;
			deq.pop_back();
			inD[j] = 0;
			recovery(j, x, y, k, mul);
			REP(p, 4)
			{
				if (!w[x][y][p]) continue;
				int nx = x + gx[p];
				int ny = y + gy[p];
				if (!legal(nx, ny)) continue;
				int nk = p;
				int nmul = (p != k);
				if (d[j] == 0) nmul = 1;
				//if (nx == r2 && ny == c2) nmul = 1;
				int cost = w[x][y][p] * (1 + nmul);
				if (nk != k) cost += (mul ? 0 : w[x][y][3 - k]);;
				int nstate = calc(nx, ny, nk, nmul);
				if (d[nstate] > d[j] + cost)
				{
					d[nstate] = d[j] + cost;
					if (!inD[nstate])
					{
						inD[nstate] = 1;
						if (deq.empty() || d[deq.back()] >= d[nstate]) deq.push_back(nstate);
						else deq.push_front(nstate);
					}
				}
			}
		}
		int ans = d[0];
		REP(p, 4)
			REP(mul, 2)
		{
			int tmp = calc(r2, c2, p, mul);
			ans = min(ans, d[tmp] + (mul ? 0 : w[r2][c2][3 - p]));
		}
		if (ans < d[0])
			printf("%d\n", ans);
		else printf("Impossible\n");
	}
	return 0;
}
