#include <bits/stdc++.h>
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)

using namespace std;

int gcd(int u, int v)
{
	if (!u || !v) return u + v;
	return gcd(v, u % v);
}

int main()
{
	freopen("out.txt", "w", stdout);
	int lim = 20000;
	int cnt = 0;
	REPP(i, 1, lim)
		REPP(j, 1, lim)
		if (gcd(i, j) != 1) ++cnt;
	printf("%d\n", cnt);
	return 0;
}
