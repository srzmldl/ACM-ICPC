#include <bits/stdc++.h>
#define MAXN 212345
#define INF 1000000000

using namespace std;

struct node
{
	long long sum;
	int pt;
	node(long long sum = 0, int pt = 0) : sum(sum), pt(pt) {};
} g[MAXN * 8];

int n, k, zeroNum, t;
int a[MAXN], d[MAXN * 8];

int minLab(int x, int y)
{
	return g[x].sum + a[g[x].pt + 1] < g[y].sum + a[g[y].pt + 1] ? x : y;
}
void change(int x, long long sum, int pt)
{
	g[x] = node(sum, pt);
	d[x + t] = x;
	x += t;
	for (x >>= 1; x; x >>= 1)
		d[x] = minLab(d[x << 1], d[x << 1 ^ 1]);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int m;
	long long X = 0;
	n = zeroNum = 0;
	scanf("%d%d", &m, &k);
	for (int i = 0; i < m; ++i)
	{	
		int x;
		scanf("%d", &x);
		if (x == 0) zeroNum++;
		else if (x > 0) a[++n] = x;
		else
		{
			a[++n] = -x;
			X += 1LL * x;
		}
	}
	if (zeroNum > 0)
	{
		if (zeroNum >= 18) zeroNum = k;
		else zeroNum = (1 << zeroNum) - 1;
	}
	sort(a + 1, a + n + 1);
	for (t = 1; t <= k * 2 + 1; t <<= 1);
	for (int i = 0; i <= t * 2; ++i)
		g[i].sum = 1LL * INF * n;
	int tot = 0;
	if (X < 0) 
	{
		++tot;
		change(tot, X, 0);
		for (int i = 0; i <= zeroNum && k; ++i, --k)
			cout << X << endl;
	}
	else 
	{
		++tot;
		change(tot, 0, 1);
		++tot;
		change(tot, a[1], 1);
		for (int i = 1; i <= zeroNum && k; ++i, --k)
			cout << 0 << endl;
		for (int i = 0; i <= zeroNum && k; ++i, --k)
			cout << a[1] << endl;
	}

	int flag = 0;
	for (; k; )
	{
		int lab = d[1];
		node tmp = g[lab];
		change(lab, 1LL * INF * n, 1);
		if (tmp.pt == n) continue;
		long long s = tmp.sum + a[tmp.pt + 1];
		int lim;
		if (s == 0 && !flag) lim = zeroNum - 1, flag = 1;
		else lim = zeroNum;
		for (int i = 0; i <= lim && k; ++i, --k)
			cout << s << endl;
		if (tmp.pt + 1 < n)
		{
			++tot;
			change(tot, tmp.sum, tmp.pt + 1);
			++tot;
			change(tot, s, tmp.pt + 1);
		}
	}
	return 0;
}
