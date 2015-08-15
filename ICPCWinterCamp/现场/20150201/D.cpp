#include <bits/stdc++.h>

#define lim 1000

using namespace std;

double x1, y11, x2, y2, x3, y3;

double sqr(double x)
{
	return x * x;
}

double f(double x, double y)
{
	return sqrt(sqr(x - x1) + sqr(y - y11)) + 2 * sqrt(sqr(x - x2) + sqr(y - y2)) + 3 * sqrt(sqr(x - x3) + sqr(y - y3));
}

double calc(double x)
{
	double ly = -10010, ry = 10010;
	for (int k = 0; k < lim; k++)
	{
		double m1 = (ry - ly) / 3;
		double m2 = ry - m1;
		m1 = ly + m1;
		double l1 = f(x, m1);
		double l2 = f(x, m2);
		if (l1 < l2)
			ry = m2;
		else
			ly = m1;
	}
	return f(x, ly);
}

int main()
{
	scanf("%lf %lf %lf %lf %lf %lf", &x1, &y11, &x2, &y2, &x3, &y3);
	double lx = -10010, rx = 10010;
	double l1, l2;
	for (int k = 0; k < lim; k++)
	{
		double m1 = (rx - lx) / 3;
		double m2 = rx - m1;
		m1 = lx + m1;
		l1 = calc(m1);
		l2 = calc(m2);
		if (l1 < l2)
			rx = m2;
		else
			lx = m1;
	}
	l1 = min(l1, f(x1, y11));
	l1 = min(l1, f(x2, y2));
	l1 = min(l1, f(x3, y3));
	printf("%.9f\n", l1);
	return 0;
}
