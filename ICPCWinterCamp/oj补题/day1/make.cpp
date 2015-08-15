#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int a[1005];

int main() {
	ios :: sync_with_stdio(0);
	int n, m;
	srand(time(0) % clock());
	n = 1000, m = rand() % 30;
	cout << n << ' ';
	REPP(i, 1, m) {
		a[i] = rand() % n + 1;
	}
	sort(a + 1, a + m + 1);
	m = unique(a + 1, a + m + 1) - a;
	cout << m - 1 << endl;
	REPP(i, 1, m - 1) {
		cout << a[i] << ' ';
	}
	cout << endl;

	return 0;
}

