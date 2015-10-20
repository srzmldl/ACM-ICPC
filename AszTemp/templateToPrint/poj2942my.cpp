typedef int arrayN[MAXN];

int n, m, top, tot, next[MAXN * MAXN], e[MAXN * MAXN], num;
VP slack, g[MAXN];
arrayN low, dfn, fir, ed[MAXN], color, isAns, belong;

void tarjan(int x, int fa)
{
    low[x] = dfn[x] = ++top;
    REPP(p, 1, n)
        if (!ed[x][p] && x != p && p != fa && dfn[p] <= dfn[x])
        {
            slack.PB(MP(x, p));
            if (!dfn[p])
            {
                tarjan(p, x);
                low[x] = min(low[x], low[p]);
                if (low[p] >= dfn[x])
                {
                    g[++tot].clear();
                    for (;;)
                    {
                        int u = slack.back().FI;
                        int v = slack.back().SE;
                        g[tot].PB(slack.back());
                        slack.pop_back();
                        if (u == x && v == p) break;
                    }
                }
            } else low[x] = min(low[x], dfn[p]);
        }
}

bool dye(int x, int co)
{
    color[x] = co;
    for (int p = fir[x]; p; p = next[p])
	if (!color[e[p]])
    if (!dye(e[p], 3 - co)) return false; else ;
	else if (color[x] + color[e[p]] != 3) return false;
    return true;
}

void link(int u, int v)
{
    e[++num] = v, next[num] = fir[u];
    fir[u] = num;
}

int main()
{
	int x, y, z, ca = 1;
	for (; RII(n, m); )
	{
	    mem(ed);
	    mem(dfn);
	    top = tot = 0;
	    if (n + m == 0) break;
	    REP(i, m)
	    {
            int u, v;
            RII(u, v);
            ed[u][v] = ed[v][u] = 1;
	    }
	    REPP(i, 1, n)
            if (!dfn[i])
		    tarjan(i, 0);
	    mem(isAns);
	    REPP(i, 1, tot)
	    {
            mem(color);
            mem(belong);
            mem(fir);
            num = 0;
            int sta = 0;
            for (; !g[i].empty(); g[i].pop_back())
            {
                belong[g[i].back().FI] = belong[g[i].back().SE] = i;
                link(sta = g[i].back().FI, g[i].back().SE);
                link(sta = g[i].back().SE, g[i].back().FI);
            }
            if (!dye(sta, 1))
		    REPP(j, 1, n)
                if (belong[j] == i)
			    isAns[j] = 1;
	    }
	    int ans = 0;
	    REPP(i, 1, n)
            if (!isAns[i]) ans++;
	    PI(ans);
	}
	return 0;
}