#include <bits/stdc++.h>

#define LL long long
#define REP(i, a) REPP(i, 0, (a) - 1)
#define REPP(i, a, b) for (int i = int(a); i <= int(b); i++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 350;

int ans[N], edge[N];
int n;

void color() {
	REPP(i, 1, n) {
		edge[i] = (i & 1) * 2 + 1;
	}
	REPP(i, 1, n) {
		ans[i] = (i & 1) + 1;
	}
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("jubilee.in", "r", stdin);
	freopen("jubilee.out", "w", stdout);

	while (cin >> n) {
		int ans = 0;
		if (n == 3) {
			ans = 1;
			REPP(i, 1, n) ::ans[i] = edge[i] = 1;
		}
		else if (n == 5) {
			ans = 2;
			int tmp[6] = {0, 1, 1, 1, 1, 2};
			int tmp2[6] = {0, 1, 2, 1, 2, 1};
			REPP(i, 1, n) ::ans[i] = tmp[i], edge[i] = tmp2[i];
		}
		else if (n == 4
            || n == 6) {
			ans = 2;
			REPP(i, 1, n) ::ans[i] = (i & 1) + 1;
			REPP(i, 1, n) edge[i] = (i & 1) + 1;
		}
		else {
			ans = 3;
			color();
		}
		cout << ans << endl;
		REPP(i, 1, n) {
			cout << ::ans[i] << " \n"[i == n];
		}
		REPP(i, 1, n) {
			cout << edge[i] << " \n"[i == n];
		}
	}

	return 0;
}
