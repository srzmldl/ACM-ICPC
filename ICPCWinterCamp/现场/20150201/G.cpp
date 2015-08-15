#include <bits/stdc++.h>

#define REP(i, a) for (long long i = 0; i < (long long) (a); i ++)
#define REPP(i, a, b) for (long long i = (long long) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const long long MOD = 1e9 + 9;
const long long M = 1005;
const long long N = 1005;

long long pow_mod(long long x, long long y) {
	long long ans = 1;
	while (y) {
		if (y & 1) ans = 1LL * ans * x % MOD;
		y >>= 1;
		x = 1LL * x * x % MOD;
	}
	return ans;
}

long long a[M], pos[M];
long long myhas[M];

bool cmp1(pair<long long, long long> a, pair<long long, long long> b) {
	return a.first > b.first || (a.first == b.first && a.second < b.second);
}

map<long long, long long> hasmp;
vector<pair<long long, long long> > q[N * N];

long long go(long long x) {
	sort(q[x].begin(), q[x].end(), cmp1);
	long long h = MOD, w = 0;
	long long ans = 0;
	REP(i, q[x].size()) {
		if (q[x][i].second > w) {
			h = min(h, q[x][i].first);
			ans += 1LL * h * (q[x][i].second - w);
			w = q[x][i].second;
		}
	}
	return ans;
}

int main() {
	ios :: sync_with_stdio(0);

	long long n, m;
	cin >> n >> m;
	REPP(i, 1, m) cin >> pos[i];
	long long mx = 0;
	a[0] = pos[1] - 1;
	REPP(i, 1, m - 1) {
		a[i] = pos[i + 1] - pos[i] - 1;
	}
	a[m] = n - pos[m];
	REPP(i, 0, m) mx = max(mx, a[i]);
	long long ans = mx;
	long long tot = 0;
	REPP(i, 0, m) myhas[i] = 1;
	REPP(i, 1, m) {
		REPP(start, 0, m) if (i + start <= m) {
			long long en = i + start;
			if (i > 1){
				myhas[start] = 1LL * myhas[start] * pow_mod(31, a[en - 1] + 1) % MOD;
				myhas[start]++;
			}
			if (myhas[start] >= MOD) myhas[start] = 0;
			long long has = myhas[start];
			if (!hasmp.count(has)) {
				hasmp[has] = tot++;
			}
			long long id = hasmp[has];
			q[id].push_back({a[start] + 1, a[en] + 1});
		}
	}
	for (auto it: hasmp) {
		long long tmp = it.second;
		//REP(i, q[tmp].size()) {
		//	cout << q[tmp][i].first << ' ' << q[tmp][i].second << endl;
		//}
		if (q[tmp].size() == 1) {
			ans += 1LL * q[tmp][0].first * q[tmp][0].second;
		}
		else {
			ans += go(tmp);
		}
	}
	cout << ans << endl;

	return 0;
}

