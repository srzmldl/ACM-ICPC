#include<bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 1111
#define MAXM 1111111

using namespace std;

int a[MAXN], g[MAXN][MAXN];

int random(int x)
{
	return abs(rand()) % x;
}

void makeYes(int n)
{
	MST(g, 0);
	REP(i, n)
		REPP(j, i + 1, n - 1)
		g[a[i]][a[j]] = 1;
	int d[5];
	REP(i, 3)
	{
		int u;
		int flag = 1;
		for (;flag;)
		{
			flag = 0;
			u = random(n);
			REPP(j, 0, i - 1)
				if (u == d[j])
					flag = 1;
		}
		d[i] = u;
	}
	REP(i, 3)
	{
		int u = d[i], v = d[(i + 1) % 3];
		if (!g[u][v])
		{
			g[u][v] = 1;
			g[v][u] = 0;
		}
	}
	
	REP(i, n)
	{
		REP(j, n)
			printf("%d", g[i][j]);
		printf("\n");
	}
}

void makeNo(int n)
{
	MST(g, 0);
	REP(i, n)
		REPP(j, i + 1, n - 1)
		g[a[i]][a[j]] = 1;
	REP(i, n)
	{
		REP(j, n)
			printf("%d", g[i][j]);
		printf("\n");
	}
}

int main()
{
	srand(time(0) % clock());
	freopen("threeCircle.in", "w", stdout);
	int task = 30;
	int n = 1000;
	REP(ca, task)
	{
		printf("%d\n", n);
		int ans = abs(rand()) & 1;
		REP(i, n)
			a[i] = i;
		REP(i, n)
			swap(a[i], a[random(i + 1)]);
		if (ans) makeYes(n);
		else makeNo(n);
	}
	printf("0\n");
	return 0;
}
