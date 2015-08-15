#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MO 1000000007

using namespace std;

long long A;

long long mul(long long u, long long v)
{
	return (u % MO) * (v % MO) % MO;
}

long long sub(long long u, long long v)
{
	long long tmp = (u % MO) - (v % MO);
	if (tmp < 0) tmp += MO;
	return tmp % MO;
}

long long add(long long u, long long v)
{
	return ((u % MO) + (v % MO)) % MO;
}

long long calcOne(long long u, long long v)
{
	if (u & 1) return mul(u, v / 2);
	else return mul(u / 2, v);
}

long long calcTwo(long long u, long long v, long long w)
{
	if (u %2 == 0) u /= 2;
	else if (v % 2 == 0) v /= 2;
	else w /= 2;
	if (u % 3 == 0) u /= 3;
	else if (v % 3 == 0) v /= 3;
	else w /= 3;
	return mul(w, mul(u, v));
}

long long calc(long long c2, long long e2, long long c1, long long e1, long long c0)
{
	long long tmp = mul(c0, e1 + 1);
	tmp = add(tmp, mul(c1, calcOne(e1, 1 + e1)));
	tmp = add(tmp, mul(c2, calcTwo(e2, e2 + 1, e2 * 2 + 1)));
	return tmp;
}

int main() {
	ios :: sync_with_stdio(0);
//	freopen("D.out", "w", stdout);
	long long n;
	cin >> n;
//	for (long long h = 31; h <= 60; ++h)
//	{
	long long ans = 0;
//	long long n = h;
	n = n - n % 5;
	A = n / 5;
	if (A == 0)
	{
		cout << 1 << endl;
		//	continue;
		return 0;
	}
	long long k1 = A / 2;
	if (A & 1)
	{
		//==========A 2k1+ 1, d 2k2+1
		long long c2 = 25;
		long long c1 = sub(10LL, mul(10LL, k1));
		long long c0 = mul(sub(k1, 1LL), sub(k1, 1LL));
		long long tmp = A / 5;
		long long e2 = (tmp - 1) / 2;
		long long e1 = e2;
		if (tmp > 0)
			ans = add(ans, calc(c2, e2, c1, e1, c0));
//==========A 2k1+ 1, d 2k2
		
		e2 = tmp / 2;
		e1 = e2;
		c2 = 25;
		c1 = add(sub(0, 15LL), mul(sub(0LL, 10LL), k1));
		c0 = mul(add(k1, 1), add(k1, 2));
		ans = add(ans, calc(c2, e2, c1, e1, c0));

	} else 
	{
		//==========A 2k1, d 2k2
		long long c2 = 25;
		long long c1 = add(sub(0LL, 10LL), mul(sub(0LL, 10LL), k1));
		long long c0 = mul(add(k1, 1LL), add(k1, 1LL));
		long long tmp = A / 5;
		long long e2 = tmp / 2;
		long long e1 = tmp / 2;
		ans = add(ans, calc(c2, e2, c1, e1, c0));
//==========A 2k1+ 1, d 2k2 + 1
		
		e2 = (tmp - 1) / 2;
		e1 = e2;
		c2 = 25;
		c1 = sub(15LL, mul(10LL, k1));
		c0 = mul(sub(k1, 1), sub(k1, 2));
		if (tmp > 0)
			ans = add(ans, calc(c2, e2, c1, e1, c0));
	}
	cout << ans << endl;
//	}	
	return 0;
}
