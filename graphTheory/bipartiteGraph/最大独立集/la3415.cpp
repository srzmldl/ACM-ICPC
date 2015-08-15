#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 512

using namespace std;

typedef int arrayN[MAXN];

struct node
{
	int height;
	char sex;
	string music, sport;
} a[MAXN], b[MAXN];

arrayN vis, w[MAXN], match;
int n, task, tot1, tot2;

int abs(int x )
{return x < 0 ? -x : x;}

int dfs(int x)
{
	REPP(i, 1, tot2)
		if (w[x][i] && !vis[i])
		{
			vis[i] = 1;
			if (!match[i] || dfs(match[i]))
			{
				match[i] = x;
				return 1;
			}
		}
	return 0;
}
int main()
{
	freopen("in.txt", "r", stdin);
	for(scanf("%d", &task); task ;--task)
	{
		scanf("%d", &n);
		tot1 = 0, tot2 = 0;
		REPP(i, 1, n)
		{
			++tot1;
			cin >> a[tot1].height >>  a[tot1].sex >> a[tot1].music >> a[tot1].sport;
			if (a[tot1].sex == 'F')
			{
				++tot2;
				b[tot2] = a[tot1];
				tot1--;	
			}
		}
		REPP(i, 1, tot1)
			REPP(j, 1, tot2)
			w[i][j] = !(abs(a[i].height - b[j].height) > 40 || a[i].music != b[j].music || a[i].sport == b[j].sport);
		MST(match, 0);
		int ans = 0;
		REPP(i, 1, tot1)
		{
			MST(vis, 0);
			if (dfs(i)) ans++;
		}
		printf("%d\n", tot1 + tot2 - ans);
	}
	return 0;
}
