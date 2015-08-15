#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int main() {
	ios :: sync_with_stdio(0);

	int n, k;
	cin >> n >> k;
	if (k == 0) {
		cout << 0 << endl;
	}
	else if (n == 2 && k == 1) {
		cout << 1 << endl;
		cout << 0 << ' ' << 1 << endl;
	}
	else {
		k = n - k;
		if (k == 1 || k == n - 1) {
			cout << 2 << endl;
			if (k == 1) {
				cout << 1 << ' ' << n - 1 << endl;
				cout << 0 << ' ' << n - 1 << endl;
			}
			else {
				cout << 0 << ' ' << k - 1 << endl;
				cout << 0 << ' ' << n - 1 << endl;
			}
		}
		else if (k == 2 || k == n - 2) {
			cout << 2 << endl;
			if (k == n - 2) {
				cout << 0 << ' ' << n - 2 << endl;
				cout << 1 << ' ' << n - 1 << endl;
			}
			else {
				cout << 1 << ' ' << n - 1 << endl;
				cout << 0 << ' ' << n - 2 << endl;
			}
		}
		else {
			cout << 3 << endl;
			cout << 0 << ' ' << k - 1 << endl;
			cout << 0 << ' ' << n - 1 << endl;
			cout << 0 << ' ' << n - k - 1 << endl;
		}
	}

	return 0;
}

