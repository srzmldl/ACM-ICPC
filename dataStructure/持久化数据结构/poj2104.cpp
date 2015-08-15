#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <iostream>

#define MAXNODE 2012345
#define MAXN 112345

using namespace std;
typedef int arrayN[MAXN];

int n, m, tot;
arrayN a, b;
vector<int> vec;

node *build(int l, int r)
{
	node *tmp = &tree[tot++];
	tmp->low = l, tmp->up = r;
	tmp->num = 0;
	if (l == r) return tmp;
	int mid = l + r >> 1;
	tmp->l = build(l, mid);
	tmp->r = build(mid + 1, r);
	return tmp;
}

node *change(node *pt, int pos, int value)
{
	node *tmp = &tree[tot++];
	tmp->num = pt->num + 1;
	tmp->l = pt->l, tmp->r = pt->r;
	tmp->low = pt->low, tmp->up = pt->up;
	if (tmp->low == tmp->up) return tmp;
	int mid = tmp->low + tmp->up >> 1;
	if (pos <= mid) tmp->l = change(pt->l, pos, value);
	else tmp->r = change(pt->r, pos, value);
	return tmp;
}

int ask(int l, int r, int k)
{
	node *ptl = root[l - 1], *ptr = root[r];
	for (;ptl->low < ptl->up;)
	{
		if (ptr->l->num - ptl->l->num >= k)
		{
			ptr = ptr->l, ptl = ptl->l;
		} else 
		{
			k -= (ptr->l->num - ptl->l->num);
			ptr = ptr->r, ptl = ptl->r;
		}
	}
	return ptl->low;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	tot = 0;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		vec.push_back(a[i]);
	}
	sort(vec.begin(), vec.end());
	vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
	for (int i = 1; i <= n; ++i)
		b[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
	root[0] = build(0, vec.size() - 1);
	for (int i = 1; i <= n; ++i)
		root[i] = change(root[i - 1], b[i], 1);
	for (int i = 0; i < m; ++i)
	{
		int l, r, k;
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", vec[ask(l, r, k)]);
	}
	return 0;
}
