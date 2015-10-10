#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 512
#define INF 0x3f3f3f3f

using namespace std;

typedef int arrayN[MAXN];

int n;
arrayN S, T, match, w[MAXN], lx, ly;

int dfs(int x)
{
	S[x] = 1;
	REPP(i, 1, n)
		if (lx[x] + ly[i] == w[x][i] && !T[i]) 
	{
		T[i] = 1;  //容易忽略
		if (!match[i] || dfs(match[i])) //dfs中别漏了match
		{
			match[i] = x;
			return 1;
		}
	}
	return 0;
}

void update()
{
	int minL = INF; //找最小
	REPP(i, 1, n)
		if (S[i])
			REPP(j, 1, n)
				if (!T[j])
					minL = min(minL, lx[i] + ly[j] - w[i][j]);
	REPP(i, 1, n)
	{
		if (S[i]) lx[i] -= minL;
		if (T[i]) ly[i] += minL;
	}
}
void KM()
{
	REPP(i, 1, n)
	{
		lx[i] = 0;
		ly[i] = 0;
		match[i] = 0;
		REPP(j, 1, n)
			lx[i] = max(lx[i], w[i][j]);
	}
	REPP(i, 1, n)
	{
		for (;;)
		{
			MST(S, 0);
			MST(T, 0);
			if (dfs(i)) break;
			else update();
		}
	}
}
int main()
{
	freopen("in.txt", "r", stdin);
	for (; scanf("%d", &n) != EOF; )
	{
		REPP(i, 1, n)
			REPP(j, 1, n)
			scanf("%d", &w[i][j]);
		KM();
		REPP(i, 1, n)
			printf("%d%c", lx[i], " \n"[i == n]);		
		REPP(i, 1, n)
			printf("%d%c", ly[i], " \n"[i == n]);
		int ans = 0;
		REPP(i, 1, n)
			ans += w[match[i]][i];
		printf("%d\n", ans);
	}
	return 0;
}
