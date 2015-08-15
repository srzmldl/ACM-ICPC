#include <bits/stdc++.h>
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define LL long long
#define MAXN 110
#define MAXM 2200

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

int num, n, m, L;
LL d[MAXN], ans[MAXM];
arrayN fir, vis, inQ, prev;
arrayM e, nxt, c, ok;
deque<int> que;
vector<int> slack;

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

void spfa(int s)
{
		que.clear();
		que.push_back(s);
		mem(vis);
		mem(inQ);
		vis[s] = 1;
		prev[s] = 0;
		d[s] = 0;
		for (; !que.empty();)
		{
			int tmp = que.back();
			inQ[tmp] = 0;
			que.pop_back();
			for (int p = fir[tmp]; p; p = nxt[p])
				if (!ok[p >> 1])
					if (!vis[e[p]] || d[e[p]] > d[tmp] + c[p])
					{
						d[e[p]] = d[tmp] + c[p];
						prev[e[p]] = p >> 1;
						vis[e[p]] = 1;
						if (!inQ[e[p]])
						{
							inQ[e[p]] = 1;
							if (que.empty() || d[e[p]] <= d[que.back()]) que.push_back(e[p]);
							else que.push_front(e[p]);
						}
					}
		}
		REPP(i, 1, n)
			if (!vis[i]) d[i] = L;
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (; scanf("%d%d%d", &n, &m, &L) != EOF;)
	{
		num = 1;
		mem(fir);
		REP(i, m)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			link(u, v, w);
			link(v, u, w);
		}
		LL c0 = 0;
		mem(ans);
		mem(ok);
		REPP(i, 1, n)
		{
			spfa(i);
			LL addThis = 0;
			REPP(j, 1, n)
				addThis += 1ll * d[j];
			c0 += addThis;
			slack.clear();
			REPP(j, 1, n)
				if (j != i && vis[j])
					slack.push_back(prev[j]);
			for (;!slack.empty(); slack.pop_back())
			{
				ok[slack.back()] = 1;
				spfa(i);
				LL mid = 0;
				REPP(j, 1, n)
					mid += 1ll * d[j];
				ans[slack.back()] += mid - addThis;
				ok[slack.back()] = 0;
			}
		}
		LL cp = 0;
		REPP(i, 1, m)
			cp = max(cp, c0 + ans[i]);
		cout << c0 << ' ' << cp << endl;
	}
	return 0;
}
