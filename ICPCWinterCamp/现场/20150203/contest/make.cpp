#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;
const int N = 2005;
int a[N];

int main() {
	ios :: sync_with_stdio(0);
	srand(time(0) % clock());

	int n = 40, m = rand() % 40 + 3;
	cout << n << ' ' << m << endl;
	REPP(i, 1, n) a[i] = 100 - rand() % 200;
	REPP(i, 1, n) cout << a[i] << ' ';
	cout << endl;
	while (m--) {
		int ty = rand() % 4 + 1;
		int l = rand() % n + 1, r = rand() % n + 1;
		int qd = 300 - rand() % 500;
		if (l > r) swap(l, r);
		if (ty <= 3) {
			cout << ty << ' ' << l << ' ' << r << ' ' << qd << endl;
		}
		else {
			cout << ty << ' ' << l << ' ' << r << endl;
		}
	}

	return 0;
}

