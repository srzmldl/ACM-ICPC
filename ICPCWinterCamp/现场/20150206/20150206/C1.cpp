#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int a[10], n;

int com(int u, int v)
{
	return u > v;
}

long long findOne()
{
	return a[1];
}

long long findTwo()
{
	return 1LL * a[1] + a[2] - 1;
}

long long findThree()
{
	return 1LL * a[1] + a[2] + a[3] - 3;
}

long long findFour()
{
	int i = 0;
	for (; i + 1 <= 4 && a[i + 1] == 3; ++i);
	if (i <= 1) return 4;
	else if (i <= 2) return 5;
	else return 6;
}

long long findFive()
{
	if (a[1] == 2)
		return 4;
	if (a[1] == 3)
	{
		int i = 0;
		for (; i + 1 <= 5 && a[i + 1] == 3; ++i);
		if (i <= 2) return 5;
		else if (i <= 4) return 6;
		else return 7;
	}

	long long tmp = 4;
	REPP(i, 1, 4)
		a[i] = a[i + 1] - 1;
	if (a[1] == 0) return tmp;
	else if (a[1] == 1)
	{
		return tmp + 1;
	} else
	if (a[1] == 2)
	{		
		int i = 0;
		for (; i + 1 <= 4 && a[i + 1] == 2; ++i);
		if (i <= 0) return tmp + 1;
		else if (i <= 1) return tmp + 2;
		else if (i <= 3) return tmp + 3;
		else return tmp + 4;
	} else if (a[1] == 3)
	{
		tmp += 3;
		REPP(i, 1, 3)
			a[i] = a[i + 1] - 1;
		if (a[1] == 0) return tmp;
		else if (a[1] == 1) return tmp + 1;
		else 
		{
			if (a[2] <= 1) return tmp + 2;
			else return tmp + 3;
		}
	}

}

int main() {
	ios :: sync_with_stdio(0);
//	freopen("C1.in", "r", stdin);
	scanf("%d", &n);
	REPP(i, 1, n)
		scanf("%d", a + i);
	sort(a + 1, a + 1 + n, com);
	long long ans = 0;
	if (n == 1) ans = findOne();
	else if (n == 2) ans = findTwo();
	else if (n == 3) ans = findThree();
	else 
	{
		REPP(i, 1, n)
			if (a[i] > n - 1)
			{
				ans += a[i] - (n - 1);
				a[i] = n - 1;
			}
	
		if (n == 4) ans += findFour();
		else ans += findFive();
	}
	cout << ans << endl;
	return 0;
}
