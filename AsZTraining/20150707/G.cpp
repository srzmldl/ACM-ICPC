#include <bits/stdc++.h>

#define LL long long
#define REP(i, a) REPP(i, 0, (a) - 1)
#define REPP(i, a, b) for (int i = int(a); i <= int(b); i++)
#define MST(a, b) memset(a, b, sizeof(a))
#define PII pair<int, int>

using namespace std;

const int N = 1e5 + 5;

int a[N], d[N], tmp[N], n, m;
set<PII, greater<PII>, allocator<vector<PII> > > maxi;
set<PII> mini;
//priority_queue<PII, vector<PII>, greater<PII> > q;
vector<int> edge[N];

int degree[N], deg[N];

bool check(int x) {
	REPP(i, 1, n) tmp[i] = n - (d[i] + x) + 1;
	REPP(i, 1, n) deg[i] = degree[i];
	maxi.clear(), mini.clear();
	int now = 1;
	REPP(i, 1, n) if(deg[i] == 0) {
		mini.insert({tmp[i], i});
	}
	while (mini.size()) {
		x = mini.begin() -> first;
		if (x > now) return 0;
		else {
			int x, y;
			auto it = mini.begin();
			tie(x, y) = *it;
			mini.erase(it);
			a[now++] = y;
			for (auto &z: edge[y]) {
				deg[z]--;
				if (deg[z] == 0) {
					mini.insert({tmp[z], z});
				}
			}
		}
	}
	return 1;
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("grand.in", "r", stdin);
	freopen("grand.out", "w", stdout);
	while (scanf("%d", &n), n) {
		REPP(i, 1, n) scanf("%d", d + i);
		REPP(i, 1, n) edge[i].clear();
		REPP(i, 1, n) degree[i] = 0;
		scanf("%d", &m);
		REPP(i, 1, m) {
			int x, y;
			scanf("%d%d", &x, &y);
			edge[y].push_back(x);
			degree[x]++;
		}
		int l = -1, r = N;
		while (l + 1 < r) {
			int mid = (l + r) >> 1;
			if (check(mid)) r = mid;
			else l = mid;
		}
		check(r);
		printf("%d\n", r);
		//REPP(i, 1, n) {
        //		printf("%d%c", a[i], " \n"[i == n]);
		//}
        for (int i = n; i >= 1; --i)
            printf("%d%c", a[i], " \n"[i == 1]);
	}

	return 0;
}
