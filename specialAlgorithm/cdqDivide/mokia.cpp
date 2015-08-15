#include <bits/stdc++.h>
#define MAXN 301234

using namespace std;
typedef int arrayN[MAXN];
arrayN lab, ans;

struct node
{
	int x, y, sum, lab, sig;
	node() {};
	node(int tx, int ty, int tsum, int tlab, int tsig)
		{
			x = tx, y = ty, sum = tsum, lab = tlab, sig = tsig;
		}
} g[MAXN];

int d[MAXN * 4], t[MAXN * 4];

int now, base, tot = 0, cnt = 0;
vector<int> vec;

void change(int x, int val)
{
	x += base;
	if (t[x] == now) d[x] += val;
	else d[x] = val;
	t[x] = now;
	for (x >>= 1; x; x >>= 1)
	{
		if (t[x << 1] != now) d[x] = d[x << 1 ^ 1];
		else if (t[x << 1 ^ 1] != now) d[x] = d[x << 1];
		else d[x] = d[x << 1] + d[x << 1 ^ 1];
		t[x] = now;
	}
}

int ask(int l, int r)
{
	if (l > r) return 0;
	l += base - 1, r += base + 1;
	int tmp = 0;
	for (; (l ^ r) != 1; l >>= 1, r >>= 1)
	{
		if (!(l & 1) && t[l + 1] == now) tmp += d[l + 1];
		if ((r & 1) && t[r - 1] == now) tmp += d[r - 1];
	}
	return tmp;
}

int comx(int u, int v)
{
	return g[u].x < g[v].x || (g[u].x == g[v].x && u < v);
}
void solve(int l, int r)
{
	if (l >= r) return ;
	int mid = l + r >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	for (int i = l; i <= r; ++i)
		lab[i] = i;
	++now;
	sort(lab + l, lab + r + 1, comx);
	for (int i = l; i <= r; ++i)
	{
		int p = lab[i];
		if (p <= mid && g[p].lab == 0) change(g[p].y, g[p].sum);
		else if (p > mid && g[p].lab) ans[g[p].lab] += ask(1, g[p].y) * g[p].sig;
	}
}

int main()
{
    //	freopen("mokia.in", "r", stdin);
    //	freopen("mokia.out", "w", stdout);
	int k;
	scanf("%d%d", &k, &k);
	for (;1;)
	{
		scanf("%d", &k);
		if (k == 3) break;
		if (k == 1)
		{
			int x, y, A;
			scanf("%d%d%d", &x, &y, &A);
			vec.push_back(y);
			g[++tot] = node(x, y, A, 0, 0);
		} else 
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			vec.push_back(y1 - 1);
			vec.push_back(y2);
			++cnt;
			g[++tot] = node(x2, y2, 0, cnt, 1);
			g[++tot] = node(x1 - 1, y1 - 1, 0, cnt, 1);
			g[++tot] = node(x1 - 1, y2, 0, cnt, -1);
			g[++tot] = node(x2, y1 - 1, 0, cnt, -1);
		}
	}
	sort(vec.begin(), vec.end());
	vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
	for (int i = 1; i <= tot; ++i)
		g[i].y = lower_bound(vec.begin(), vec.end(), g[i].y) - vec.begin() + 2;
	for (base = 1; base <= vec.size() + 1; base <<= 1);
	solve(1, tot);
	for (int i = 1; i <= cnt; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
