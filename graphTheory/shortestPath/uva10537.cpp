#include <bits/stdc++.h>
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define MAXN 300
#define MAXM 10000
#define mem(a) memset(a, 0, sizeof(a))
#define LL long long

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];

LL d[MAXN];
int num, m, items;
char S, T;
arrayM e, nxt;
arrayN vis, inD, fir;
deque<int> deq;
void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num;
}

LL calcCost(int pos, LL dp)
{
	if (pos >= 'A' && pos <= 'Z')
	{
		if (dp % 19 == 0) return dp / 19;
		return dp / 19 + 1;
	}
	return 1;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int ca = 0;
	for (;;)
	{
		++ca;
		scanf("%d\n", &m);
		if (m < 0) break;
		num = 0;
		mem(fir);
		REP(i, m)
		{
			char u, v;
			scanf("%c %c\n", &u, &v);
			link(u, v);
			link(v, u);
		}
		scanf("%d %c %c\n", &items, &S, &T);
		{
			deq.clear();
			deq.push_back(T);
			mem(vis);
			d[T] = items;
			mem(inD);
			vis[T] = 1;
			for (; !deq.empty(); )
			{
				int tmp = deq.back();
				deq.pop_back();
				inD[tmp] = 0;
				for (int p = fir[tmp]; p; p = nxt[p])
				{
					LL cost = calcCost(tmp, d[tmp]);
					if (!vis[e[p]] || d[e[p]] > d[tmp] + cost)
					{
						vis[e[p]] = 1;
						d[e[p]] = d[tmp] + cost;
						if (!inD[e[p]])
						{
							inD[e[p]] = 1;
							if (deq.empty() || d[e[p]] < d[deq.back()]) deq.push_back(e[p]);
							else deq.push_front(e[p]);
						}
					}
				}
			}
			char now = S;
			printf("Case %d:\n", ca);
			printf("%lld\n", d[S]);
			for (;;)
			{
				printf("%c", now);
				if (now == T) {printf("\n"); break;}
				printf("-");
				int tmp = 125;
				for (int p = fir[now]; p; p = nxt[p])
					if (d[e[p]] + calcCost(e[p], d[e[p]]) == d[now])
						tmp = min(tmp, e[p]);
				now = tmp;
			}
		}
 	}
	return 0;
}
