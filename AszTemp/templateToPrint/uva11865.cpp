#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 66
#define MAXM 11234

using namespace std;
const int oo = ~0U>>1;
typedef int arrayN[MAXN], arrayM[MAXM];

int N, M, C;
arrayN vis, minW, belong, pre;

struct edge
{
	int u, v, b, c;
	edge(int u1 = 0, int v1 = 0, int b1 = 0, int c1 = 0)
		{
			u = u1, v = v1, b = b1,  c = c1;
		}
}edOri[MAXM], ed[MAXM];

int zhuLiu(int bLowLim)
{
	int root = 0, tot = N, ntot;
	int ans = 0;
	REP(i, M) ed[i] = edOri[i];
	for (;;)
	{
		REP(i, tot) minW[i] = oo, vis[i] = -1, belong[i] = -1;
		REP(i, M)
		{
			if (ed[i].u == ed[i].v || ed[i].b < bLowLim) continue;
			if (ed[i].c < minW[ed[i].v])
			{
				minW[ed[i].v] = ed[i].c;
				pre[ed[i].v] = ed[i].u;
			}
		}
		
		pre[root] = -1;
		minW[root] = 0;
		REP(i, tot) 
			if(minW[i] >= oo) return oo;
			else ans += minW[i];
		ntot = 0;
		REP(i, tot)
			if (vis[i] == -1)
			{
			
				int h1 = i;
				for (; vis[h1] == -1; h1 = pre[h1])
				{
					vis[h1] = i;
					if (h1 == root) break;
				}
				if (h1 == root || vis[h1] != i) continue;
				int h2 = h1;
				for (h2 = pre[h1]; h2 != h1; h2 = pre[h2])
					belong[h2] = ntot;
				belong[h1] = ntot++;
			}
		REP(i, tot) if (belong[i] == -1) belong[i] = ntot++;
		REP(i, M)
		{
			ed[i].c -= minW[ed[i].v];
			ed[i].u = belong[ed[i].u];
			ed[i].v = belong[ed[i].v];
		}
		if (tot == ntot) return ans;
		tot = ntot;
		root = belong[root];
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int task;
	for (scanf("%d", &task); task; --task)
	{
		int L = 1, R = 1;
		scanf("%d%d%d", &N, &M, &C);
		REP(i, M)
		{
			int u, v, b, c;
			scanf("%d%d%d%d", &u, &v, &b, &c);
			edOri[i] = edge(u, v, b, c);
			R = max(R, b);
		}
		L = 0;
		for (; L < R; )
		{
			int mid = (L + R + 1) >> 1;
			if (zhuLiu(mid) > C)
				R = mid - 1;
			else L = mid;
		}
		if (L == 0) printf("streaming not possible.\n");
		else printf("%d kbps\n", L); 
	}
	return 0;
}
