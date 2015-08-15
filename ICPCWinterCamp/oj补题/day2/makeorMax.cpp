#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n = 1000;
	srand(clock() % time(0));
	printf("%d\n", n);
	int lim = 1<<16;
	for (int i = 0; i < n; ++i)
		printf("%d ", rand() % lim);
	return 0;
}
