#include <bits/stdc++.h>
#define MAXN 60
using namespace std;

struct node
{
	int lab, value;
}a[MAXN];

long long m;
int n;

int com(node u, node v)
{
	return u.value < v.value || (u.value == v.value && u.lab < v.lab);
}

struct sameSegment
{
	int l, r;
	
}g[MAXN];

int tot, ans[MAXN];

int getBlock()
{
	for (int i = 0; i <= tot; ++i)
	{
		int ok = 0;
		long long tmp = 1; 
		for (int j = i + 1; j <= tot && !ok; ++j)
		{
			for (int k = 1; !ok && k <= g[j].r - g[j].l + 1; ++k)
			{
				tmp *= k;
				if (tmp >= m) ok = 1;
			}
		}
		if (ok == 0) return i - 1;
	}
	return tot;
}

int checkAndSub(int blk, int u, int v)
{
	long long tmp = 1;
	int ok = 0;
	for (int i = blk + 1; !ok && i <= tot; ++i)
		for (int j = 1; !ok && j <= g[i].r - g[i].l + 1; ++j)
		{
			tmp *= j;
			if (tmp >= m) ok = 1;
		}
	for (int k = 1; !ok && k <= g[blk].r - u; ++k)
	{
		tmp *= k;
		if (tmp >= m) ok = 1;
	}
	if (!ok)
	{
		long long t1 = tmp * (v - u + 1);
		if (t1 >= m) ok = 1;
	}
	if (ok && v > u)
		m -= tmp * (v - u);
	return ok;
}

void getAns()
{
	for (int i = 1; i <= tot; ++i)
		for (int j = g[i].l; j <= g[j].r; ++j)
			for (int k = j; k <= g[j].r; ++k)
				if (checkAndSub(i, j, k))
				{
					node tmp = a[k];
					for (int h = k; h > j; --h)
						a[h] = a[h - 1];
					a[j] = tmp;
					break;
				}
	for (int i = 1; i <= n; ++i)
		ans[a[i].lab] = i;
	for (int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], " \n"[i == n]);
}

int main()
{
	//freopen("B1.in", "r", stdin);
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i)
	{
		a[i].value = i * (n - i + 1);
		a[i].lab = i;
	}
	return 0;
}

