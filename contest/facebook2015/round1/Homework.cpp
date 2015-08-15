#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))

#define MAXN 11234567

using namespace std;

int a[MAXN];
int lim = 10000000;
int tot, pri[MAXN], vis[MAXN];

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
	MST(a, 0);
	MST(vis, 0);
	tot = 0;
	REPP(i, 2, lim)
	{
		if (!vis[i]) 
		{
			pri[++tot] = i;
			a[i] = 1;
			vis[i] = 1;
		}
		REPP(j, 1, tot)
		{
			if (1LL * i * pri[j] > lim) break;
			vis[i * pri[j]] = 1;
			a[pri[j] * i] = a[i];
			if (i % pri[j] == 0) break;
			a[pri[j] * i] ++;
		}
	}
	int task;
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		int A, B, K;
		int ans = 0;
		scanf("%d%d%d", &A, &B,&K);
		REPP(i, A, B)
			if (a[i] == K) ans++;
		printf("Case #%d: %d\n", t, ans);
	}
	return 0;
}
