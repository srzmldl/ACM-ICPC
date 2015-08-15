#include <bits/stdc++.h>
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MAXN 4100000
#define MAXM 4100000

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

int ticTot, traTot, s, t, cityLim, num;
arrayN fir, inD;
int d[MAXN];
vector<int> vCity;
deque<int> deq;
struct prev
{int pos, e;} pre[MAXN];

struct tickit
{
	int cost, tot;
	int city[30];
} tic[30], tra, ticMid[30];
struct edge
{
	int e, next, c, pos;
} ed[MAXM];

void scatde()
{
	REP(i, ticTot)
		tic[i] = ticMid[i];
	vCity.clear();
	REP(i, ticTot)
		REP(j, tic[i].tot)
		vCity.push_back(tic[i].city[j]);
	REP(i, tra.tot)
		vCity.push_back(tra.city[i]);
	sort(vCity.begin(), vCity.end());
	vCity.resize(unique(vCity.begin(), vCity.end()) - vCity.begin());
	cityLim = vCity.size() + 2;
	REP(i, ticTot)
		REP(j, tic[i].tot)
		tic[i].city[j] = lower_bound(vCity.begin(), vCity.end(), tic[i].city[j]) - vCity.begin();
	REP(j, tra.tot)
		tra.city[j] = lower_bound(vCity.begin(), vCity.end(), tra.city[j]) - vCity.begin();
}

int trans2To1(int p1, int p0)
{
	return p1 * cityLim + p0;
}

void link(int u, int v, int pos, int w)
{
	ed[++num].e = v, ed[num].next = fir[u];
	fir[u] = num, ed[num].c = w, ed[num].pos = pos;
//	printf("%d %d %d\n", u, v, w);
}

void buildGraph()
{
	num = 0;
	mem(fir);
	s = trans2To1(0, cityLim - 1);
	t = trans2To1(1, cityLim - 1);

	REP(j, cityLim)
		if (j == tra.city[0])
			link(s, trans2To1(1, j), -1, 0);
	//	else link(s, trans2To1(0, j), -1, 0);

	link(trans2To1(tra.tot, tra.city[tra.tot - 1]), t, -1, 0);
	
	REPP(i, 0, tra.tot - 1)
		REP(j, cityLim)
	{
		int uSta = trans2To1(i, j);
		REP(k, ticTot)
			if (tic[k].city[0] == j)
			{
				int tmp = i;
				REPP(h, 1, tic[k].tot - 1)
				{
					if (tmp < tra.tot && (tra.city[tmp] == tic[k].city[h]))
						tmp++;
					int vSta = trans2To1(tmp, tic[k].city[h]);
					link(uSta, vSta, k, tic[k].cost);
				}
			}
	}
}

void spfa()
{
	
	deq.clear();
	deq.push_back(s);
	memset(d, 50, sizeof(d));
	//printf("%lld\n", d[0]);
	mem(inD);
	d[s] = 0;
	inD[s] = 1;
	for (; !deq.empty();)
	{
		int tmp = deq.back();
		deq.pop_back();
		inD[tmp] = 0;
		for (int p = fir[tmp]; p; p = ed[p].next)
			if (d[ed[p].e] > d[tmp] + ed[p].c)
			{
				pre[ed[p].e].pos = ed[p].pos;
				pre[ed[p].e].e = tmp;
				d[ed[p].e] = d[tmp] + ed[p].c;
				if (!inD[ed[p].e])
				{
					inD[ed[p].e] = 1;
					if (deq.empty() || d[ed[p].e] <= d[deq.back()])
						deq.push_back(ed[p].e);
					else deq.push_front(ed[p].e);
				}
			}
	}
}

int ans[MAXN];
void printAns()
{
	int tmp = t;
	int tot = 0;
	for (; tmp != s; tmp = pre[tmp].e)
		ans[++tot] = pre[tmp].pos;
	for (int i = tot; i; --i)
		if (ans[i] >= 0) printf(" %d", ans[i] + 1);
}

int main()
{
	freopen("la3561.in", "r", stdin);
	for (int ca = 1;; ++ca)
	{
		scanf("%d", &ticTot);
		if (!ticTot) break;
		REP(i, ticTot)
		{
			scanf("%d", &tic[i].cost);
			scanf("%d", &tic[i].tot);
			REP(j, tic[i].tot)
				scanf("%d", &tic[i].city[j]);
			ticMid[i] = tic[i];
		}
		scanf("%d", &traTot);
		REP(i, traTot)
		{
			scanf("%d", &tra.tot);
			REP(j, tra.tot)
				scanf("%d", &tra.city[j]);
			scatde();
			buildGraph();
			spfa();
			printf("Case %d, Trip %d: Cost = %d\n", ca, i + 1, d[t]);
			printf("  Tickets used:");
			printAns();
			printf("\n");
		}
		
	}
	return 0;
}
