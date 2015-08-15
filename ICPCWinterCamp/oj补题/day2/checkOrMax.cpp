#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = a; i <= b; ++i)

using namespace std;

int a[112345];

int calc(int l, int r)
{
	int tmp = a[l];
	int tmpAns = 0;
	REPP(i, l, r)
	{
		tmp = max(tmp, a[i]);
		tmpAns |= a[i];
	}
	return tmpAns + tmp;
}
int main()
{
	int n;
	scanf("%d", &n);
	REP(i, n) scanf("%d", a + i);
	REPP(i, 1, n)
	{
		int ans = 0;
		REP(j, n)
			if (j + i - 1 <= n)
			{
				ans = max(ans, calc(j, i + j - 1));
			}
		printf("%d\n", ans);
	}
	return 0;
}
