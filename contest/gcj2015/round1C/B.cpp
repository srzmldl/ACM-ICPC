#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <cassert>
#include <climits>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <bitset>
#include <algorithm>

#define MST(a, b) memset(a, b, sizeof(a))
#define REP(i, a) for (int i = 0; i < int(a); i++)
#define REPP(i, a, b) for (int i = int(a); i <= int(b); i++)

using namespace std;
const int N = 105;
int f[N], n, key, len;
int dp[N][N];
double p[N][N][N];
char s[N], mp[N];

void get() {
	f[0] = f[1] = 0;
	for (int i = 1; i < n; i++) {
		int j = f[i];
		while (j && s[j] != s[i]) j = f[j];
		f[i + 1] = s[j] == s[i] ? j + 1 : 0;
	}
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("B.in", "r", stdin);
	freopen("B.ans", "w", stdout);

	int t, ca = 1;
	cin >> t;
	while (t--) {
		cin >> key >> n >> len;
		//key length of keyboard
		//n lenght of target
		//len length to construct
		cin >> mp >> s;
		//cout << mp << ' ' << s << endl;
		get();
		dp[0][0] = 0;
		REPP(i, 0, len - 1) {
			int lim = min(i, n);
			REPP(j, 0, lim) {
				REP(k, key) {
					int pos = j;
					while (pos && s[pos] != mp[k]) pos = f[pos];
					pos = s[pos] == mp[k] ? pos + 1 : 0;
					dp[i + 1][pos] = max(dp[i + 1][pos], dp[i][j] + (pos == n));
				}
			}
		}
		p[0][0][0] = 1.0;
		REPP(i, 0, len - 1) {
			REPP(cnt, 0, len) {
				int lim = min(i, n);
				REPP(j, 0, lim) {
					REP(k, key) {
						int pos = j;
						while (pos && s[pos] != mp[k]) pos = f[pos];
						pos = s[pos] == mp[k] ? pos + 1 : 0;
						int add = pos == n;
						p[i + 1][cnt + add][pos] += p[i][cnt][j] / key;
					}
				}
			}
		}
		int ans = 0;
		double pans = 0;
		REPP(i, 0, n) ans = max(ans, dp[len][i]);
		REPP(i, 1, len) {
			REPP(j, 0, n) {
				pans += i * p[len][i][j];
			}
		}
		//cout << ans << ' ' << pans << endl;
		cout << "Case #" << ca++ << fixed << setprecision(10) << ": " << ans - pans << endl;
		MST(dp, 0), MST(p, 0);
	}

	return 0;
}

