#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MO 1000000007
#define MAXN 111111

using namespace std;
long long pow2[MAXN], jc[MAXN];

long long add(long long u, long long v)
{
	return ((u % MO) + v % MO) % MO;
}

long long mul(long long u, long long v)
{
	return (u % MO) * (v % MO) % MO;
}

long long calc1(int len)
{
	int tmp = (len - 1) * len / 2 - (len - 1);
	return pow2[tmp];
}

long long calc2(int len)
{
	long long tmp = 0;
/*	long long pe = (len - 1) * len / 2 - (len - 1);
	tmp = mul(2LL, pow2[pe]);
	pe = (len - 1) * len / 2 - (len - 1) - 1;
	tmp = mul(len - 3LL, add(tmp, pow2[pe]));
	return tmp;*/
	REPP(i, 0, len - 2)
	{
		long long pe = 0;
		REPP(j, 1, i - 1)
			pe += max(0, len - j - 1);
		if (i > 0)
			pe += max(len - i - 2, 0);
		pe += 2 * max(0, (len - i - 3));
		REPP(j, i + 3, len)
			pe += max(0, len - j - 1);
		tmp = add(tmp, pow2[pe]);
	}
	return tmp;
}

long long calc3(int len)
{
	long long tmp = 0;
	//last len - 3, 1 left
	long long pe = 0;
	REPP(i, 1, len - 4)
		pe += max(0, len - i - 1);
	if (len - 3 > 0) pe += 1;
	tmp = pow2[pe];

	REPP(i, 0, len - 4)
	{
		pe = 0;
		REPP(j, 1, i - 1)
			pe += max(0, len - j - 1);
		if (i) pe += len - i - 2;
		pe += 2 * (len - i - 1 - 3);
		pe += len - i - 3;
		REPP(j, i + 4, len)
			pe += max(0, len - j - 1);
		tmp = add(tmp, pow2[pe]);
	}
	return tmp;
}


int main() {
	ios :: sync_with_stdio(0);
	int n;
	scanf("%d", &n);
	long long ans1 = 0, ans2 = 0, ans3 = 0;
	jc[0] = 1, pow2[0] = 1;
	REPP(i, 1, (n * n))
	{
		jc[i] = mul(jc[i - 1], 1LL * i);
		pow2[i] = mul(pow2[i - 1], 2LL);
	}

	if (n == 1)
	{
		ans1 = 1;
	} 
	else if (n == 2)
	{
		ans1 = 2;
		ans2 = 1;
		ans3 = 0;
	} else 
	{
		ans1 = mul(jc[n], add(ans1, calc1(n)));
		ans2 = calc2(n);
		REPP(i, 3, n)
			ans2 = mul(ans2, i * 1LL);
		ans3 = mul(jc[n], add(ans3, calc3(n)));
	}
	cout << ans1 << endl << ans2 << endl << ans3 << endl;
	return 0;
}
