#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 212345

using namespace std;

int g[20], n, h[20];

int main()
{
	//freopen("A.in", "r", stdin);
	MST(g, 0);
	scanf("%d\n", &n);
	REPP(i, 1, n)
	{
		char ch;
		scanf("%c", &ch);
		int tmp = ch - '0';
		REPP(j, 2, tmp)
			g[j]++;
	}
	g[2] += g[4] * 2 + g[6] + g[8] * 3;
	g[3] += g[6] + g[9] * 2;
	h[7] = g[7];
	h[6] = h[7];
	h[5] = g[5];
	h[4] = h[5];
	h[3] = g[3] - h[6];
	h[2] = g[2] - h[6] - h[4] * 2;
	for (int i = 7; i >= 2; --i)
	{
		for (int j = h[i] - h[i + 1]; j >= 1; --j)
			printf("%d", i);
	}
	printf("\n");
	return 0;
}
