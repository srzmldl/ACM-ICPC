#include <bits/stdc++.h>

using namespace std;

long long a[10], deg[10];
int num[10][10];

int main()
{
	int n;
	long long sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; sum += a[i++])
	{
		scanf("%d", &a[i]);
		if (a[i] == 1)
			n--, i--;
	}
	if (!n)
	{
		cout << 1 << endl;
		return 0;
	}
	int tot = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			num[i][j] = tot++;
	int all = 1 << tot;
	long long ans = sum;
	for (int k = 0; k < all; k++)
	{
		for (int i = 0; i < n; i++)
			deg[i] = 0;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (k & (1 << num[i][j]))
					deg[i]++, deg[j]++;
		bool flag = true;
		long long tmp = 0;
		for (int i = 0; i < n; tmp += deg[i++])
			if (deg[i] > a[i])
				flag = false;
		if (flag)
			ans = min(ans, sum - tmp / 2);
	}
	cout << ans << endl;
	return 0;
}
