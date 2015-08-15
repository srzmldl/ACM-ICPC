#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 112345
#define esp 1e-8

using namespace std;

struct node
{
    double A, B, rate; //A/B
    double x, y;
    double f;
}g[MAXN];

int lab[MAXN], a[MAXN];

int cmp(double x)
{
    if (x < -esp) return -1;
    if (x > esp) return 1;
    return 0;
}

int smaller(int u, int v)
{
    int tx = cmp(g[u].x - g[v].x);
    int ty = cmp(g[u].y - g[v].y);
    return tx < 0 || (tx == 0 && ty < 0);
}

void mergeSortX(int al, int ar, int bl, int br)
{
    int Na = 0;
    for (int i = al; i <= ar; ++i)
    {
        while (bl <= br && smaller(lab[bl], lab[i]))
            a[++Na] = lab[bl++];
        a[++Na] = lab[i];
    }
    for (; bl <= br; ++bl)
        a[++Na] = lab[bl];
    for (int i = 1; i <= Na; ++i)
        lab[al + i - 1] = a[i];
}


double cross(int A, int B, int C)
{
    return (g[B].x - g[A].x) * (g[C].y - g[B].y) - (g[B].y - g[A].y) * (g[C].x - g[B].x);
}

double comRate(int A, int B, int C)
{
    return (g[B].y - g[A].y) * g[C].B + g[C].A * (g[B].x - g[A].x);
}

void getRightPartF(int al, int ar, int bl, int br)
{
    int Na = 0;
    double lim = 0;
    for (int i = al; i <= ar; ++i)
    {
        lim = max(lim, g[lab[i]].f);
        while (Na >= 2 && cmp(cross(a[Na - 1], a[Na], lab[i])) >= 0)
            --Na;
        a[++Na] = lab[i];
    }
    int La = 1;
    for (int i = bl; i <= br; ++i)
    {
        int p = lab[i];
        g[p].f = max(g[p].f, lim);
        for (; La + 1 <= Na && cmp(comRate(a[La], a[La + 1], p)) >= 0; ++La);
        g[p].f = max(g[p].f, g[a[La]].x * g[p].A + g[a[La]].y * g[p].B);
    }
}

void solve(int l, int r)
{
    if (l == r)
    {
        int p = lab[l];
        //g[p].f = max(g[p].f, g[p - 1].f);
        g[p].x *= g[p].f;
        g[p].y *= g[p].f;
        return ;
    }
    int Na = r - l + 1;
    int upLim = 0, downLim = MAXN;
    for (int i = l; i <= r; ++i)
    {
        upLim = max(upLim, lab[i]);
        downLim = min(downLim, lab[i]);
    }
    int midLim = (upLim + downLim) >> 1;
    int pLow = 0;
    for (int i = l; i <= r; ++i)
        if (lab[i] <= midLim)
            a[++pLow] = lab[i];
    int pHigh = pLow;
    for (int i = l; i <= r; ++i)
        if (lab[i] > midLim)
            a[++pHigh] = lab[i];
    for (int i = 1; i <= Na; ++i)
        lab[i + l - 1] = a[i];
    pLow += l - 1;
    solve(l, pLow);
    getRightPartF(l, pLow, pLow + 1, r);
    solve(pLow + 1, r);
    mergeSortX(l, pLow, pLow + 1, r);
}

int com(int u, int v)
{
    node tu = g[u];
    node tv = g[v];
    return tu.A * tv.B < tv.A * tu.B;
}

int main()
{
    //  freopen("cash4.in", "r", stdin);
    int N, S;
    scanf("%d%d", &N, &S);
    for (int i = 1; i <= N; ++i)
    {
        scanf("%lf%lf%lf", &g[i].A, &g[i].B, &g[i].rate);
        g[i].y = 1.0 / (g[i].B + g[i].A * g[i].rate);
        g[i].x = g[i].y * g[i].rate;
        g[i].f = S;
        lab[i] = i;
    }
    g[1].f = S;
    sort(lab + 1, lab + N + 1, com);
    solve(1, N);
    double ans = 0;
    for (int i = 1; i <= N; ++i)
        ans = max(ans, g[i].f);
    printf("%.3f\n", ans);
    return 0;
}
