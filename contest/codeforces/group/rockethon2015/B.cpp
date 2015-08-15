#include <bits/stdc++.h>
#define MAXN 60
using namespace std;

long long m;
int n, ans[MAXN];

struct node
{
	int l, r;
}g[MAXN];

void work(int x, int l, int r)
{
	if (x > n) return ;
	long long tmp = 1;
	for (int k = l + 1; k <= r - 1; ++k)
	{
		tmp *= 2;
		if (tmp >= m) break;
	}
	if (tmp >= m) 
	{
		ans[l] = x;
		work(x + 1, l + 1, r);
	} else 
	{
		ans[r] = x;
		m -= tmp;
		work(x + 1, l, r - 1);
	}
	return ;
}

int main()
{
	//freopen("B1.in", "r", stdin);
	scanf("%d%I64d", &n, &m);
	work(1, 1, n);
	for (int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}

