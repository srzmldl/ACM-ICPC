#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define REPP(i, a, b) for(int i = a; i <= b; ++i)

using namespace std;

void prt(int x, int y)
{
	printf("%d %d\n", x, y);
}

int main()
{
	freopen("in.txt", "r", stdin);
	int l, s;
	scanf("%d%d", &l, &s);

	int h = l / 4;
	int w = l / 2 - h;
	if ((l & 1) || (s < h + w - 1) || (1LL * s > 1LL * h * w)) 
	{
		printf("-1\n");
		return 0;
	}
	s -= (h + w - 1);
	if (s == (h - 1) * (w - 1))
	{
		printf("4\n");
		printf("0 0\n");
		printf("%d %d\n", w, 0);
		printf("%d %d\n", w, h);
		printf("%d %d\n", 0, h);
	} else if (s % (h - 1) == 0)
	{
		int tmp = s / (h - 1);
		printf("%d\n", 6);
		prt(0, 0);
		prt(w, 0);
		prt(w, 1);
		prt(tmp + 1, 1);
		prt(tmp + 1, h);
		prt(0, h);
	} else 
	{
		int tmp = s / (h - 1);
		int rst = s % (h - 1);
		if (tmp + 2 != w)
		{
			printf("%d\n", 8);
			prt(0, 0);
			prt(w, 0);
			prt(w, 1);
			prt(tmp + 2, 1);
			prt(tmp + 2, rst + 1);
			prt(tmp + 1, rst + 1);
			prt(tmp + 1, h);
			prt(0, h);
		} else 
		{
			printf("6\n");
			prt(0, 0);
			prt(w, 0);
			prt(w, rst + 1);
			prt(w - 1, rst + 1);
			prt(w - 1, h);
			prt(0, h);
		}
	}
	return 0;
}
