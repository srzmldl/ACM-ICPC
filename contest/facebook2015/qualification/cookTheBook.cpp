#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXN 15

using namespace std;
const long long INF = 11234567891011LL;

int g[MAXN], task, tot;

long long calc()
{
	long long tmp = 0;
	for (int i = tot; i; --i)
		tmp = tmp * 10 + g[i];
	return tmp;
}

int main()
{
	freopen("in1.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		long long N;
		scanf("%lld", &N);
		printf("Case #%d: ", t);
		if (N == 0) 
		{
			printf(" %lld %lld\n", N, N);
			continue;
		}
		tot = 0;
		for (; N; N /= 10)
			g[++tot] = N % 10;
		long long low = INF, high = -INF;
		REPP(i, 1, tot)
			REPP(j, i, tot)
		{
			swap(g[i], g[j]);
			if (g[tot])
			{
				long long tmp = calc();
				low = min(low, tmp);
				high = max(high, tmp);
			}
			swap(g[j], g[i]);
		}
		printf("%lld %lld\n", low, high);
	}
	return 0;
}
