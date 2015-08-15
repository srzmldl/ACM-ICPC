#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 200005;

long long cnt[2][N], tail[2], num[2];
int fail[N];

string s, t;

int presolve() {
	bool a = 1;
	REP(i, t.size()) {
		a = (a && (t[i] == 'a'));
		if (!a) return -1;
	}
	int ans = 1000;
	long long mx = -1;
	REP(i, num[0]) {
		mx = max(mx, cnt[0][i]);
	}
	if (mx != -1) {
		int res = 0;
		while(mx - 1 < (int) t.size()) {
			mx <<= 1;
			res++;
		}
		ans = min(ans, res);
	}
	int tmp = tail[0], tmpans = 0;
	if (tmp == 0) return ans;
	while (tmp < (int) t.size()) {
		tmp <<= 1;
		tmpans++;
	}
	ans = min(ans, tmpans);
	return ans;
}

void init() {
	int n = s.size();
	REP(i, n) {
		int tmp = 0;
		while (i < n && s[i] == 'a') tmp++, i++;
		if (i == n) {
			tail[0] = tmp;
		}
		else {
			cnt[0][num[0]++] = tmp + 1;
		}
	}
	n = t.size();
	REP(i, n) {
		int tmp = 0;
		while (i < n && t[i] == 'a') tmp++, i++;
		if (i == n) {
			tail[1] = tmp;
		}
		else {
			cnt[1][num[1]++] = tmp + 1;
		}
	}
	REP(i, 2) cnt[i][num[i]] = -1;
}

long long tmp[N];

void getfail() {
	REP(i, num[1] - 1) {
		tmp[i] = cnt[1][i + 1];
	}
	tmp[num[1] - 1] = -1;
	fail[0] = fail[1] = 0;
	REPP(i, 1, num[1] - 2) {
		int j = fail[i];
		while (j && tmp[j] != tmp[i]) j = fail[j];
		fail[i + 1] = tmp[j] == tmp[i] ? j + 1 : 0;
	}
}

bool KMP() {
	int now = 0;
	if (num[1] == 1) {
		REP(i, num[0]) {
			if (i < num[0] - 1) {
				if (cnt[0][i] >= cnt[1][0] && cnt[0][i + 1] - 1 >= tail[1]) return 1;
			}
			else if (i == num[0] - 1 && cnt[0][i] >= cnt[1][0] && tail[0] >= tail[1]) return 1;
		}
		return 0;
	}
	REPP(i, 1, num[0] - 1) {
		while (now && cnt[0][i] != tmp[now]) now = fail[now];
		if (cnt[0][i] == tmp[now]) now++;
		if (now + 1 == num[1]) {
			int start = i - num[1] + 1;
			if (i < num[0] - 1) {
				if (cnt[0][start] >= cnt[1][0] && cnt[0][i + 1] - 1 >= tail[1]) return 1;
			}
			else if (i == num[0] - 1 && cnt[0][start] >= cnt[1][0] && tail[0] >= tail[1]) return 1;
		}
	}
	return 0;
}

int main() {
	ios :: sync_with_stdio(0);
	//freopen("B.in", "r", stdin);
	cin >> s >> t;
	init();
	int tmp = presolve();
	if (tmp >= 0) {
		cout << tmp << endl;
		return 0;
	}
	else {
		if (num[1] > num[0]) {
			cout << -1 << endl;
			return 0;
		}
		getfail();
		//REP(i, 2) {
		//	cout << i << "****************" << endl;
		//	REP(j, num[i]) {
		//		cout << cnt[i][j] << ' ';
		//	}
		//	cout << endl;
		//}
		//cout << "tail" << endl;
		//REP(i, 2) {
		//	cout << tail[i] << ' ';
		//}
		//cout << endl;
		//cout << endl;
		//cout << "fail" << endl;
		//REP(i, num[1]) {
		//	cout << fail[i] << ' ';
		//}
		//cout << endl;
		int flag = 0, ans = -1;
		REP(i, 20) {
			if (flag) break;
			else {
				if (!KMP()) {
					REP(i, num[0]) {
						cnt[0][i] <<= 1;
					}
					tail[0] <<= 1;
				}
				else {
					flag = 1;
					ans = i;
				}
			}
		}
		cout << ans << endl;
	}

	return 0;
}

