#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPP(i, a, b) for (int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 312345

using namespace std;

typedef int arrayN[MAXN];

arrayN a[2], b[2], c;
int n, g[MAXN * 4], t;

int ask(int l, int r)
{
	if (l > r) return 0;
	l = l + 1 + t - 1;
	r = r + 1 + t + 1;
	int tmp = 0;
	for (; (l ^ r) != 1; l >>= 1, r >>= 1)
	{
		if (r & 1) tmp += g[r - 1];
		if (!(l & 1)) tmp += g[l + 1];
	}
	return tmp;
}

void change(int x)
{
	x = x + 1 + t;
	g[x] = 1;
	for (x >>= 1; x; x >>= 1)
		g[x] = g[x << 1] + g[x << 1 ^ 1];
}

void calc(int k)
{
	MST(g, 0);
	REP(i, n - 1)
	{
		b[k][i] = a[k][i] - ask(0, a[k][i] - 1);
		change(a[k][i]);
	}
}

int main()
{
//	freopen("B.in", "r", stdin);
	scanf("%d", &n);
	for (t = 1; t <= n + 2; t <<= 1);
	REP(i, n) scanf("%d", &a[0][i]);
	REP(i, n) scanf("%d", &a[1][i]);
	calc(0);
	calc(1);

	MST(c, 0);
	for (int i = n - 2; i >= 0; --i)
	{
		int jc = n - i - 1;
		c[i] += b[0][i] + b[1][i];
		int j = i;
		for (;;)
		{
			if (c[j] > jc)
			{
				if (j - 1 >= 0) 
					c[j - 1] += c[j] / (jc + 1);
				c[j] %= (jc + 1);
				++jc;
				--j;
				if (j < 0) break;
			} else break;
		}
	}

	MST(g, 0);
	REPP(i, 0, n - 2)
	{
		int l = 0, r = n - 1;
		for (;l < r;)
		{
			int mid = (l + r + 1) >> 1;
			int tmp = mid - ask(0, mid - 1);
			if (tmp <= c[i])
				l = mid;
			else r = mid - 1;
		}
		printf("%d ", l);
		change(l);
	}
	REPP(i, 0, n - 1)
	{
		if (g[i + 1 + t] == 0)
		{
			printf("%d\n", i);
			break;
		}
	}
	return 0;
}
