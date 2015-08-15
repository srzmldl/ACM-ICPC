#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 1e5 + 5;
int tmp[N];

int main() {
	ios :: sync_with_stdio(0);
	srand(time(0) % clock());
	int n = 5, m = 3;
	cout <<  1 << endl << n << ' ' << m << endl;
	REPP(i, 1, n) {
		cout << rand() % 10 << ' ';
	}
	cout << endl;
	while (m--) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if (l > r) swap(l, r);
		int x = rand() % 10;
		cout << l << ' ' << r << ' ' << x << endl;
	}
	return 0;
}
