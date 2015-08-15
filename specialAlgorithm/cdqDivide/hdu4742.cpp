#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REDD(i, a, b) for(int i = (int) (a); i >= (int) (b); --i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 111111
#include <vector>

using namespace std;
int zLim;

long long gTot[MAXN *4];
int t, g[MAXN *4], n, ti[MAXN *4], now;
struct node
{
    int x, y, z, f;
    long long tot;
} a[MAXN];

int comx(node A, node B)
{
    return (A.x < B.x) || ((A.x == B.x) && (A.y < B.y)) || ((A.x == B.x) && (A.y == B.y) && A.z < B.z);
}

int comy(node A, node B)
{
    return A.y < B.y;
}

void change(int pos, int x, long long cnt)
{
    pos += t;
    if (ti[pos] != now) g[pos] = gTot[pos] = 0;
    if (x < g[pos]) return ;
    if (x == g[pos]) gTot[pos] += cnt;
    else gTot[pos] = cnt, g[pos] = x;
    ti[pos] = now;

    for(pos >>= 1; pos; pos >>= 1)
    {
        if (ti[pos <<1] != now) g[pos <<1] = gTot[pos <<1] = 0;
        if (ti[pos <<1 ^1] != now) g[pos <<1 ^ 1] = gTot[pos <<1 ^1] = 0;
        ti[pos] = now;
        g[pos] = max(g[pos <<1], g[pos << 1 ^1]);
        gTot[pos] = 0;
        if (g[pos] == g[pos <<1]) gTot[pos] += gTot[pos <<1];
        if (g[pos] == g[pos <<1 ^1]) gTot[pos] += gTot[pos <<1 ^1];
    }
}

int ask(int l, int r, long long &cnt)
{
    if (l > r) return 0;
    int tmp = 0;
    cnt = 0;
    l += t - 1, r += t + 1;
    for (;(l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l &1))
        {
            if (ti[l +1] == now)
			{
            if (tmp == g[l +1]) cnt += gTot[l +1];
            else if (tmp <g[l +1])
            {
                tmp = g[l +1];
                cnt = gTot[l +1];
            }
			}
        }
        if (r &1)
        {
            if (ti[r - 1] == now)
			{
            if (tmp == g[r - 1]) cnt += gTot[r - 1];
            else if (tmp < g[r - 1])
            {
                tmp = g[r - 1];
                cnt = gTot[r - 1];
            }
			}
        }
    }
    return tmp;
}


void solve(int l, int r)
{
    if (l == r) return ;
    int mid = (l +r) >>1;
    solve(mid +1, r);

    sort(a +mid +1, a +r +1, comy);
    sort(a +l, a +mid +1, comy);

    // MST(g, 0);
    //MST(gTot, 0);
    ++now;
    int pos = r +1;
    REDD(i, mid, l)
    {
        for (;pos > mid +1 && a[pos - 1].y >= a[i].y; --pos)
        {
            change(a[pos - 1].z, a[pos - 1].f, a[pos - 1].tot);
        }

        long long tmpTot;
        int tmp = ask(a[i].z, zLim, tmpTot) +1;
        if (a[i].f == tmp) a[i].tot += tmpTot;
        else if (a[i].f < tmp)
        {
            a[i].f = tmp;
            a[i].tot = tmpTot;
        }
    }

    sort(a + l, a +r +1, comx);
    solve(l, mid);
}

int INT()
{
    int res;
    char ch;
    while (ch = getchar(), !isdigit(ch));
    for (res = ch - '0'; ch = getchar(), isdigit(ch);)
        res = res * 10 + ch - '0';
    return res;
}

int main()
{
    int task;
    freopen("in.txt", "r", stdin);
    now = 0;
    for (task = INT(); task; --task)
    {
        n = INT();
        vector <int> dataZ;
        REPP(i, 1, n)
        {
            a[i].x = INT();
            a[i].y = INT();
            a[i].z = INT();
            a[i].f = 1;
            a[i].tot = 1;
            dataZ.push_back(a[i].z);
        }
        sort(dataZ.begin(), dataZ.end());
        dataZ.resize(unique(dataZ.begin(), dataZ.end()) - dataZ.begin());
        REPP(i, 1, n)
        {
            a[i].z = (lower_bound(dataZ.begin(), dataZ.end(), a[i].z) - dataZ.begin()) +1;
        }
        zLim = dataZ.size();
        for (t = 1; t <= zLim + 1; t <<= 1);
        sort(a +1, a + n +1, comx);
        solve(1, n);
        int ans = 0;
        long long cnt = 0;
        REPP(i, 1, n)
        {
            if (ans == a[i].f) cnt += a[i].tot;
            else if (ans < a[i].f) cnt = a[i].tot, ans = a[i].f;
        }
        printf("%d %lld\n", ans, cnt);
    }
    return 0;
}
