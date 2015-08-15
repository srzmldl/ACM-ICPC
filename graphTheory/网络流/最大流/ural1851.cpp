#include <bits/stdc++.h>
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define MAXN 3000
#define MAXM 3000000
#define INF 0x3F3F3F
#define mem(a) memset(a, 0, sizeof(a))

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

char sts[1010], stp[1010];

int S, T, num;
arrayN fir, slack, cur, vis, d;
arrayM nxt, e, c;

int abs(int x) {return x < 0 ? -x : x;}

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

int bfs()
{
	REPP(i, 1, T) d[i] = INF;
	d[0] = 0;
	int l = 1, r = 1;
	slack[1] = S;
	mem(vis);
	vis[S] = 1;
	for (; l <= r; ++l)
	{
		int tmp = slack[l];
		for (int p = fir[tmp]; p; p = nxt[p])
			if (!vis[e[p]] && c[p])
			{
				d[e[p]] = d[tmp] + 1;
				vis[e[p]] = 1;
				slack[++r] = e[p];
			}
	}
	if (d[T] < INF) return 1;
	return 0;
}

int dfs(int x, int low)
{
	if (x == T || low == 0) return low;
	int tmp = 0;
	for (int &p = cur[x]; p; p = nxt[p])
		if (d[e[p]] == d[x] + 1 && c[p])
		{
			int mid = dfs(e[p], min(low, c[p]));
			if (mid == 0) d[e[p]] = INF;
			tmp += mid;
			c[p] -= mid;
			c[p ^ 1] += mid;
			low -= mid;
			if (!low) break;
		}
	return tmp;
}

int dinic()
{
	int tmp = 0;
	for (; bfs(); ){
		REPP(i, 0, T) cur[i] = fir[i]; 
		tmp += dfs(S, INF);
		
	}
	return tmp;
}

void pwh()
{
	REPP(i, 1, 1000) printf("?");
	printf("\n");
	REPP(i, 1, 500) printf("?");
	printf("\n");
}

int main()
{
	freopen("in.txt", "r", stdin);
//	pwh();
	scanf("%s", sts);
	scanf("%s", stp);
	int ls = strlen(sts), lp = strlen(stp);
	int ans = 0;
	S = 0, T = ls + lp + 1;
	num = 1;
	mem(fir);
	REP(i, lp)
		REP(j, ls)
		if (j >= i && j <= ls - (lp - i))
		{
			if (stp[i] != '?' && sts[j] != '?')
				ans += abs(stp[i] - sts[j]);
			else
			{
				int u, v;
				if (stp[i] == '?') u = i + 1;
				else if (stp[i] == '0') u = S;
				else u = T;
					
				if (sts[j] == '?') v = lp + j + 1;
				else if (sts[j] == '0') v = S;
				else v = T;
				
				link(u, v, 1);
				//	link(v, u, 0);

				link(v, u, 1);
				//	link(u, v, 0);
			}
		}
	ans += dinic();
	printf("%d\n", ans);
	REPP(i, 1, ls)
		if (sts[i - 1] == '?')
		{
			if (vis[i + lp]) printf("0");
			else printf("1");
		} else printf("%c", sts[i - 1]);
	printf("\n");
	
	REPP(i, 1, lp)
		if (stp[i - 1] == '?')
		{
			if (vis[i]) printf("0");
			else printf("1");
		} else printf("%c", stp[i - 1]);
	printf("\n");

	return 0;
}
