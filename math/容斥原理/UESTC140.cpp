#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MOD 1000000007
#define MAXM 1111

using namespace std;

int n, m, a[MAXM];

long long getSum(int x)
{
	return 1LL * (x + 1) * x / 2 % MOD;
}

long long getSquareSum(int x)
{
	long long t[3];
	if (x <= 0) return 0;
	t[0] = x;
	t[1] = x + 1;
	t[2] = 2LL * x + 1;
	REP(i, 3)
		if (t[i] % 2 == 0)
		{
			t[i] /= 2;
			break;
		}
	REP(i, 3)
		if (t[i] % 3 == 0)
		{
			t[i] /= 3;
			break;
		}
	long long tmp = t[0] * t[1] % MOD;
	return tmp * t[2] % MOD;
}

long long getZero()
{
	int limEven = n / 2;
	int limOdd = n / 2;
	if (!(n & 1)) --limOdd;
	long long tmp = (getSquareSum(limEven - 1) + getSquareSum(limOdd)) % MOD;
	tmp = (tmp - getSum(limOdd) + MOD) % MOD;
	return tmp;
}

long long getOne()
{
	long long tmp = 0;
	REP(i, m)
	{
		long long k = a[i] / 2;
		if (a[i] & 1)
		{
			long long mid = (1LL * k * k - k + MOD) % MOD;
			tmp = (tmp + mid) % MOD;
		} else 
		{
			long long mid = 1LL * (k - 1) * (k - 1) % MOD;
			tmp = (tmp + mid) % MOD;
		}// RIGHT


		// LEFT
		long long x = a[i];
		k = n - 2LL * x;
		long long mid;
		if (k >= 0) mid = (getSum(x - 1) + (x - 1) * k % MOD) % MOD;
		else mid = getSum(n - x - 1);

		tmp = (tmp + mid) % MOD;
		//MID
		long long R = n - a[i];
		long long rT = a[i] - 2;
		if (rT <= R)
			tmp = (tmp + getSum(rT)) % MOD;
		else tmp = ((tmp + getSum(R)) % MOD + R * (rT - R) % MOD) % MOD;
		
			
	}
	return tmp;
}

long long getTwo()
{
	long long tmp = 0;
	REPP(i, 0, m - 2)
		REPP(j, i + 1, m - 1)
	{
		int R = min(n, a[i] + a[j] - 1);
		if (R >= a[j] + 1) //right
			tmp = (tmp + R - a[j]) % MOD;
		if (a[i] - 1 >= a[j] - a[i] + 1) //left
			tmp = (tmp + (a[i] - 1) - (a[j] - a[i]) + MOD) % MOD;
		if (a[j] - 1 >= a[j] - a[i] + 1) //mid
		{
			int L = max(a[i] + 1, a[j] - a[i] + 1);
			tmp = (tmp + a[j] - L) % MOD;
		}
	}
	return tmp;
}

long long getThr()
{
	long long tmp = 0;
	REPP(i, 2, m - 1)
	{
		int r = i, totOk = 0;
		REPP(j, 0, i - 2)
		{
			for (; (r - 1 > j && a[j] + a[r - 1] > a[i]); --r, ++totOk);
			if (r > j) tmp = (tmp + totOk) % MOD;
			else tmp = (tmp + i - 1 - j + MOD) % MOD;
		}
	}
	return tmp;
}

int main()
{
	freopen("in.txt", "r", stdin);
	int task, ca;
	long long ans = 0;
	scanf("%d", &ca);
	for (task = 1; task <= ca; ++task)
	{
		scanf("%d%d", &n, &m);
		REP(i, m) scanf("%d", &a[i]);
		sort(a, a + m);
		/*printf("%lld\n", getZero());
		printf("%lld\n", getOne());
		printf("%lld\n", getTwo());
		printf("%lld\n", getThr());*/
		ans = getZero();
		ans = (ans - getOne() + MOD) % MOD;
		ans = (ans + getTwo()) % MOD;
		ans = (ans - getThr() + MOD) % MOD;
		printf("Case %d: %lld", task, ans);
		if (task == ca) printf("\n");
		else printf("\n");
	}
	return 0;
}
