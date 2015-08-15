#include <bits/stdc++.h>

#define EPS 1e-10

using namespace std;

int cmp(double x, double y)
{
	if (x < y - EPS)
		return -1;
	if (x > y + EPS)
		return 1;
	return 0;
}

double sqr(double x)
{
	return x * x;
}

int main()
{
	double d;
	scanf("%lf", &d);
	if (cmp(d, 1) == -1)
	{
		printf("%.10f\n", d * sqrt(2));
		return 0;
	}
	double ans = d * sqrt(2);
	double a, b;
	for (a = 10; cmp(a, 0) == 1; a -= 1)
	{
		if (cmp(a, d) > 0)
			continue;
		b = sqrt(sqr(d) - sqr(a));
		ans = max(ans, a + b);
		if (cmp(b, 1) == -1);
		ans = max(ans, a + 1);
	}
	printf("%.10f\n", ans);
	return 0;
}
