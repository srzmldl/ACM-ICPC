#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 1234
#define MAXM 12345

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, cham, d, win, fail;
arrayM nxt, e, c;
int S, T, n, num, chamNum;
const int INF = 0x3f3f3f3f;
int a[30][30];

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}
bool bfs(int s)
{
	MST(d, 0x3f);
	d[s] = 0;
	queue<int> que;
	que.push(s);
	for (; !que.empty();)
	{
		int u = que.front();
		que.pop();
		for (int p = fir[u]; p; p = nxt[p])
			if (c[p] && d[e[p]] > d[u] + 1)
			{
				d[e[p]] = d[u] + 1;
				if (e[p] == T) return true;
				que.push(e[p]);
			}
	}
	return d[T] < d[0];
}

int dfs(int x, int low)
{
	if (x == T) return low;
	int flow = 0;
	for (int p = fir[x]; p; p = nxt[p])
		if (c[p] && d[e[p]] == d[x] + 1)
		{
			int tmp = dfs(e[p], min(low, c[p]));
			if (!tmp) d[e[p]] = d[0];
			c[p] -= tmp, c[p ^ 1] += tmp;
			flow += tmp, low -= tmp;
		}
	return flow; 
}

bool buildGraph(int x)
{
	S = n * n + n + 1;
	T = n * n + n + 2;
	num = 1;
	MST(fir, 0);
	int mark = win[x];
	REPP(i, 1, n)
		mark += a[x][i];
	REPP(i, 1, n)
		if (i != x)
		{
			if (mark < win[i]) return false;
			link(n * n + i, T, mark - win[i]);
			link(T, n * n + i, 0);
		}
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		if (i != x && j != x && a[i][j])
		{
			int u = S;
			int v = (i - 1) * n + j;
			link(u, v, a[i][j]);
			link(v, u, 0);
			link(v, n * n + i, INF);
			link(n * n + i, v, 0);
			link(v, n * n + j, INF);
			link(n * n + j, v, 0);
		}
	return true;
}

void judgeCham(int x)
{
	if (!buildGraph(x)) return;
	for (; bfs(S); dfs(S, INF));
	for (int p = fir[S]; p; p = nxt[p])
		if (c[p]) return ;
	cham[++chamNum] = x;
}

int main()
{
	freopen("la2531.in", "r", stdin);
	int task;
	scanf("%d", &task);
	REPP(ca, 1, task)
	{
		scanf("%d", &n);
		REPP(i, 1, n)
			scanf("%d%d", win + i, fail + i);
		REPP(i, 1, n)
			REPP(j, 1, n)
			scanf("%d", &a[i][j]);
		chamNum = 0;
		REPP(i, 1, n)
			judgeCham(i);
		REPP(i, 1, chamNum)
			printf("%d%c", cham[i], " \n"[i == chamNum]);
	}
	return 0;
}
