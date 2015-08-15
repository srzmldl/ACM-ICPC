#include<bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 1111

using namespace std;

bool vis[MAXN];
char st[MAXN];
int n, ans;

int main()
{
	freopen("threeCircle.in", "r", stdin);
	for(;;)
	{
		scanf("%d", &n);
		if (!n) break;
		MST(vis, 0);
		ans = 1;
		REP(i, n)
		{
			int tmp = 0;
			scanf("%s", st);
			REP(j, n)
				if (st[j] == '1')
					tmp++;
			if (vis[tmp]) ans = 0;
			else vis[tmp] = true;
		}
		printf(ans ? "NO\n" : "YES\n");
	}
	return 0;
}
