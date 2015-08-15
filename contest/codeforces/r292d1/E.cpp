#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 11234

using namespace std;

typedef int arrayN[MAXN];

int n = 4;
int tot = 0;
int a[100][100], vis[100];

void dfs(int lab)
{
	if (lab == n)
	{
		++tot;
		REP(i, n) a[tot][i] = a[tot - 1][i];
		return ;
	}
	REP(i, n)
		if (!vis[i])
		{
			vis[i] = 1;
			a[tot][lab] = i;
			dfs(lab + 1);
			vis[i] = 0;
		}
}

void prt1()
{
	int njc = 24;
	REP(i, njc)
		REP(j, njc)
	{
		int k = (i + j) % njc;
		printf("%d = %d + %d\n", k, i, j);
		printf("%d: ", i);
		REP(h, n)
			printf(" %d", a[i][h]);
		printf("\n");
		printf("%d: ", j);
		REP(h, n)
			printf(" %d", a[j][h]);
		printf("\n");
		printf("%d: ", k);
		REP(h, n)
			printf(" %d", a[k][h]);
		printf("\n");
		printf("\n");
	}
}

void prt2()
{
	REP(i, tot)
	{
		printf("%d :", i);
		REP(j, n) 
			printf(" %d", a[i][j]);
		printf("\n");
	}
}

int main()
{
	freopen("pl.out", "w", stdout);
	MST(vis, 0);
	dfs(0);
	prt1();
	//prt2();
	return 0;
}
