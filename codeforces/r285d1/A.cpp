#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 212345

using namespace std;

typedef int arrayN[MAXN];

vector <int> sta;
int n;
struct node
{int deg, s;}a[MAXN];

struct edge
{int u, v;} ed[MAXN];

int main()
{
	//freopen("A.in", "r", stdin);
	scanf("%d", &n);
	sta.clear();
	REP(i, n)
	{
		scanf("%d%d", &a[i].deg, &a[i].s);
		if (a[i].deg == 1) sta.push_back(i);
	}
	int m = 0;
	for (; !sta.empty();)
	{
		int u = sta.back();
		sta.pop_back();
		if (a[u].deg == 0) continue;
		++m;
		ed[m].u = u;
		int v = a[u].s;
		ed[m].v = v;
		a[v].deg--;
		a[v].s ^= u;
		if (a[v].deg == 1)
			sta.push_back(v);
	}
	printf("%d\n", m);
	REPP(i, 1, m)
		printf("%d %d\n", ed[i].u, ed[i].v);
	return 0;
}
