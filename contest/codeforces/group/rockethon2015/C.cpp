#include <bits/stdc++.h>
#define MAXN 10
using namespace std;


int n;

struct node
{
	int l, r;
}g[MAXN];

int main()
{
//	freopen("C.in", "r", stdin);
	scanf("%d", &n);
	int limL = 10000, limR = 1;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d", &g[i].l, &g[i].r);
		limL = min(limL, g[i].l);
		limR = max(limR, g[i].r);
	}
	double ans = 0;
	for (int i = limL; i <= limR; ++i)
		for (int j = 1; j < (1 << n); ++j)
		{
			int a[6], bitNum = 0;
			int ok = 1;
			for (int k = 0; k < n && ok; ++k)
			{
				a[k] = (j & (1 << k)) > 0;
				bitNum += a[k];
				if (a[k])
				{
					if (i < g[k].l || i > g[k].r) ok = 0;
				}
			}
			if (!ok) continue;
			double tmp = i;
			if (bitNum != 1)
			{
				for (int k = 0; ok && k < n; ++k)
					if (!a[k])
					{
						if (g[k].l >= i) ok = 0;
						tmp *= 1.0 * (min(i - 1, g[k].r) - g[k].l + 1) / (g[k].r - g[k].l + 1);
					} else tmp *= 1.0 / (g[k].r - g[k].l + 1);
				if (ok) ans += tmp;
			}
			{
				for (int king = 0; king < n; ++king)
					if (!a[king] && g[king].r > i)
					{
						double t1 = 1.0 * i * (g[king].r - max(i + 1, g[king].l) + 1) / (g[king].r - g[king].l + 1);
						for (int k = 0; k < n; ++k)
							if (k != king)
							{
								if (a[k]) t1 *= 1.0 / (g[k].r - g[k].l + 1);
								else 
								{
									if (g[k].l >= i)
										t1 = 0;
									else t1 *= 1.0 * (min(i - 1, g[k].r) - g[k].l + 1) / (g[k].r - g[k].l + 1);
								}
							}
						ans += t1;
					}
			}
		}
	printf("%.10lf\n", ans);
	return 0;
}

