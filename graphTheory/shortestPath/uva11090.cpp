#include <bits/stdc++.h>
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MAXN 60
#define MAXM 10000

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

int num, n, m;
arrayN fir, vis, inD, f;
deque<int> deq;
arrayM e, nxt;
double c[MAXM], d[MAXM];
vector<int> slack;

void link(int u, int v, double w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

int topSort()
{
	mem(inD);
	REPP(i, 1, n)
		for (int p = fir[i]; p; p = nxt[p])
			++inD[e[p]];
	slack.clear();
	REPP(i, 1, n)
		if (!inD[i])
			slack.push_back(i);
	int cnt = 0;
	for (;!slack.empty();)
	{
		int tmp = slack.back();
		slack.pop_back();
		++cnt;
		for (int p = fir[tmp]; p; p = nxt[p])
		{
			--inD[e[p]];
			if (!inD[e[p]])
				slack.push_back(e[p]);
		}
	}
	return cnt == n;
}

int check(double x)
{
	deq.clear();
	REPP(i, 1, num) c[i] -= x;
	mem(vis);
	mem(inD);
	REPP(i, 1, n)
	{
		vis[i] = 1;
		inD[i] = 1;
		d[i] = 0;
		deq.push_back(i);
	}
	for (;!deq.empty();)
	{
		int tmp = deq.back();
		deq.pop_back();
		inD[tmp] = 0;
		for (int p = fir[tmp]; p; p = nxt[p])
			if (!vis[e[p]] || d[e[p]] > d[tmp] + c[p])
			{
				d[e[p]] = d[tmp] + c[p];
				if (!inD[e[p]])
				{
					inD[e[p]] = 1;
					vis[e[p]]++;
					if (vis[e[p]] >= n + 1) 
					{
						REPP(i, 1, num) c[i] += x;
						return 1;
					}
					if (deq.empty() || d[deq.back()] > d[e[p]]) deq.push_back(e[p]);
					else deq.push_front(e[p]);
				}
			}
	}
	REPP(i, 1, num) c[i] += x;
	return 0;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int task;
	scanf("%d", &task);
	for (int ca = 1; ca <= task; ++ca)
	{
		printf("Case #%d: ", ca);
		scanf("%d%d", &n, &m);
		num = 0;
		mem(fir);
		REP(i, m)
		{
			int u, v;
			double w;
			scanf("%d%d%lf", &u, &v, &w);
			link(u, v, w);
		}
		if (topSort()) printf("No cycle found.\n");
		else 
		{
			double l = 0, r = 1e7 + 1;
			int twoDivideLim = 100;
			REP(i, twoDivideLim)
			{
				double mid = (l + r) / 2.0;
				if (check(mid)) r = mid;
				else l = mid;
			}
			printf("%.2f\n", l);
		}
	}
	return 0;
}
