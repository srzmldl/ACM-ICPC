#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 2005;
int a[N];

int main() {
	ios :: sync_with_stdio(0);
	//freopen("A.in", "r", stdin);

	int n, m;
	cin >> n >> m;
	REPP(i, 1, n) cin >> a[i];
	while (m--) {
		int ty, l, r, qd;
		cin >> ty >> l >> r;
		if (ty <= 3) {
			cin >> qd;
			if (ty == 1) {
				REPP(i, l, r) a[i] += qd;
			}
			else if (ty == 2) {
				REPP(i, l, r) a[i] = min(a[i], qd);
			}
			else if (ty == 3) {
				REPP(i, l, r) a[i] = max(a[i], qd);
			}
		}
		else {
			int mi = 2e9, mx = -2e9;
			REPP(i, l, r) mi = min(mi, a[i]);
			REPP(i, l, r) mx = max(mx, a[i]);
			cout << mi << ' ' << mx << endl;
		}
	}



	return 0;
}

