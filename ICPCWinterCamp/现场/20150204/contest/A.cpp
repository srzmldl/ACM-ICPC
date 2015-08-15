#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 212345

using namespace std;


int n, m, x, y;
long long a[MAXN];


int checkY(int boxNum, int tmpY)
{
	long long high = 1LL * x * (boxNum - 1) + tmpY + a[1];
	long long boxTot = boxNum;
	REPP(i, 2, n)
	{
		long long boxNow = 0;
		if (high <= a[i]) continue;
		boxNow = (high - a[i]) / x;
		if ((high - a[i]) % x != 0)
			boxNow++;
		boxTot += boxNow;
		if (boxTot > m) return 0;
	}
	if (boxTot > m) return 0;
	return 1;
}

int checkBox(int boxNum, int &tmpY)
{
	
	int l = 0, r = y;
	if (!checkY(boxNum, 0)) return 0;
	for (; l < r;)
	{
		int mid = (l + r + 1) >> 1;
		if (checkY(boxNum, mid))
			l = mid;
		else r = mid - 1;
	}
	tmpY = l;
	return 1;
}

long long work()
{
	int lbox = 0, rbox = m;
	int maxY = 0;
	for (; lbox < rbox;)
	{
		int tmpY;
		int mid = (lbox + rbox + 1) >> 1;
		if (checkBox(mid, tmpY))
		{
			lbox = mid;
			maxY = tmpY;
		} else 
		{
			rbox = mid - 1;
		}
	}
	return 1LL * lbox * x + maxY + a[1];
}

int main() {
	ios :: sync_with_stdio(0);
//	freopen("A.in", "r", stdin);
	scanf("%d%d%d%d", &n, &m, &x, &y);
	REPP(i, 1, n)
		scanf("%lld", a + i);
	long long aori = a[1];
	long long ans = a[1] + y;
	if (y < x)
	{
		ans = max(ans, work());
	} else 
	{
		int yori = y;
		y = x - 1;
		a[1] += 1LL * x * (yori / x - 1);
		ans = max(ans, work());
		y = yori % x;
		a[1] = aori + 1LL * x * (yori / x);
		ans = max(ans, work());
	}
	cout << ans << endl;
	return 0;
}
