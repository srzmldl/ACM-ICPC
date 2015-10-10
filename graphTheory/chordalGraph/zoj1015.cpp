#include <bits/stdc++.h>
#define MAXN 1123
#define MAXM 2123456

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir, firMcs, nxtMcs, mcsSeq, l;
arrayN vis, r, cnt, preMcs, lab;
arrayM nxt, e;
int num, flag[MAXN][MAXN];
int mx; // max

void link(int u, int v)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

void delMcs(int pos, int pt)
{
    if (nxtMcs[pt] == pt)
    {
        r[l[pos]] = r[pos];
        l[r[pos]] = l[pos];
        if (pos == mx) mx = l[mx];
        firMcs[pos] = 0;
        return ;
    }
    preMcs[nxtMcs[pt]] = preMcs[pt];
    nxtMcs[preMcs[pt]] = nxtMcs[pt];
    if (firMcs[pos] == pt)
        firMcs[pos] = nxtMcs[pt];
}

void insMcs(int pos, int pt)
{
    if (firMcs[pos])
    {
        int tmp = firMcs[pos];
        nxtMcs[pt] = tmp;
        preMcs[pt] = preMcs[tmp];
        nxtMcs[preMcs[pt]] = pt;
        preMcs[nxtMcs[pt]] = pt;
        return;
    }
    preMcs[pt] = nxtMcs[pt] = firMcs[pos] = pt;
    if (firMcs[pos - 1]) //easy wrong
    {
        l[pos] = pos - 1;
        r[pos] = r[pos - 1];
    } else
    {
        if (l[pos - 1] == pos - 1)
            l[pos] = r[pos] = pos;
        else
        {
            l[pos] = l[pos - 1];
            r[pos] = r[pos - 1];
        }
    }
    r[l[pos]] = l[r[pos]] = pos;
    if (pos > mx) mx = pos;
}

void getMcsSeq(int n, int m)
{
    mx = 0;
    l[0] = 0, r[0] = 0;
    memset(firMcs, 0, sizeof(firMcs));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; ++i)
    {
        nxtMcs[i] = i + 1;
        preMcs[i] = i - 1;
    }
    nxtMcs[n] = 1, preMcs[1] = n;
    firMcs[0] = 1;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= n; ++i)
    {
        int tmp = (mcsSeq[i] = firMcs[mx]);
        delMcs(cnt[tmp], tmp);
        vis[tmp] = 1;
        for (int p = fir[tmp]; p; p = nxt[p])
            if (!vis[e[p]])
            {
                delMcs(cnt[e[p]], e[p]);
                ++cnt[e[p]];
                insMcs(cnt[e[p]], e[p]);
            }
    }
}

int checkMcs(int n)
{
    for (int i = 1; i <= n; ++i)
        lab[mcsSeq[i]] = i;
    memset(vis, 0, sizeof(vis));
    int now = 0;
    for (int i = 1; i <= n; ++i)
    {
        ++now;
        int pt = mcsSeq[i], cnt = 0, bgst = 0;
        for (int p = fir[pt]; p; p = nxt[p])
            if (lab[e[p]] < i)
            {
                vis[e[p]] = now;
                ++cnt;
                if (lab[e[p]] > bgst)
                    bgst = e[p];
            }
        if (bgst == 0) continue;
        for (int p = fir[bgst]; p; p = nxt[p])
        {
            if (lab[e[p]] < i && vis[e[p]] == now)
                --cnt;
        }
        if (cnt > 1) return 0;
    }
    return 1;
}

int main()
{
    //  freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    for (;;)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        if (n + m == 0) break;
        num = 0;
        memset(fir, 0, sizeof(fir));
        memset(flag, 0, sizeof(flag));
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (flag[u][v] || u == v) continue;
            link(u, v);
            link(v, u);
            flag[u][v] = flag[v][u] = 1;
        }
        getMcsSeq(n, m);
        if (checkMcs(n)) printf("Perfect\n\n");
        else printf("Imperfect\n\n");
    }
    return 0;
}
