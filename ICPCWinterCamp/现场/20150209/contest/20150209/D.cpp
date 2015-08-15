#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 2005;
const int MO = 10000007;
const int exxp = 3214567;

int fi[MO], ne[MO], step[MO], edge;
int dp[MO], stepLab[MO];
int a[N];

void add(int x, int lab, int d, int y) {
	ne[++edge] = fi[x];
	fi[x] = edge;
	step[edge] = d;
	stepLab[edge] = lab;
	dp[edge] = y;
}

int myhash(int x, int d) {
	//return 1LL * x * x % MO * (d + x) % MO;
	return (1LL * d * exxp % MO + x) % MO;
}

int gethash(int x, int d) {
	int tmp = myhash(x, d);
	int go;
	for (go = fi[tmp]; go && (step[go] != d || stepLab[go] != x); go = ne[go]);
	return go;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		REPP(i, 1, n) {
			scanf("%d", a + i);
		}
		sort(a + 1, a + n + 1);
		int res = 1;
		REPP(i, 1, n) {
			REPP(j, i + 1, n) {
				if (!gethash(j, a[j] - a[i])) {
					int tmp = myhash(j, a[j] - a[i]);
					add(tmp, j, a[j] - a[i], 2);
				}
			}
		}
		REPP(i, 1, n) {
			REPP(j, 1, i - 1) {
				int x = a[i], y = a[j];
				int d = abs(x - y);
				int &ans = dp[gethash(i, d)];
				int tmp = gethash(j, d);
				if (tmp)
					ans = max(ans, dp[tmp] + 1);
				res = max(res, ans);
			}
		}
		cout << res << endl;
		REPP(i, 1, n) {
			REPP(j, i + 1, n) {
				int tmp = myhash(j, a[j] - a[i]);
				fi[tmp] = 0;
			}
		}
		edge = 0;
	}

	return 0;
}
