#include <bits/stdc++.h>

#define EPS 1e-8

using namespace std;

struct Point
{
	double x, y, z;
	Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
	Point operator - (Point a)
	{
		return Point(x - a.x, y - a.y, z - a.z);
	}
	Point operator * (double k)
	{
		return Point(x * k, y * k, z * k);
	}
	Point operator / (double k)
	{
		return Point(x / k, y / k, z / k);
	}
} p[3], v[3];

double ymi, yma;
double x[3], y[3];

int cmp(double x, double y)
{
	if (x > y + EPS)
		return 1;
	if (x < y - EPS)
		return -1;
	return 0;
}

double sqr(double x)
{
	return x * x;
}

double len(Point v)
{
	return sqrt(sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double dot(Point v1, Point v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double dist(Point v1, Point v2)
{
	return sqrt(sqr(v1.x - v2.x) + sqr(v1.y - v2.y) + sqr(v1.z - v2.z));
}

double f(double xx, double yy)
{
	double res = 0;
	for (int i = 0; i < 3; i++)
		res += sqrt(sqr(xx - x[i]) + sqr(yy - y[i]));
	return res;
}

double calc(double x)
{
	double l1, l2;
	double l = ymi, r = yma;
	for (int i = 0; i < 100; i++)
	{
		double m1 = (r - l) / 3;
		double m2 = r - m1;
		m1 = l + m1;
		l1 = f(x, m1);
		l2 = f(x, m2);
		if (l1 < l2)
			r = m2;
		else
			l = m1;
	}
	return l1;
}

int main()
{
	freopen("1.in", "r", stdin);
	for (int i = 0; i < 3; i++)
	{
		double x, y, z;
		scanf("%lf %lf %lf", &x, &y, &z);
		p[i] = Point(x, y, z);
	}
	for (int i = 0; i < 3; i++)
		if (cmp(dist(p[i], p[(i + 1) % 3]) + dist(p[(i + 1) % 3], p[(i + 2) % 3]), dist(p[i], p[(i + 2) % 3])) == 0)
		{
			printf("%.6f\n", dist(p[i], p[(i + 2) % 3]));
			return 0;
		}
	for (int i = 0; i < 2; i++)
		v[i] = p[i + 1] - p[i];
	v[2] = p[0] - p[2];
	Point ex = v[0] / len(v[0]);
	Point ey = v[1] - ex * dot(v[1], ex);
	ey = ey / len(ey);
	x[0] = y[0] = 0;
	x[1] = len(v[0]), y[1] = 0;
	x[2] = -dot(v[2], ex), y[2] = -dot(v[2], ey);

//	for (int i = 0; i < 3; i++)
//		cout << x[i] << " " << y[i] << endl;


	ymi = min(y[0], min(y[1], y[2]));
	yma = max(y[0], max(y[1], y[2]));
	double l = min(x[0], min(x[1], x[2]));
	double r = max(x[0], max(x[1], x[2]));
	double l1, l2;
	for (int i = 0; i < 100; i++)
	{
		double m1 = (r - l) / 3;
		double m2 = r - m1;
		m1 = l + m1;
		l1 = calc(m1);
		l2 = calc(m2);
		//cout << l1 << " " << l2 << endl;
		if (l1 < l2)
			r = m2;
		else
			l = m1;
	}
	printf("%.6f\n", l1);
	return 0;
}
