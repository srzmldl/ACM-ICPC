#include <bits/stdc++.h>

using namespace std;

bool a[1000100];

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int main()
{
//	int n;
//	scanf("%d", &n);
//	int maxi = 0;
//	for (int i = 0; i < n; i++)
//	{
//		int x;
//		scanf("%d", &x);
//		maxi = max(maxi, x);
//		a[x] = true;
//	}
	int maxi = 1000000;
	for (int i = 1; i <= maxi; i++)
		a[i] = true;

	int cnt = 0;
	int ans = 0;
	for (int i = 1; i * i < maxi; i++)
		for (int j = i + 1; j * j <= maxi; j++)
		{
			if (gcd(i, j) != 1)
				continue;
			int k1 = i * i, k2 = j * j;
			for (int g = 1; g * k2 <= maxi; g++)
			{
				cnt++;
				if (a[g * k1] && a[g * i * j] && a[g * k2])
					ans++;
			}
		}
	cout << ans << endl;
	return 0;
}
