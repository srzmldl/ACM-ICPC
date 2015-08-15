#include <bits/stdc++.h>

using namespace std;

int main()
{
	freopen("zoj3837.txt", "w", stdout);
	int task = 3;
	printf("%d\n", task);
	for (int i = 1; i <= task; ++i)
	{
		int n = 5;
		printf("%d\n", n);
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				if (i == (n + 1) / 2 && i == j)
				{
					printf("v");
					continue;
				}
				int k = rand();
				if (k % 5 == 0) printf("@");
				else 
				{
					//(k % 10); 
					printf("%c", k % 10 + '0');
				}
			}
			printf("\n");
		}
	}
	return 0;
}
