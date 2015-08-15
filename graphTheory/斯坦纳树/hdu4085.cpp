#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <vector>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 60
#define MAXK 12
#define STALIM 4000
#define MAXM 4000
typedef int arrayN[MAXN], arrayM[MAXM];

using namespace std;

int task, n, m, k, num, g[STALIM], f[STALIM];
int dp[MAXN][STALIM];
vector <int> stac;
arrayN inS, fir;
arrayM nxt, e, c;


void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

void updateMin(int &u, int v)
{
	u = min(u, v);
}

int check(int sub)
{
	int s1 = 0, s2 = 0;
	REPP(i, 1, k)
	{s1 += sub & 1; sub >>= 1;}
	REPP(i, 1, k)
	{s2 += sub & 1; sub >>= 1;}
	return s1 == s2;
}


int main()
{
	freopen("hdu4085.txt", "r", stdin);
	for (scanf("%d", &task); task; --task)
	{
		num = 0;
		MST(fir, 0);
		scanf("%d%d%d", &n, &m, &k);
		REP(i, m) 
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			link(u, v, w);
			link(v, u, w);
		}
		MST(dp, 0x3f);
		int INF = dp[0][0];
		REPP(i, 1, n) dp[i][0] = 0;
		REPP(i, 1, k) 
		{
			dp[i][1 << (i - 1)] = 0;
			dp[n - i + 1][1 << (i - 1 + k)] = 0;
		}

		int staLim = (1 << (2 * k)) - 1;
		REPP(sta, 1, staLim)
		{
			MST(inS, 0);
			REPP(i, 1, n)
			{
				for (int sub = sta & (sta - 1); sub; sub = (sub - 1) & sta)
					updateMin(dp[i][sta], dp[i][sub] + dp[i][sta - sub]);
				
				if (dp[i][sta] < INF) 
				{
					stac.push_back(i);
					inS[i] = 1;
				}
			}
			for (; !stac.empty(); )
			{
				int tmp = stac.back();
				stac.pop_back();
				inS[tmp] = 0;
				for (int p = fir[tmp]; p; p = nxt[p])
					if (dp[e[p]][sta] > dp[tmp][sta] + c[p])
					{
						dp[e[p]][sta] = dp[tmp][sta] + c[p];
						if (!inS[e[p]]) 
						{
							inS[e[p]] = 1;
							stac.push_back(e[p]);
						}
					}
			}
		}
		
		
		REPP(i, 0, staLim)
		{
			g[i] = INF;
			REPP(j, 1, n)
				updateMin(g[i], dp[j][i]);
			//	printf("%d:%d\n", i, g[i]);
		}

		MST(f, 0x3f);
		f[0] = 0;
		REPP(i, 0, staLim)
		{
			f[i] = g[i];
			for (int sub = (i- 1) & i; sub; sub = (sub - 1) & i)
				if (check(sub) && check(i - sub))
					updateMin(f[i], f[sub] + g[i - sub]);
		}
		if (f[staLim] < INF)
			printf("%d\n", f[staLim]);
		else printf("No solution\n");
		
	}
	return 0;
}
