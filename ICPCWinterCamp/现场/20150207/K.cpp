#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 4e4 + 5;
int vis[N], now;

long long calc(int a, int b) {
	return 1LL * (a + b) * (b - a + 1) / 2;
}

void go(int n, int k, int s) {
	REPP(i, 1, k) vis[i] = now;
	long long num = calc(1, k);
	while (num != s) {
		if (num - k + n >= s) {
			int tmp = s - (num - k);
			vis[tmp] = now;
			vis[k] = 0;
			break;
		}
		else {
			vis[k] = 0;
			vis[n] = now;
			num += n - k;
			k--;
			n--;
		}
	}
}

int main() {
	ios :: sync_with_stdio(0);

	int t;
	cin >> t;
	REPP(i, 1, t) {
		int n, k, s;
		cin >> n >> s >> k;
		if (calc(n - k + 1, n) < s || calc(1, k) > s) {
			cout << "NO" << endl;
		}
		else {
			now++;
			go(n, k, s);
			cout << "YES" << endl;
			REPP(i, 1, n) {
				if (vis[i] == now) {
					cout << '1';
				}
				else {
					cout << '0';
				}
			}
			cout << endl;
		}
	}


	return 0;
}

