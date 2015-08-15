#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))

#define MAXN 401234

using namespace std;
typedef int arrayN[MAXN];

int n;
int num, sta[MAXN];
arrayN fir, nxt, e;

const int INF = 0x3f3f3f3f;

const int lim = 20;

int f[MAXN][lim], g[MAXN][lim], t1[lim], t2[lim];

void link(int u, int v)
{
	e[++num] = v;
	nxt[num] = fir[u];
	fir[u] = num;
}

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out4.txt", "w", stdout);
	int task;
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		num = 0;
		MST(fir, 0);
		scanf("%d", &n);
		REPP(i, 1, n)
		{
			int u, v;
			scanf("%d", &u);
			v = i;
			if (u == 0) continue;
			link(u, v);
		}
		int l = 1, r = 1;
		sta[1] = 1;
		for (; l <= r;)
		{
			int tmp = sta[l];
			++l;
			for (int p = fir[tmp]; p; p = nxt[p])
			{
				sta[++r] = e[p];
			}
		}

		for (int i = n; i >= 1; --i)
		{
			int u = sta[i];
			for (int j = 1; j <= lim; ++j)
			{
				f[u][j] = j;
				for (int p = fir[u]; p; p = nxt[p])
				{
					int v = e[p];
					f[u][j] += g[v][j];
				}
			}
			t1[1] = INF;
			REPP(j, 2, lim)
				t1[j] = min(t1[j - 1], f[u][j - 1]);
			t2[lim] = INF;
			for (int j = lim - 1; j >= 1; --j)
				t2[j] = min(t2[j + 1], f[u][j + 1]);
			REPP(j, 1, lim)
				g[u][j] = min(t1[j], t2[j]);
		}
		
		printf("Case #%d: %d\n", t, min(f[1][1], g[1][1]));
	}
	return 0;
}
