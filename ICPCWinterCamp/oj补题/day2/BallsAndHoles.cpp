#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for (int i = 0; i < (int) (n); ++i) 
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 5123

using namespace std;

long long a[MAXN], b[MAXN];
int n;
const long long allOne = (1ll << 50) - 1;

int check(long long A, long long B)
{
	long long t1 = (B ^ allOne);
	t1 &= A;
	A -= t1;
	long long t2 = ((A + B) & allOne) | B;
	t2 -= B;
	return __builtin_parityll(t1 | t2);
	
}
int main()
{
	freopen("ball.txt", "r", stdin);
	scanf("%d", &n);
	REPP(i, 1, n)
	{
		int len;
		scanf("%d", &len);
		a[i] = 0;
		b[i] = allOne;
		REP(j, len)
		{
			int x;
			scanf("%d", &x);
			long long tmp = 1LL << (x - 1);
			a[i] += tmp;
			b[i] -= tmp;
		}
	}
	int ans = 0;
	REPP(i, 1, n)
		REPP(j, i + 1, n)
		ans += check(a[i], b[j]);
	printf("%d\n", ans);
	return 0;
}

