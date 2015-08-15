#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 100005;
int path[N << 1], now = 1;
vector<int> edge[N];

void dfs(int x, int pre) {
	path[now++] = x;
	for (auto it: edge[x]) {
		if (it != pre) dfs(it, x);
	}
	path[now++] = x;
}


int main() {
	ios :: sync_with_stdio(0);

	int n;
	cin >> n;
	REPP(i, 2, n) {
		int x;
		cin >> x;
		edge[x].push_back(i);
		edge[i].push_back(x);
	}
	dfs(1, 0);
	REPP(i, 1, n) {
		cout << path[2 * i - 1] << endl;
	}


	return 0;
}

