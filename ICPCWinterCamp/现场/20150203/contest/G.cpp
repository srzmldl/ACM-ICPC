#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

#define MAXN 1123456

using namespace std;
typedef int arrayN[MAXN];

int num, n, m;
arrayN fir, e, nxt, deg;

void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, deg[v]++;
}

int topSort()
{
	vector<int> sta;
	REPP(i, 1, n)
		if (deg[i] == 0) sta.push_back(i);
	for (;!sta.empty();)
	{
		if (sta.size() > 1) return 0;
		int u = sta.back();
		sta.pop_back();
		for (int p = fir[u]; p; p = nxt[p])
		{
			deg[e[p]] --;
			if (!deg[e[p]])
				sta.push_back(e[p]);
		}
	}
	return 1;
}

int main() {
	ios :: sync_with_stdio(0);
//	freopen("G.in", "r", stdin);
	scanf("%d%d", &n, &m);
	int ans = 1;
	MST(fir, 0);
	MST(deg, 0);
	REPP(i, 1, m)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (u == v)
		{
			--i, --m;
			continue;
		}
		if (u > v)
		{
			ans = 0;
			printf("No\n");
			return 0;
		}
		link(u, v);
	}
	ans = topSort();
	if (ans) printf("Yes\n");
	else printf("No\n");
	return 0;
}
