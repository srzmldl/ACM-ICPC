#include <bits/stdc++.h>
#define MAXN 112345
#define MAXNODE 5012345

using namespace std;
typedef int arrayN[MAXN * 2];

arrayN e, nxt, fir;
int num, tot;

struct segmentNode
{
	segmentNode *l, *r;
	int low, up, num;
}tree[MAXNODE];

struct node
{
	int val, dep;
	int f[25];
	segmentNode *rt;
} a[MAXN];


void link(int u, int v)
{
	e[++num] = v, nxt[num] = fir[u];
	fir[u] = num;
}

segmentNode *build(int l, int r)
{
	segmentNode *tp = &tree[tot++];
	int mid = l + r >> 1;
	tp->low = l, tp->up = r;
	tp->num = 0;
	tp->l = tp->r = NULL;
	if (l == r) return tp;
	tp->l = build(l, mid);
	tp->r = build(mid + 1, r);
	return tp;
}

segmentNode *change(segmentNode *u, int x)
{
	segmentNode *tp = &tree[tot++];
	tp->l = u->l, tp->r = u->r;
	tp->num = u->num + 1;
	tp->low = u->low, tp->up = u->up;
	int mid = tp->up + tp->low >> 1;
	if (tp->low == tp->up) return tp;
	if (x <= mid) tp->l = change(u->l, x);
	else tp->r = change(u->r, x);
	return tp;
}

void dfs(int x, int fa, int depth)
{
	a[x].dep = depth;
	a[x].f[0] = fa;
	a[x].rt = change(a[fa].rt, a[x].val);
	for (int p = fir[x]; p; p = nxt[p])
		if (e[p] != fa)
			dfs(e[p], x, depth + 1);
}

void initLCA(int n)
{
	for (int i = 1; i <= 20; ++i)
		for (int j = 1; j <= n; ++j)
			a[j].f[i] = a[a[j].f[i - 1]].f[i - 1];
}

int getLCA(int u, int v)
{
	if (a[u].dep < a[v].dep) swap(u, v);
	int dt = a[u].dep - a[v].dep;
	for (int i = 20; i >= 0 && dt; i--)
		if (a[u].f[i] && ((1<< i) <= dt)) 
		{
			u = a[u].f[i];
			dt -= (1 << i);
		}
	if (u == v) return u;
	for (int i = 20; i >= 0; --i)
		if (a[u].f[i] != a[v].f[i])
			u = a[u].f[i], v = a[v].f[i];
	return a[u].f[0];
}

int ask(int u, int v, int lca, int k)
{
	int fa = a[lca].f[0];
	segmentNode *lk1l = a[u].rt, *lk1r = a[lca].rt;
	segmentNode *lk2l = a[v].rt, *lk2r = a[fa].rt;
	for (; ;)
	{
		if (lk1l->low == lk1l->up) return lk1l->low;
		int tmp = lk1l->l->num - lk1r->l->num + lk2l->l->num - lk2r->l->num;
		if (tmp >= k)
		{
			lk1l = lk1l->l, lk1r = lk1r->l;
			lk2l = lk2l->l, lk2r = lk2r->l;
		}else 
		{
			k -= tmp;
			lk1l = lk1l->r, lk1r = lk1r->r;
			lk2l = lk2l->r, lk2r = lk2r->r;
		}
	}
}

vector<int> vec;

int main()
{
	freopen("in.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i].val);
		vec.push_back(a[i].val);
	}
	sort(vec.begin(), vec.end());
	vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
	for (int i = 1; i <= n; ++i)
		a[i].val = lower_bound(vec.begin(), vec.end(), a[i].val) - vec.begin();
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		link(u, v);
		link(v, u);
	}
	a[0].rt = build(0, n);
	dfs(1, 0, 1);
	initLCA(n);
	for (int i = 1; i <= m; ++i)
	{
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		int lca = getLCA(u, v);
		printf("%d\n", vec[ask(u, v, lca, k)]);
	}
	return 0;
}

