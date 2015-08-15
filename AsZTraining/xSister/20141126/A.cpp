#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))

using namespace std;

int main()
{
	freopen("in.txt", "r", stdin);
	int task;
	for (scanf("%d", &task); task; --task)
	{
		int n;
		scanf("%d", &n);
		int tmp = sqrt(n) + 1;
		int x = n, a = 1;
		REPP(i, 2, tmp)
		{
			if (x % i == 0)
			{
				a *= i;
				for (; x % i == 0; x /= i);
			}
		}
		if (x > 1) a *= x;
		printf("%d\n", n / a + 1);
	}
	return 0;
}
