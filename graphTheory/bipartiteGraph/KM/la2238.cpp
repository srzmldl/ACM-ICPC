#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 512
#define INF 0x3f3f3f3f

using namespace std;
typedef int arrayN[MAXN];

int n, m;
arrayN S, T, memcap, match, w[MAXN], edge[MAXN], wsp, lx, ly, maxLab, rankR, tim[MAXN];
int bestW;

int dfs(int x)
{
	S[x] = 1;
	REPP(i, 1, n * m)
		if (w[x][i] == lx[x] + ly[i] && !T[i] && edge[x][i])
		{
			T[i] = 1;
			if (!match[i] || dfs(match[i]))
			{
				match[i] = x;
				return 1;
			}
		}
	return 0;
}

void update()
{
	int minW = INF;
	REPP(i, 1, n)
		REPP(j, 1, n * m)
		if (lx[i] + ly[j] != w[i][j] && edge[i][j])
			minW = min(minW, lx[i] + ly[j] - w[i][j]);
	REPP(i, 1, n)
		if (S[i]) lx[i] -= minW;
	REPP(i, 1, n * m)
		if (T[i]) ly[i] += minW;
}

void KM()
{
	MST(match, 0);
	REPP(i, 1, m * n)
		ly[i] = match[i] = 0;
	REPP(i, 1, n)
	{
		lx[i] = -INF;
		REPP(j, 1, m * n)
			if (edge[i][j])
				lx[i] = max(lx[i], w[i][j]);
	}
	REPP(i, 1, n)
	{
		for(;;)
		{
			MST(S, 0);
			MST(T, 0);
			if (dfs(i)) break;
			else update();
		}
	}
	bestW = 0;
	MST(maxLab, 0);
	REPP(i, 1, n * m)
		if (match[i])
		{
			bestW -= w[match[i]][i];
			wsp[match[i]] = (i - 1) / n + 1;
			rankR[match[i]] = (i - 1) % n + 1;
			tim[wsp[match[i]]][rankR[match[i]]] = -w[match[i]][i] / rankR[match[i]];
			maxLab[wsp[match[i]]] = max(maxLab[wsp[match[i]]], rankR[match[i]]);
		}
	REPP(i, 1, m)
	{
		tim[i][maxLab[i] + 1] = 0;
		for (int j = maxLab[i]; j; --j)
			tim[i][j] += tim[i][j + 1];
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (int task = 1;; ++task)
	{
		scanf("%d%d", &m, &n);
		if (n + m == 0) break;
		if (task > 1) printf("\n");
		printf("Case %d\n", task);
		REPP(i, 1, m) scanf("%d", &memcap[i]);
		REPP(i, 1, n)
			REPP(j, 1, n * m)
			w[i][j] = -INF;
		MST(edge, 0);
		REPP(i, 1, n)
		{
			int k;
			scanf("%d", &k);
			
			int s[12], t[12];
			REPP(j, 1, k)
			{
				scanf("%d%d", &s[j], &t[j]);
			}
			REPP(h, 1, m)
				for (int j = k; j >= 1; --j)
					if (s[j] <= memcap[h])
					{
						int ti = t[j];
						REPP(t, 1, n)
						{
							edge[i][(h - 1) * n + t] = 1;
							w[i][(h - 1) * n + t] = max(w[i][(h - 1) * n + t], -ti * t);
						}
						break;
					}
		}
		KM();
		printf("Average turnaround time = %.2f\n", bestW * 1.0 / n);
		REPP(i, 1, n)
		{
			printf("Program %d runs in region %d from %d to %d\n", i, wsp[i], tim[wsp[i]][rankR[i] + 1], tim[wsp[i]][rankR[i]]);
		}
		
	}
	return 0;
}
