#include<bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 1111
#define MAXM 1111111

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, deg;
arrayM nxt, e;
char st[MAXN];
int num;

void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, deg[v]++;
}

int main()
{
	freopen("threeCircle.in", "r", stdin);
	for(;;)
	{
		int n;
		scanf("%d", &n);
		if (!n) break;
		num = 0;
		MST(fir, 0);
		MST(deg, 0);
		int tot = 0;
		REP(i, n)
		{
			scanf("%s", st);
			REP(j, n)
				if (st[j] == '1')
					link(i, j);
		}
		vector<int> sta;
		REP(i, n)
			if (deg[i] == 0)
				sta.push_back(i);
		for (; !sta.empty();)
		{
			int tmp = sta.back();
			++tot;
			sta.pop_back();
			for(int p = fir[tmp]; p; p = nxt[p])
			{
				--deg[e[p]];
				if (!deg[e[p]])
					sta.push_back(e[p]);
			}
		}
		printf(tot == n ? "NO\n" : "YES\n");
	}
	return 0;
}
