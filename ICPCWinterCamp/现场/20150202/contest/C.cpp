#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;
#define MAXN 5100
int n, k[MAXN], s[MAXN][52], sum[MAXN][52];
int main() {
	ios :: sync_with_stdio(0);
	freopen("C.in", "r", stdin);
	scanf("%d", &n);
	REPP(i, 1, n)
	{
		scanf("%d", &k[i]);
		REPP(j, 1, k[i])
			scanf("%d", &s[i][j]);
		sort(s[i] + 1, s[i] + k[i] + 1);
		REPP(j, 1, k[i])
			sum[i][s[i][j]] = 1;
		REPP(j, 1, 50)
			sum[i][j] += sum[i][j - 1];
		s[i][0] = 0;
	}
	int ans = 0;
	REPP(i, 1, n - 1)
		REPP(j, i + 1, n)
	{
		int t = 0;
		REPP(h, 1, k[j])
			if ((sum[i][s[j][h]] - sum[i][s[j][h - 1]]))
				++t;
		if (t & 1) ans++;
				
				
	}
	printf("%d\n", ans);
	return 0;
}
