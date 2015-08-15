#include<bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 1111

using namespace std;

int vis[MAXN];
char st[MAXN];

int main()
{
	freopen("threeCircle.in", "r", stdin);
	for(;;)
	{
		int n;
		scanf("%d", &n);
		if (!n) break;
		MST(vis, 0);
		int ans = 1;
		REP(i, n)
		{
			int tmp = 0;
			scanf("%s", st);
			REP(j, n)
				if (st[j] == '1')
					tmp++;
			vis[tmp]++;
			if (vis[tmp] > 1) ans = 0;
		}
		printf(ans ? "NO\n" : "YES\n");
	}
	return 0;
}
