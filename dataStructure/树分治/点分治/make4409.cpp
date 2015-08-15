#include<bits/stdc++.h>

using namespace std;

int random(int x)
{
	return abs(rand() * rand() * rand()) % x + 1;
}

int main()
{
	srand(clock() % time(0));
	freopen("la4409.in", "w", stdout);
	int mLim = 100000000, nLim = 30000;
	int n = random(nLim);
	int m = random(mLim);
	int llim = 1000, dlim = 1000;
	int T = 10;
	printf("%d\n", T);
	for (int task = 1; task <= T; ++task)
	{
		printf("%d %d\n", n, m);
		for (int i = 2; i <= n; ++i)
		{
			int u = random(i - 1);
			int v = i;
			int D = random(dlim);
			int L = random(llim);
			printf("%d %d %d %d\n", u, v, D, L);
		}
	}
	return 0;
}
