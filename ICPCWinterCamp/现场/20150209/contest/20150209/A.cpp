#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 100005;
int a[N];

int main() {
	ios :: sync_with_stdio(0);
	int t;
	cin >> t;
	int n, m, x, y;
	while (t--) {
		cin >> n >> m >> x >> y;
		REPP(i, 1, n) {
			cin >> a[i];
		}
		if (n < 2 + m) {
			cout << "NO" << endl;
			continue;
		}
		sort(a + 1, a + n + 1);
		bool flag = 0;
		if (x >= y) {
			if (a[n] < x || a[n - 1] < x) {
				flag = 1;
			}
			for (int i = n - 2, j = 0; i >= 1 && j < m; i--, j++) {
				if (a[i] < y) flag = 1;
			}
		}
		else {
			for (int i = n, j = 0; i >= 1 && j < m; i--, j++) {
				if (a[i] < y) {
					flag = 1;
				}
			}
			if (a[n - m] < x || a[n - m - 1] < x) {
				flag = 1;
			}
		}
		if (!flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	return 0;
}

