#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define MAXM 2100
#define MAXN 60

using namespace std;
const int oo = ~0U>>1;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, f, point, oneNum;
arrayM e, nxt, c, vis, pos;
int sTot, n, m, k, task, ans, S[10], T[10], limS, haveGood[MAXN], num, clk = 0, cnt[10][10], kk;
struct edge
{
    int u, v, w, id;
} ed[MAXM];

struct allState
{
    int S[10], T[10];
} allSt[10][10][15000];

int com(edge u, edge v)
{
	return u.w <v.w;
}

int getfa(int x)
{
	return x == f[x] ? x : (f[x] = getfa(f[x]));
}

void link(int u, int v, int w, int po)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num, c[num] = w;
	pos[num] = po;
}


int getOneNum1(int x)
{
	int cnt = 0;
	while (x) {
		cnt++;
		x &= x - 1;
	}
	return cnt;
}

int getOneNum(int x)
{
	return oneNum[x];
}

int dfs(int now, int fa, int tar)
{
    if (now == tar) return 0;
    for (int p = fir[now]; p; p = nxt[p])
		if (e[p] != fa)
		{
            int x = dfs(e[p], now, tar);
            if (x >= 0)
            {
				if (vis[pos[p]] != clk) x += c[p];
				vis[pos[p]] = clk;
				return x;
            }
		}
	return -1;
}

void solve()
{
	int pTot;
    int tmpAns = 0;
    REPP(i, 1, sTot)
    {
		pTot = getOneNum(S[i]) *2;
        int t1 = 0, t2 = pTot +1;

		REPP(i, 1, n)
		{
			f[i] = i;
			haveGood[i] = 0;
		}

        REP(j, k)
		{
			if (S[i] & (1 <<j))
			{
                point[++t1] = j +1;
                haveGood[j +1] = 1;
			}
			if (T[i] & (1 <<j))
			{
				point[--t2] = n - j;
				haveGood[n - j] = 1;
			}
		}

		num = 0;
        mem(fir);
		REPP(i, 1, m)
		{
			int u = ed[i].u, v = ed[i].v;
			int fu = getfa(u), fv = getfa(v);
            if (fu != fv)
            {
				f[fu] = fv;
				link(u, v, ed[i].w, ed[i].id);
				link(v, u, ed[i].w, ed[i].id);
				haveGood[fv] += haveGood[fu];
				if (haveGood[fv] == pTot) break;
            }
		}

		clk++;
		int tmp = 0;
        REPP(i, 1, pTot / 2)
        {
			tmp += dfs(point[i], 0, point[pTot - i +1]);
        }
        tmpAns += tmp;
        if (tmpAns >= ans) return ;

    }
    ans = min(ans, tmpAns);
}

void dfsT(int dep, int state)
{
	if (dep == sTot)
	{
        if (state == limS)
        {
            ++cnt[kk][sTot];
            int tmp = cnt[kk][sTot];
            REPP(i, 1, sTot)
            {
				allSt[kk][sTot][tmp].S[i] = S[i];
				allSt[kk][sTot][tmp].T[i] = T[i];
			}
        }
        return ;
	}
    int all = (~state) & limS;
	for (int sub = all; sub; sub = all & (sub - 1))
	{
		T[dep +1] = sub;
        if (getOneNum(S[dep +1]) != getOneNum(T[dep +1])) continue;
        dfsT(dep +1, state | sub);
	}


}



void dfsS(int dep, int state)
{
    if (dep == sTot)
    {
        if (state == (limS))
			dfsT(0, 0);
		return ;
	}
    int all = (~state) & limS;
	for (int sub = all; sub; sub = all & (sub - 1))
	{
		S[dep +1] = sub;
        dfsS(dep +1, state | sub);
	}

}

int get()
{
	char c;
	while (c = getchar(), (c < '0' || c > '9') &&(c != '-'));
	bool flag = (c == '-');
    if (flag) c = getchar();
    int x = 0;
    while (c >= '0' &&c <= '9')
    {
		x = x *10 +c - 48;
		c = getchar();
    }
    return flag ? -x : x;
}

int main()
{
	freopen("Bcheck.in", "r", stdin);
	freopen("E1.out", "w", stdout);
	REP(i, 32) oneNum[i] = getOneNum1(i);

	mem(cnt);
    for(kk = 1; kk <= 5; ++kk)
    {
		limS = (1 <<kk) - 1;
        for(sTot = 1; sTot <= kk; ++sTot)
        {
			dfsS(0, 0);
			//printf("%d\n", cnt[kk][sTot]);
		}
	}

    for (scanf("%d", &task); task; --task)
    {
		scanf("%d%d%d", &n, &m, &k);
        limS = (1 <<k) - 1;
        REPP(i, 1, m)
        {
			scanf("%d%d%d", &ed[i].u, &ed[i].v, &ed[i].w);
			//ed[i].u = get();
			//ed[i].v = get();
			//ed[i].w = get();
			ed[i].id = i;
		}
		sort(ed +1, ed +m +1, com);
		ans = oo;
		for(sTot = 1; sTot <= k; ++sTot)
		{
			REPP(i, 1, cnt[k][sTot])
			{
				REPP(j, 1, sTot)
				{
					S[j] = allSt[k][sTot][i].S[j];
					T[j] = allSt[k][sTot][i].T[j];
				}
				solve();
			}
		}
		if (ans == oo)
		 printf("No solution\n");
		else printf("%d\n", ans);
    }
	return 0;
}
