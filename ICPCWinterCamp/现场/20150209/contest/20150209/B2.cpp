#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int mp[6][6];
string tmp[6];
string s;
map<char, int> g;

string op = "LUDR";
vector<int> ans;

void goleft(int r) {
	int tmp[6];
	REP(i, 6) tmp[i] = mp[r][i];
	REP(i, 6) {
		mp[r][i] = tmp[(i + 1) % 6];
	}
	ans.push_back(r);
	ans.push_back(0);
}

void goright(int r) {
	int tmp[6];
	REP(i, 6) tmp[i] = mp[r][i];
	REP(i, 6) {
		mp[r][i] = tmp[(i + 5) % 6];
	}
	ans.push_back(r);
	ans.push_back(3);
}

void goup(int c) {
	int tmp[6];
	REP(i, 6) tmp[i] = mp[i][c];
	REP(i, 6) {
		mp[i][c] = tmp[(i + 1) % 6];
	}
	ans.push_back(c);
	ans.push_back(1);
}

void godown(int c) {
	int tmp[6];
	REP(i, 6) tmp[i] = mp[i][c];
	REP(i, 6) {
		mp[i][c] = tmp[(i + 5) % 6];
	}
	ans.push_back(c);
	ans.push_back(2);
}

void swaprow(int x, int y) {
	int y1 = (y + 1) % 6;
	int x1 = (x + 1) % 6;
	godown(y1);
	goright(x);
	goup(y1);
	goleft(x);
	godown(y1);
	goright(x1);
	REP(i, 4) goup(y1);
	goleft(x1);
	godown(y1);
	goright(x1);
	godown(y1);
	goleft(x1);
	godown(y1);
	goright(x1);
	godown(y1);
	goleft(x1);
}

void swapcol(int x, int y) {
	int x1 = (x + 1) % 6;
	int y1 = (y + 5) % 6;
	goleft(x1);
	godown(y);
	goright(x1);
	goup(y);
	goleft(x1);
	godown(y1);
	REP(i, 4) goright(x1);
	goup(y1);
	goleft(x1);
	godown(y1);
	goleft(x1);
	goup(y1);
	goleft(x1);
	godown(y1);
	goleft(x1);
	goup(y1);
}

void find(int now, int &x, int &y) {
	REP(i, 6) {
		REP(j, 6) {
			if (mp[i][j] == now) {
				x = i, y = j;
				return ;
			}
		}
	}
}

void recover(int x, int y) {
	int num = 6 * x + y;
	if (mp[x][y] == num) {
		return ;
	}
	else {
		int nx, ny;
		find(num, nx, ny);
		if (ny != y) {
			if (ny > y) {
				while (ny > y) {
					swaprow(nx, ny - 1);
					ny--;
				}
			}
			else {
				while (ny < y) {
					swaprow(nx, ny);
					ny++;
				}
			}
		}
		if (nx != x) {
			while (nx > x) {
				swapcol(nx - 1, y);
				nx--;
			}
		}
	}
}

void solve() {
	REP(i, 6) {
		REP(j, 6) {
			recover(i, j);
		}
	}
}

int main() {
	ios :: sync_with_stdio(0);
	//freopen("B.in", "r", stdin);
	
	REP(i, 26) {
		s += 'a' + i;
		g[s[i]] = i;
	}
	REP(i, 10) {
		g[i + '0'] = i + 26;
	}
	REP(i, 6) {
		cin >> tmp[i];
	}
	REP(i, 6) REP(j, 6) {
		mp[i][j] = g[tmp[i][j]];
	}
	//REP(i, 6) {
	//	REP(j, 6) {
	//		cout << mp[i][j] << '\t';
	//	}
	//	cout << endl;
	//}
	solve();
	for (int i = 0; i < (int) ans.size(); i += 2) {
		int x = ans[i], y = ans[i + 1];
		cout << x << ' ' << op[3 - y] << ' ' << 1 << endl;
	}
	//REP(i, 6) {
	//	REP(j, 6) {
	//		cout << mp[i][j] << '\t';
	//	}
	//	cout << endl;
	//}

	return 0;
}
