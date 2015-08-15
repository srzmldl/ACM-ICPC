#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 1123
#define MAXM 112345

using namespace std;

struct edge
{
	int u, v, w;
}ed[MAXM];

int com(edge A, edge B)
{
	return A.w < B.w;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int T;
	for (scanf("%d", &T); T; --T)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		REP(i, m)
			scanf("%d%d%d", &ed[i].u, &ed[i].v, &ed[i].w);
		sort(ed, ed + m, com);
		for (int i = m - 1; i >= 0; --i)
		{
		}
	}
	return 0;
}

