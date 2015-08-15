#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 55;
const int MO = 1e9 + 7;

void add(int &x, int y) {
	x += y;
	if (x >= MO) x -= MO;
}

int dp[N][25][30][2], sum[N][25][30][2], pw[N] = {1}, cnt[N][25];
char s[N][25];

int main() {
	ios :: sync_with_stdio(0);
	freopen("B.in", "r", stdin);

	REPP(i, 1, 20) pw[i] = 26LL * pw[i - 1] % MO;
	int n;
	cin >> n;
	REPP(i, 1, n) cin >> s[i] + 1;
	REPP(i, 1, n) {
		int len = strlen(s[i] + 1);
		for (int j = len; j >= 1; j--) {
			cnt[i][j] = cnt[i][j + 1] + (s[i][j] == '?');
		}
	}
	REPP(j, 0, 20) {
		REPP(c, 0, 26) {
			dp[0][j][c][1] = 1;
		}
	}
	REPP(i, 1, n) {
		int len = strlen(s[i] + 1);
		REPP(j, 1, 26) sum[i][0][j][0] = 1;
		REPP(j, 1, len) {
			REPP(c, 1, 26) {
				if (s[i][j] == 'a' + c - 1 || s[i][j] == '?') {
					if (i == 1 || 'a' + c - 1 == s[i - 1][j]) {
						dp[i][j][c][0] = sum[i][j - 1][26][0] * (i == 1 || 'a' + c - 1 == s[i - 1][j]);
					}
				}
			}
			REPP(c, 1, 26) {
				sum[i][j][c][0] = sum[i][j][c - 1][0];
				add(sum[i][j][c][0], dp[i][j][c][0]);
			}
			REPP(c, 1, 26) {
				if (s[i][j] == 'a' + c - 1 || s[i][j] == '?') {
					dp[i][j][c][1] = sum[i][j - 1][26][1];
					add(dp[i][j][c][1], 1LL * sum[i][j - 1][26][0] * dp[i - 1][j][c - 1][1] % MO * pw[cnt[i][j + 1]] % MO);
				}
			}
		}
	}
	REPP(i, 1, n) {
		REPP(j, 1, strlen(s[i] + 1)) {
			REPP(c, 1, 26) {
				cout << dp[i][j][c][1] << ' ';
			}
			cout << endl;
		}
	}
	int len = strlen(s[n] + 1);
	cout << dp[n][len][26][1] << endl;

	return 0;
}

