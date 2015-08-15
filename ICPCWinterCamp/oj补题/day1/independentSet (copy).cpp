#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for (int i = 0; i < (int) (n); ++i) 
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 1000000
#define MAXM 6000000
#define MO 1000000007

using namespace std;

char a[MAXM];
int f[MAXN][12][2], g[10][40000][12][2];//last sta, m, 01
int tf[18][12][2];


int add(int u, int v)
{
	int tmp = u + v;
	if (tmp > MO) tmp -= MO;
	return tmp;
}

int mul(int u, int v)
{
	return 1LL * u * v  % MO;
}

void calc(int sta, int n, int m)
{
	
	for (int i = n; i >= 1; --i)
		REPP(k, 0, m)
		{
			tf[i][k][0] = tf[i][k][1] = 0;
			{
				//calc tf0
				if ((i << 1) > n)
				{
					if (k == 0) 
						tf[i][k][0] = 1;
				} else if (i * 2 + 1 > n)
				{
					tf[i][k][0] = add(tf[i << 1][k][0], tf[i << 1][k][1]);
				} else 
				{
					REPP(h, 0, k)
						tf[i][k][0] = add(tf[i][k][0], mul(add(tf[i << 1][h][0], tf[i << 1][h][1]), add(tf[i << 1 ^ 1][k - h][0], tf[i << 1 ^ 1][k - h][1])));
				}
			}
			if (!(sta & (1 << (i - 1))))
			{
				//calc tf1
				if (k >= 2) tf[i][k][1] = tf[i][k - 1][1];
				if (i * 2 > n)
				{
					if (k > 0) tf[i][k][1] = 1;
				} else if (i * 2 + 1 > n)
				{
					if (k > 0)
						tf[i][k][1] = add(tf[i][k][1], tf[i << 1][k - 1][0]);
				} else 
				{
					REPP(h, 0, k - 1)
						tf[i][k][1] = add(tf[i][k][1], mul(tf[i << 1][h][0], tf[i << 1 ^ 1][k - h - 1][0]));
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
				g[i][j][k][0] = tf[1][k][0];
				g[i][j][k][1] = tf[1][k][1];
			}
		}
	}
}

void getNAndF(int &n, int m)
{
	int tmp = 1;
	for (; tmp <= n; tmp <<= 1);
	int newN = tmp / 16 - 1;
	for (int i = newN + 1; i <= newN * 2 + 1; ++i)
	{
		int s1 = 8;
		if (i * 8 > n) s1 = 0;
		else if (i * 8 + 7 > n)
			s1 = n - (i * 8) + 1;
		int s2 = 0, cnt = 0;
		deque<int> deq;
		deq.push_back(i);
		for(; !deq.empty();)
		{
			int tt = deq.front();
			deq.pop_front();
			if (a[tt - 1] == '1')
				s2 += (1 << cnt);
			cnt++;
			if (tt * 2 <= n)
				deq.push_back(tt * 2);
			if (tt * 2 + 1 <= n)
				deq.push_back(tt * 2 + 1);
		}

		REPP(j, 0, m)
			REP(k, 2)
			f[i][j][k] = g[s1][s2][j][k];
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
		printf("%d\n", add(tf[1][m][0], tf[1][m][1]));
		return 0;
	}

	
	origin16(n, m);
	getNAndF(n, m); //newN n last unkown

	for (int i = n; i >= 1; --i)
	{
		int i2 = i << 1, i21 = i << 1 ^ 1;
		int im1 = i - 1;
		for (int k = 0; k <= m; ++k)
		{
			int t1 = f[i][k][0];
			for (int h = 0; h <= k; ++h)
				t1 = add(t1, mul(add(f[i2][h][0], f[i2][h][1]), add(f[i21][k - h][0], f[i21][k - h][1])));
			f[i][k][0] = t1;
			if (a[im1] == '0')
			{
				t1 = f[i][k][1];
				if (k > 1)
					t1 = f[i][k - 1][1];
				for (int h = 0; h < k; ++h)
					t1 = add(t1, mul(f[i2][h][0], f[i21][k - 1 - h][0]));
				f[i][k][1] = t1;
			}
		}
	}
	printf("%d\n", add(f[1][m][0], f[1][m][1]));
	return 0;
}

