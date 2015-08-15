#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (int) (b); ++i)
#define MAXN 61234
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;
typedef int arrayN[MAXN];

arrayN fir, nxt, e, dam, len, size, vis, maxLen;
int num, n, m, ans;

struct edge
{
	int dam, len;
	edge(int dam = 0, int len = 0) : dam(dam), len(len) {};
};

vector <edge> rootVec, tmpVec, midVec;

void link(int u, int v, int D, int L)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, dam[num] = D, len[num] = L;
}

int dfsSize(int x, int fa)
{
	size[x] = 1;
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa && !vis[e[p]])
			size[x] += dfsSize(e[p], x);
	return size[x];
}

int dfsRoot(int x, int fa, int sizeTot)
{
	int tmp = sizeTot - size[x];
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa && !vis[e[p]])
		{
			int root = dfsRoot(e[p], x, sizeTot);
			if (root > 0) return root;
			tmp = max(tmp, size[e[p]]);
		}
	if (tmp <= sizeTot / 2) return x;
	return -1;
}

void dfsVec(int x, int fa, int D, int L)
{
	tmpVec.push_back(edge(D, L));
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa && !vis[e[p]])
			dfsVec(e[p], x, D + dam[p], L + len[p]);
}

int com(edge A, edge B)
{
	return A.dam < B.dam;
}

void solve(int x)
{
//注意此处root极容易打错成x
	int root = dfsRoot(x, x, dfsSize(x, x));
	vis[root] = 1;
	rootVec.clear();
	rootVec.push_back(edge(0, 0));
	for (int p = fir[root]; p; p = nxt[p])
		if (!vis[e[p]])
		{
			tmpVec.clear();
			dfsVec(e[p], root, dam[p], len[p]);
			sort(tmpVec.begin(), tmpVec.end(), com);
			maxLen[0] = rootVec[0].len;
			REPP(i, 1, (rootVec.size() - 1))
				maxLen[i] = max(maxLen[i - 1], rootVec[i].len);
			int j = 0;
			for (int i = tmpVec.size() - 1; i >= 0; --i)
			{
				for (; j < rootVec.size() && rootVec[j].dam + tmpVec[i].dam <= m; ++j);
				if (j == 0) continue;
				ans = max(ans, maxLen[j - 1] + tmpVec[i].len);
			}
			midVec = rootVec;
			rootVec.clear();
			j = 0;
			for (int i = 0; i < midVec.size(); ++i)
			{
				for (; j < tmpVec.size() && tmpVec[j].dam <=midVec[i].dam; ++j)
					rootVec.push_back(tmpVec[j]);
				rootVec.push_back(midVec[i]);
			}
			for (; j < tmpVec.size(); ++j)
				rootVec.push_back(tmpVec[j]);
		}
	for (int p = fir[root]; p; p = nxt[p])
		if (!vis[e[p]]) solve(e[p]);
	vis[root] = 0;
}

int main()
{
	freopen("la4409.in", "r", stdin);
	freopen("out2.txt", "w", stdout);
	int task;
	scanf("%d", &task);
	REPP(T, 1, task)
	{
		scanf("%d%d", &n, &m);
		num = 0;
		MST(fir, 0);
		ans = 0;
		REP(i, n - 1)
		{
			int u, v, D, L;
			scanf("%d%d%d%d", &u, &v, &D, &L);
			link(u, v, D, L);
			link(v, u, D, L);
		}
		MST(vis, 0);
		solve(1);
		printf("Case %d: %d\n", T, ans);
	}
	return 0;
}
