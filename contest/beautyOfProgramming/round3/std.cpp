#include <bits/stdc++.h>

#define INF 1000000001

using namespace std;

int a[10010];

int main()
{
	//freopen("1.in", "r", stdin);
	// freopen("1.out", "w", stdout);

	int T;
	scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++)
	{
		printf("Case #%d:\n", ca);
		int n, q;
		scanf("%d %d", &n, &q);
		for (int i = 0; i < n; i++)
			scanf("%d", &a[i]);
		for (int i = 0; i < q; i++)
		{
			int l, r, k;
			scanf("%d %d %d", &l, &r, &k);
			l--, r--;
			int mini = INF;
			for (int j = l; j <= r; j++)
				mini = min(abs(a[j] - k), mini);
			printf("%d\n", mini);
		}
	}

	return 0;
}

