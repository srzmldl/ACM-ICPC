#include <bits/stdc++.h>

#define MOD 1000000007

using namespace std;

int a[5000500];
int f[5000500][12][2];

int add(int x, int y)
{
	x += y;
	if (x > MOD)
		x -= MOD;
	return x;
}

int mul(int x, int y)
{
	long long g = x, h = y;
	g *= y;
	g %= MOD;
	return (int)g;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%1d", &a[i + 1]);
	for (int i = n; i; i--)
	{
		int l = i << 1;
		int r = l ^ 1;
		if (l > n)
		{
			f[i][0][0] = 1;
			if (!a[i])
				f[i][1][1] = 1;
			continue;
		}
		if (r > n)
		{
			for (int j = 0; j <= m; j++)
			{
				f[i][j][0] = add(f[l][j][0], f[l][j][1]);
				if (!a[i] && j)
					f[i][j][j] = f[l][j - 1][0];
			}
			continue;
		}
		for (int j = 0; j <= m; j++)
		{
			for (int g = 0; g <= j; g++)
				f[i][j][0] = add(f[i][j][0], add(add(mul(f[l][g][0], f[r][j - g][0]), mul(f[l][g][0], f[r][j - g][1])), add(mul(f[l][g][1], f[r][j - g][0]), mul(f[l][g][1], f[r][j - g][1]))));
			if (!a[i] && j)
				for (int g = 0; g < j; g++)
					f[i][j][1] = add(f[i][j][1], mul(f[l][g][0], f[r][j - g - 1][0]));
		}
	}
	printf("%d\n", add(f[1][m][0], f[1][m][1]));
	return 0;
}
