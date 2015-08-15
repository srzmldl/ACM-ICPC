#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXN  25

using namespace std;


double E[MAXN], ppow[MAXN], oneppow[MAXN];
double c[MAXN][MAXN];

int main()
{
	freopen("B.txt", "r", stdin);
	freopen("B.out", "w", stdout);
	c[0][0] = 1;
	REPP(i, 1, 20)
	{
		c[i][0] = 1;
		REPP(j, 1, i)
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
	}
	
	int T;
	scanf("%d", &T);
	for(int task = 1; task <= T; ++task)
	{
		double p;
		scanf("%lf", &p);
		oneppow[0] = 1;
		REPP(i, 1, 20)
			oneppow[i] = oneppow[i - 1] * (1 - p);
		ppow[0] = 1;
		REPP(i, 1, 20)
			ppow[i] = ppow[i - 1] * p;
		E[0] = 0;
		REPP(i, 1, 20)
		{
			double sum = 0;
			REPP(j, 1, i)
				sum += c[i][j] * E[i - j] * ppow[j] * oneppow[i - j];
			sum = (sum + 1) / (1 - oneppow[i]);
			E[i] = sum;
		}
		printf("Case #%d: %.5f\n", task, E[20]);
	}

	return 0;
}
