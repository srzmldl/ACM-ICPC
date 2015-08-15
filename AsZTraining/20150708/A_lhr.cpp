#include <bits/stdc++.h>

using namespace std;

int a[1010][1010];

int main()
{
	freopen("avangard.in", "r", stdin);
	freopen("avangard.out", "w", stdout);
	int n;
	scanf("%d", &n);

	if (n % 2 == 0 || n % 3 == 0)
	{
		printf("No\n");
		return 0;
	}

	int p = 2;

	printf("Yes\n");
	for (int i = 0; i < n; i++)
	{
		int k = (i * p) % n;
		for (int j = 0; j < n; j++)
			printf("%d%c", (((j + k) >= n) ? (j + k - n) : (j + k)) + 1, " \n"[j == n - 1]);
	}

	return 0;
}