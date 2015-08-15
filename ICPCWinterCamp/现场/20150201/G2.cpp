#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 1005;
int a[N];

int main() {
	ios :: sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	REPP(i, 1, m) {
		cin >> a[i];
		a[i]--;
	}
	string s(n, '0');
	REPP(i, 1, m) s[a[i]] = '1';
	set<string> myset;
	REP(i, n) {
		REPP(j, i, n) {
			myset.insert(s.substr(i, j - i + 1));
		}
	}
	cout << myset.size() << endl;

	return 0;
}

