#include <vector>
#include <deque>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>

#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MAXC 200
#define MAXS 500000
#define INF 0x3f3f3f3f

using namespace std;

int gx[4] = {1, 0, -1, 0};
int gy[4] = {0, 1, 0, -1};
int op[4] = {2, 3, 0, 1};

int d[MAXS], vis[MAXS];
struct node
{
	int x, y;
	node() {};
	node(int x1, int y1)
		{x = x1, y = y1;};
	bool operator == (node B)
		{
			return (x == B.x) && (y == B.y);
		} 
} s, t;

struct rec
{
	node dl, ur;
} g[60];

vector<int> vx, vy;
deque<int> deq; 

int n, have[MAXC][MAXC][4], sn, tn;

int trans3To1(int x, int y, int p)
{
	return x * vy.size() * 4 + y * 4 + p;
}

void trans1To3(int state, int &x, int &y, int &p)
{
	p = state % 4;
	state /= 4;
	y = state % vy.size();
	state /= vy.size();
	x = state;
}

void getNewCoor(node &u)
{
	REP(i, vx.size())
		if (u.x == vx[i])
		{
			u.x = i;
			break;
		}
	REP(i, vy.size())
		if (u.y == vy[i])
		{
			u.y = i;
			break;
		}
}

void getFourDirRec()
{
	mem(have);
	REP(i, n)
	{
		REPP(x, g[i].dl.x + 1, g[i].ur.x - 1)
			REPP(y, g[i].dl.y + 1, g[i].ur.y - 1)
			REP(k, 4) have[x][y][k] = 1;
		REPP(x, g[i].dl.x + 1, g[i].ur.x - 1)
		{
			REPP(k, 0, 1) have[x][g[i].dl.y][k] = 1;
			REPP(k, 2, 3) have[x][g[i].ur.y][k] = 1;
		}
		REPP(y, g[i].dl.y + 1, g[i].ur.y - 1)
		{
			REPP(k, 1, 2) have[g[i].ur.x][y][k] = 1;
			have[g[i].dl.x][y][0] = 1;
			have[g[i].dl.x][y][3] = 1;
		}
		have[g[i].dl.x][g[i].dl.y][0] = 1;
		have[g[i].dl.x][g[i].ur.y][3] = 1;
		have[g[i].ur.x][g[i].dl.y][1] = 1;
		have[g[i].ur.x][g[i].ur.y][2] = 1;
	}
}

int checkPath(int sx, int sy, int p)
{
	int nx = sx + gx[p];
	int ny = sy + gy[p];
	if (nx < 0 || ny < 0 || nx >= vx.size() || ny >= vy.size())
		return 0;
	int lb = p, rb = p - 1;
	if (rb < 0) rb = 3;
	return have[sx][sy][lb] + have[sx][sy][rb] <= 1;
}

void origin()
{
	deq.clear();
	mem(vis);
	memset(d, 50, sizeof(d));
	REP(p, 4)
		if (checkPath(s.x, s.y, p))
		{
			int nx = s.x + gx[p];
			int ny = s.y + gy[p];
			int nsta = trans3To1(nx, ny, p);
			d[nsta] = 0;
			vis[nsta] = 1;
			deq.push_back(nsta);
		}
}

int getCost(int sx, int sy, int sp, int tx, int ty, int tp)
{
	if (!checkPath(sx, sy, tp)) return -1;
	if (sp != tp)
	{
		int rp = sp - 1;
		int lp = sp + 1;
		int lb = tp;
		int rb = tp - 1;
		if (rb < 0) rb = 3;
		if (rp < 0) rp = 3;
		if (lp > 3) lp = 0;
		if (lp == tp)
		{
			if (have[sx][sy][lb] && have[sx][sy][op[lb]])
				return -1;
		}
		else 
		{
			if (have[sx][sy][rb] && have[sx][sy][op[rb]])
				return -1;
		}
		return 1;
	}
	REP(k, 2)
		if (have[sx][sy][k] && have[sx][sy][k + 2])
			return -1;
	return 0;
}

int main()
{
	freopen("walk.in", "r", stdin);
	for(;;)
	{
		int x1, y1, x2, y2;
		vx.clear(), vy.clear();
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 + y1 + x2 + y2 == 0) break;
		vx.push_back(x1), vy.push_back(y1);
		vx.push_back(x2), vy.push_back(y2);
		s = node(x1, y1);
		t = node(x2, y2);
		scanf("%d", &n);
		REP(i, n)
		{
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			g[i].dl = node(x1, y1);
			g[i].ur = node(x2, y2);
			vx.push_back(x1), vy.push_back(y1);
			vx.push_back(x2), vy.push_back(y2);
		}

		sort(vx.begin(), vx.end());
		sort(vy.begin(), vy.end());
		vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
		vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
		getNewCoor(s);
		getNewCoor(t);
		REP(i, n) 
		{
			getNewCoor(g[i].dl);
			getNewCoor(g[i].ur);
		}
		//================
		getFourDirRec();
		if (s == t)
		{
			printf("0\n");
			continue;
		}

		origin();
		
		int ans = INF;
		for(;!deq.empty();)
		{
			int sx, sy, sp;
			trans1To3(deq.front(), sx, sy, sp);
			int osta = deq.front();
			deq.pop_front();
			if (node(sx, sy) == t) 
			{
				ans = min(ans, d[osta]);
			}
			vis[osta] = 0;
			REP(p, 4)
			{
				int tx = sx + gx[p];
				int ty = sy + gy[p];
				int cost = getCost(sx, sy, sp, tx, ty, p);
				if (cost < 0) continue;
				int nsta = trans3To1(tx, ty, p);
				if (cost + d[osta] < d[nsta])
				{
					d[nsta] = cost + d[osta];
					if (!vis[nsta])
					{
						vis[nsta] = 1;
						deq.push_back(nsta);
					}
				}
			}
		}
		printf("%d\n", ans == INF ? -1 : ans);

	}
	return 0;
}
