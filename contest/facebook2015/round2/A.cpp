#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXN 51234

using namespace std;


int n, a[MAXN];

int check(int lnum, int rnum, int llab, int rlab)
{
	for (;llab <= rlab;)
	{
		int x = a[llab];
		if (x == lnum - 1) 
		{
			++llab;
			lnum--;
			continue;
		}
		if (x == rnum + 1)
		{
			++llab;
			rnum++;
			continue;
		}
		x = a[rlab];
		if (x == lnum - 1)
		{
			--rlab;
			lnum--;
			continue;
		}
		if (x == rnum + 1)
		{
			--rlab;
			rnum++;
			continue;
		}
		return 0;
	}
	return 1;
}

int main()
{
	freopen("A.txt", "r", stdin);
	freopen("A.out", "w", stdout);
	int T;
	scanf("%d", &T);
	REPP(task, 1, T)
	{
		scanf("%d", &n);
		REPP(i, 1, n)
			scanf("%d", &a[i]);
		printf("Case #%d: ", task);
		if (check(a[1], a[1], 2, n) || check(a[n], a[n], 1, n - 1))
			printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
