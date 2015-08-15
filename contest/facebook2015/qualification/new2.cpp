#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXN 25

int task, p[MAXN], c[MAXN], f[MAXN];

int main()
{
	freopen("in2.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		int gp, gc, gf, N;
		printf("Case #%d: ", t);
		scanf("%d%d%d", &gp, &gc,&gf);
		scanf("%d", &N);
		REPP(i, 1, N)
			scanf("%d%d%d", &p[i], &c[i], &f[i]);
		int ans = 0;
		for (int i = 0; (i < (1 << N)) && !ans; ++i)
		{
			int tp = 0, tc = 0, tf = 0;
			REPP(j, 1, N)
				if (i & (1 << (j - 1)))
					tp += p[j], tc += c[j], tf += f[j];
			if (tp == gp && tc == gc && tf == gf)
				ans = 1;
		}
		if (ans) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
