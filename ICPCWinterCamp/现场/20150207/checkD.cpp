#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MO 1000000007

using namespace std;


int main() {
	ios :: sync_with_stdio(0);
	freopen("checkD.out", "w", stdout);
	for (int h = 31; h <= 60; ++h)
	{
		int n = h;
		n = n - n % 5;
		n /= 5;
		long long ans = 0;
		REPP(i, 0, n / 5)
			REPP(j, 0, (n - i * 5) / 2)
			ans = (ans + n - 5 * i - 2 * j + 1) % MO;
		cout << ans << endl;
	}
	return 0;
}
