#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 1e5 + 5;
const double EPS = 1e-9;
vector<int> edge[N];
double dp[N];
bool vis[N];

int cmp(double x, double y) {
	if (fabs(x - y) < EPS) return 1;
	else return 0;
}

int main() {
	ios :: sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	REPP(i, 1, m) {
		int x, y;
		cin >> x >> y;
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	dp[n] = 0.0;
	vis[n] = 1;
	queue<int> q;
	q.push(n);

	while (q.size()) {
		int x = q.front();
		
		while (q.size() && cmp(q.front(), x)) {

		}

	}



	return 0;
}

