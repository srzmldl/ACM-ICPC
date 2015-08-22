#include <bits/stdc++.h>
#define MAXN 51234
#define MAXSEG 401234

using namespace std;
typedef int arrayN[MAXN], arrayS[MAXN];

struct node
{
    int L, R;
} g[MAXN];

struct point
{
	int nxt;
	int f;

}dp[MAXN];

struct segmentTree
{
	int lab;
	int f, t;
} seg[MAXSEG];

int now, base, lim;
arrayN bh;

int com(int u, int v)
{
    return (g[u].L > g[v].L) || ((g[u].L == g[v].L) && (g[u].R < g[v].R)) || (g[u].L == g[v].L && g[u].R == g[v].R && u < v);
}

void change(int x, int lab, int f)
{
    x += base;
    if (seg[x].t == now)
    {
        if (seg[x].f > f || (seg[x].f == f && seg[x].lab < lab))
            return ;
    }
    seg[x].t = now;
    seg[x].lab = lab;
    seg[x].f = f;
    for (x >>= 1; x; x >>= 1)
    {
		int l = x << 1;
		int r = l ^ 1;
        if (seg[l].t < now)
        {
			seg[x] = seg[r];
			continue;
        }
        if (seg[r].t < now)
        {
			seg[x] = seg[l];
			continue;
		}
        if (seg[l].f == seg[r].f)
        {
			seg[x].f = seg[l].f;
			seg[x].lab = min(seg[l].lab, seg[r].lab);
			continue;
        }
        if (seg[l].f < seg[r].f)
			seg[x] = seg[r];
		else seg[x] = seg[l];
    }
}

void ask(int l, int r, int &rlab, int &rf)
{
	int f = 0, lab = 0;
	l += base - 1;
	r += base + 1;
	for (; (l ^ r) != 1; l >>= 1, r >>= 1)
	{
        if (!(l & 1))
        {
			if (seg[l + 1].t == now)
			{
				if (seg[l + 1].f > f || (seg[l + 1].f == f && seg[l + 1].lab < lab))
                    lab = seg[l + 1].lab, f = seg[l + 1].f;
			}
        }
        if (r & 1)
        {
			if (seg[r - 1].t == now)
			{
				if (seg[r - 1].f > f || (seg[r - 1].f == f && seg[r - 1].lab < lab))
                    lab = seg[r - 1].lab, f = seg[r - 1].f;
			}
        }
	}
    ++f;
	if (f > rf || (f == rf && lab < rlab))
	{
		rf = f, rlab = lab;
	}
}

void solve(int l, int r)
{
    if (l >= r) return ;
    int mid = (l + r) >> 1;
    solve(mid + 1, r);
	++now;
	for (int i = l; i <= r; ++i)
		bh[i] = i;
    sort(bh + l, bh + r + 1, com);

	for (int i = r; i >= l; --i)
	{
		int p = bh[i];
		if (p > mid)
		{
            change(g[p].R, p, dp[p].f);
		} else
		{
            ask(g[p].R, lim, dp[p].nxt, dp[p].f);
		}
	}

    solve(l, mid);
}

int main()
{
	//freopen("I.in", "r", stdin);
	now = 0;
	for (int n; scanf("%d", &n) != EOF; )
	{
		vector <int> vec;
		for (int i = 1; i <= n; ++i)
		{
            scanf("%d", &g[i].L);
            vec.push_back(g[i].L);
		}
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &g[i].R);
			vec.push_back(g[i].R);
			dp[i].nxt = dp[i].f = 0;
		}
        sort(vec.begin(), vec.end());
        vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
        int tmp = vec.size();
        lim = tmp;
        for (base = 1; base <= tmp + 2; base <<= 1);
        for (int i = 1; i <= n; ++i)
		{
			g[i].L = lower_bound(vec.begin(), vec.end(), g[i].L) - vec.begin() + 1;
			g[i].R = lower_bound(vec.begin(), vec.end(), g[i].R) - vec.begin() + 1;
		}
		dp[n].f = 1;
		dp[n].nxt = 0;
		solve(1, n);
		int lab = 0, f = 0;
		for (int i = 1; i <= n; ++i)
			if (dp[i].f > f)
			{
				lab = i;
				f = dp[i].f;
			}
        printf("%d\n", f);
        printf("%d", lab);
        for (lab = dp[lab].nxt;lab; lab = dp[lab].nxt)
        {
			printf(" %d", lab);
        }
        printf("\n");
	}
	return 0;
}
