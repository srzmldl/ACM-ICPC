#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for (int i = 0; i < (int) (n); ++i) 
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 1050000
#define MAXM 5000010
#define MO 1000000007

using namespace std;

char a[MAXM];
int f[MAXN][22], g[9][33000][22];//last sta, m, 01
int tf[18][22];


void add(int &u, int v)
{
	u += v;
	if (u > MO) u -= MO;
}

void calc(int sta, int n, int m)
{
	for (int i = n; i >= 1; --i)
	{
		int avail = !(sta & (1 << (i - 1)));
		int sum = 0;
		REPP(k, 0, m)
		{
			tf[i][k << 1] = tf[i][k << 1 | 1] = 0;
			if ((i << 1) > n)
			{
				if (k == 0) tf[i][k << 1] = tf[i][k << 1 | 1] = 1;
				else if (avail) tf[i][k << 1 | 1] = 1;
			} else if ((i << 1 | 1) > n)
			{
				tf[i][k << 1] = tf[i][k << 1 | 1] = tf[i << 1][k << 1 | 1];
				if (avail && k) tf[i][k << 1 | 1]++;
			} else 
			{
				for (int h = 0; h <= k; ++h)
					add(tf[i][k << 1], 1LL * tf[i << 1][h << 1 ^ 1] * tf[i << 1 ^ 1][(k - h) << 1 | 1] % MO);
				if (avail)
					for (int h = 0; h < k; ++h)
						add(tf[i][k << 1 | 1], 1LL * tf[i << 1][h << 1] * tf[i << 1 ^ 1][(k - 1 - h) << 1] % MO);
			}
		}
		if ((i << 1 ^ 1) <= n)
		{
			if (avail)
				REPP(k, 0, m)
				{
					int tmp = sum;
					add(sum, tf[i][k << 1 | 1]);
					add(tf[i][k << 1 | 1], tmp);
					add(tf[i][k << 1 | 1], tf[i][k << 1]);
				}
			else 
			{
				REPP(k, 0, m)
					tf[i][k << 1 | 1] = tf[i][k << 1];
			}
		}
	}
}

void origin16(int n, int m)
{
	//REPP(i, 0, 8)
	int tmpArr[3];
	tmpArr[0] = 0;
	tmpArr[1] = 8;
	tmpArr[2] = 0;

	int tmp = 1;
	for (; tmp <= n; tmp <<= 1);
	int newN = tmp / 16 - 1;
	for (int i = newN + 1; i <= newN * 2 + 1; ++i)
	{
		if (i * 8 <= n && i * 8 + 7 > n)
		{
			tmpArr[2] = n - (i * 8) + 1;
			break;
		}
	}

	for (int tt = 0; tt <= 2; ++tt)
	{
		int i = tmpArr[tt];
		REP(j, (1 << (7 + i)))
		{
			calc(j, 7 + i, m);
			REPP(k, 0, m)
			{
				g[i][j][k << 1] = tf[1][k << 1];
				g[i][j][k << 1 ^ 1] = tf[1][k << 1 | 1];
			}
		}
	}
}

void getNAndF(int &n, int m)
{
	int tmp = 1;
	for (; tmp <= n; tmp <<= 1);
	int newN = tmp / 16 - 1;
	for (int i = newN + 1; i <= ((newN << 1) ^ 1); ++i)
	{
		int s1 = 8;
		if (i << 3 > n) s1 = 0;
		else if ((i << 3) + 7 > n)
			s1 = n - (i << 3) + 1;
		int s2 = 0;
		int cnt = 0;
		REPP(j, 0, 3)
		{
			for (int k = i << j; k < ((i << j) + (1 << j)) && k <= n; ++k)
			{
				if (a[k - 1] == '1')
					s2 |= 1 << cnt;
				cnt++;
			}
		}
		REPP(j, 0, m)
		{
			f[i][j << 1] = g[s1][s2][j << 1];
			f[i][j << 1 ^ 1] = g[s1][s2][j << 1 ^ 1];
		}
	}
	n = newN;
}

int main()
{
	freopen("set.txt", "r", stdin);
	int n, m;
	scanf("%d%d", &n, &m);
	scanf("%s", a);
	if (n < 16)
	{
		int sta = 0;
		REP(i, n) 
			if (a[i] == '1')
				sta += (1 << i);
		calc(sta, n, m);
		printf("%d\n", tf[1][m << 1 ^ 1]);
		return 0;
	}

	
	origin16(n, m);
	getNAndF(n, m); //newN n last unkown
	
	for (int i = n; i >= 1; --i)
	{
		int avail = 0;
		int i2 = i << 1, i21 = i << 1 ^ 1;
		if (a[i - 1] == '0') avail = 1;
		for (int k = 0; k <= m; ++k)
		{
			f[i][k << 1] = f[i][k << 1 | 1] = 0;
			for (int h = 0; h <= k; ++h)
				add(f[i][k << 1], 1LL * f[i2][h << 1 | 1]* f[i21][(k - h) << 1 | 1] % MO);
			if (avail)
			{
				for (int h = 0; h < k; ++h)
					add(f[i][k << 1 | 1], 1LL * f[i2][h << 1] * f[i21][(k - 1 - h) << 1] % MO);
			}
		}
		int sum = 0;
		if (avail)
		{
			REPP(k, 0, m)
			{
				int tmp = sum;
				add(sum, f[i][k << 1 | 1]);
				add(f[i][k << 1 | 1], f[i][k << 1]);
				add(f[i][k << 1 | 1], tmp);
			}
		} else 
		{
			REPP(k, 0, m)
				f[i][k << 1 | 1] = f[i][k << 1];
		}
	}
	printf("%d\n", f[1][m << 1 | 1]);
	return 0;
}

