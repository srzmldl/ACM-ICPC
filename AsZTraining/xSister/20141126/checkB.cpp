#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MOD 1000000007
#define MAXM 1111

using namespace std;

int n, m, a[MAXM], mis[MAXM];

long long getZero()
{
	long long tmp = 0;
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		REPP(k, j + 1, n)
		if (i + j > k)
			tmp ++;
	return tmp;
}

long long getOne()
{
	long long tmp = 0;
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		REPP(k, j + 1, n)
		if (i + j > k)
		{
			int tot = 0;
			tot = mis[i] + mis[j] + mis[k];
			if (tot >= 1) tmp ++;
		}
	return tmp;
}

long long getTwo()
{
	long long tmp = 0;
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		REPP(k, j + 1, n)
		if (i + j > k)
		{
			int tot = 0;
			tot = mis[i] + mis[j] + mis[k];
			if (tot >= 2) tmp ++;
		}
	return tmp;
}

long long getThr()
{
	
	long long tmp = 0;
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		REPP(k, j + 1, n)
		if (i + j > k)
		{
			int tot = 0;
			tot = mis[i] + mis[j] + mis[k];
			if (tot >= 3) tmp ++;
		}
	return tmp;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int task, ca;
	scanf("%d", &ca);
	for (task = 1; task <= ca; ++task)
	{
		MST(mis, 0);
		scanf("%d%d", &n, &m);
		REP(i, m) 
		{
			scanf("%d", &a[i]);
			mis[a[i]] = 1;
		}
		sort(a, a + m);
		/*	printf("%lld\n", getZero());
		printf("%lld\n", getOne());
		printf("%lld\n", getTwo());
		printf("%lld\n", getThr());*/
		long long ans = 0;
		REPP(i, 1, n)
			REPP(j, i + 1, n)
			REPP(k, j + 1, n)
			if (mis[i] + mis[j] + mis[k] == 0)
				if (i + j > k) ans++;
		printf("%lld\n", ans);
		/*ans = getZero();
		ans = (ans - getOne() + MOD) % MOD;
		ans = (ans + getTwo()) % MOD;
		ans = (ans - getThr() + MOD) % MOD;
		printf("Case %d: %lld", task, ans);
		if (task == ca) printf("\n");
		else printf(" \n");*/
	}
	return 0;
}
