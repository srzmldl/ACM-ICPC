#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define mem(a, b) memset((a), (b), sizeof(a))
#define MAXN 2100000
#define MAXM 8500000

using namespace std;
typedef int arrayN[MAXN], arrayM[MAXM];


int n, m, s, t, num;
arrayN fir, inD;
long long d[MAXN];
arrayM e, nxt, c;
int deq[MAXM * 5];

int getOdd(int x, int y)
{
    if (x == 0 || y == m) return s;
    if (x == n || y == 0) return t;
    return 2 * ((m - 1) * (x - 1) + y) - 1;
}

int getEven(int x, int y)
{
    if (x == 0 || y == m) return s;
    if (x == n || y == 0) return t;
    return 2 * ((m - 1) * (x - 1) + y);
}

void link(int u, int v, int w)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num, c[num] = w;
}

void spfa()
{
    mem(d, 0x3f);
    int l = 1, r = 1;
    deq[l] = s;
    d[s] = 0;
    mem(inD, 0);
    inD[s] = 1;
    for (; l <= r;)
    {
        int tmp = deq[l];
        ++l;
        inD[tmp] = 0;
        for (int p = fir[tmp]; p ;p = nxt[p])
            if (d[e[p]] > d[tmp] +c[p])
            {
                d[e[p]] = d[tmp] +c[p];
                if (!inD[e[p]])
                {
                    inD[e[p]] = 1;
                    deq[++r] = e[p];
                    if (d[deq[l]] >d[deq[r]])
                        swap(deq[l], deq[r]);
                }
            }
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int ca = 1;
    for (;;++ca)
    {
        scanf("%d%d", &n, &m);
        if (n + m == 0) break;
        num = 0;
        mem(fir, 0);
        s = 0;
        t = 2 * n * m +1;
        REPP(i, 1, n)
            REPP(j, 1, m - 1)
            {
                int fee;
                scanf("%d", &fee);
                int u = getOdd(i - 1, j);
                int v = getEven(i, j);
                link(u, v, fee);
                link(v, u, fee);
            }

        REPP(i, 1, n - 1)
            REPP(j, 1, m)
            {
                int fee;
                scanf("%d", &fee);
                int u = getEven(i, j - 1);
                int v = getOdd(i, j);
                link(u, v, fee);
                link(v, u, fee);
            }

          REPP(i, 1, n - 1)
            REPP(j, 1, m - 1)
            {
                int fee;
                scanf("%d", &fee);
                int u = getOdd(i, j);
                int v = getEven(i, j);
                link(u, v, fee);
                link(v, u, fee);
            }
        spfa();
        printf("Case %d: Minimum = %lld\n", ca, d[t]);
    }
    return 0;
}
