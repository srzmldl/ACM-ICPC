#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 15;
const int INF = 0x3f3f3f3f;

char mp[N][N];
int id[N][N], val[N][N], blk, sx, sy, tot, n;
int dp[100][1 << 12], dep[N][N], dis[N][N][N][N], d[100][100];
bool vis[100][1 << 12], use[N][N];
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

bool good(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void expand(int x, int y) {
	queue<int> q;
	use[x][y] = 1;
	id[x][y] = blk;
	q.push(x), q.push(y);

	while (q.size()) {
		x = q.front(); q.pop();
		y = q.front(); q.pop();
		REP(k, 4) {
			int tx = x + dx[k], ty = y + dy[k];
			if (good(tx, ty) && !use[tx][ty] && mp[tx][ty] == '@') {
				id[tx][ty] = blk;
				use[tx][ty] = 1;
				q.push(tx), q.push(ty);
			}
		}
	}
}

void getmp() {
	MST(d, 0x3f);
	REPP(x, 1, n) {
		REPP(y, 1, n) {
			REPP(i, 1, n) {
				REPP(j, 1, n) {
					int &tmp = d[id[x][y]][id[i][j]];
					tmp = min(tmp, dis[x][y][i][j]);
				}
			}
		}
	}
}	

void bfs(int sx, int sy) {
	MST(dep, 0x3f);
	queue<int> q;
	int x = sx, y = sy, tx, ty;
	dep[x][y] = 0;
	use[x][y] = 1;
	q.push(x), q.push(y);

	while (q.size()) {
		x = q.front(), q.pop();
		y = q.front(), q.pop();
		REP(k, 4) {
			tx = x + dx[k], ty = y + dy[k];
			if (good(tx, ty) && mp[tx][ty] != 'X') {
				if (dep[tx][ty] > dep[x][y] + val[x][y]) {
					dep[tx][ty] = dep[x][y] + val[x][y];
					if (!use[tx][ty]) {
						q.push(tx), q.push(ty);
						use[tx][ty] = 1;
					}
				}
			}
		}
		use[x][y] = 0;
	}

	REPP(i, 1, n) REPP(j, 1, n) {
		dis[sx][sy][i][j] = dep[i][j];
	}
}

queue<int> q;

void spfa() {
	while (q.size()) {
		int node = q.front(); q.pop();
		int st = q.front(); q.pop();
		REP(i, blk) if (d[node][i] < INF){
			if (dp[i][st] > dp[node][st] + d[node][i]) {
				dp[i][st] = dp[node][st] + d[node][i];
				if (!vis[i][st]) {
					q.push(i);
					q.push(st);
				}
			}
		}
		vis[node][st] = 0;
	}
}

int Steiner_Tree() {
	REPP(i, 1, n) {
		REPP(j, 1, n) {
			if (id[i][j] < tot) {
				int tmp = id[i][j];
				dp[tmp][1 << tmp] = 0;
				q.push(tmp), q.push(1 << tmp);
			}
		}
	}

	REP(st, (1 << tot)) if (st) {
		REPP(i, 1, n) {
			REPP(j, 1, n) if (mp[i][j] != 'X') {
				int all = st, node = id[i][j];
				int &tmp = dp[node][st];
				for (int sub = all; sub; sub = all & (sub - 1)) {
					if (dp[node][sub] + dp[node][all ^ sub] < tmp) {
						tmp = dp[node][sub] + dp[node][all ^ sub];
						if (!vis[node][st]) {
							q.push(node), q.push(st);
							vis[node][st] = 1;
						}
					}
				}	
			}
		}
		spfa();
	}

	return dp[0][(1 << tot) - 1];
}

int main() {
	freopen("zoj3837.txt", "r", stdin);
	ios :: sync_with_stdio(0);
	
	int t;
	cin >> t;
	while (t--) {
		cin >> n;
		blk = 0, sx = sy = (n + 1) >> 1;

		MST(id, -1), MST(val, 0), MST(dp, 0x3f);
		MST(mp, 0), MST(vis, 0), MST(use, 0);

		//get id
		REPP(i, 1, n) {
			cin >> mp[i] + 1;
		}
		expand(sx, sy);
		blk++;

		REPP(i, 1, n) {
			REPP(j, 1, n) {
				if (mp[i][j] == '@' && !use[i][j]) {
					expand(i, j);
					blk++;
				}
			}
 		}
 		tot = blk;

 		REPP(i, 1, n) {
 			REPP(j, 1, n) {
 				if (id[i][j] < 0 && mp[i][j] != '@' && mp[i][j] != 'v') {
 					id[i][j] = blk++;
 				}
 			}
 		}

 		//get val
 		REPP(i, 1, n) {
 			REPP(j, 1, n) {
 				if (mp[i][j] == '@' || mp[i][j] == 'v') {
 					val[i][j] = 0;
 				}
 				else if (mp[i][j] == 'X') {
 					val[i][j] = INF;
 				}
 				else if (mp[i][j] >= '0' && mp[i][j] <= '9') {
 					val[i][j] = mp[i][j] - '0';
 				}
 				else {
 					val[i][j] = INF;
 				}
 			}
 		}

 		
 		//get dis
 		MST(use, 0), MST(dis, 0x3f);
 		REPP(i, 1, n) {
 			REPP(j, 1, n) {
 				bfs(i, j);
 			}
 		}
 		getmp();

 		int bad = 0;
 		REP(i, tot) {
 			if (d[0][i] >= INF) {
 				bad = 1;
 				break;
 			}
 		}
 		if (bad) {
 			cout << "-1" << endl;
 		}
 		else {
 			cout << Steiner_Tree() << endl;
 		}
	}

	return 0;
}
