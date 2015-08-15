#include <bits/stdc++.h>
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define MAXN  600
#define MAXM 3000
#define mem(a) memset(a, 0, sizeof(a))

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];
int num, V, E;
arrayN fir, vis, inD, d;
arrayM e, nxt, eU, eV, eW, c;
deque<int> deq;

void link(int u, int v, int w)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
}

int minuCircle()
{
	deq.clear();
	REPP(i, 1, V)
	{
		deq.push_back(i);
		vis[i] = 1;
		inD[i] = 1;
		d[i] = 0;
	}
	for (; !deq.empty();)
	{
		int tmp = deq.back();
		inD[tmp] = 0;
		deq.pop_back();
		for (int p = fir[tmp]; p; p = nxt[p])
			if (d[e[p]] > d[tmp] + c[p])
			{
				d[e[p]] = d[tmp] + c[p];
				if (!inD[e[p]])
				{
					inD[e[p]] = 1;
					vis[e[p]]++;
					if (vis[e[p]] >= V + 1) return 1;
					if (deq.empty() || d[e[p]] <= d[deq.back()]) deq.push_back(e[p]);
					else deq.push_front(e[p]);
				}
			}
	}
	return 0;
}

int check(int x)
{
	num = 0;
	mem(fir);
	REP(i, E)
		link(eU[i], eV[i], eW[i] - x);
	return !minuCircle();
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (; scanf("%d%d", &V, &E) != EOF; )
	{
		int lim = 1;
		REP(i, E)
		{
			scanf("%d%d%d", &eU[i], &eV[i], &eW[i]);
			lim = max(lim, eW[i] + 1);
		}
		{
			int l = 0, r = lim;
			for (; l < r;)
			{
				int mid = l + r + 1 >> 1;
				if (check(mid)) l = mid;
				else r = mid - 1;
			}
			if (l == 0) printf("No Solution\n");
			else if (l == lim) printf("Infinite\n");
			else printf("%d\n", l);
		}
	}
	return 0;
}

