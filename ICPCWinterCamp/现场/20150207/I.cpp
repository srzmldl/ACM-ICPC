#include <bits/stdc++.h>

#define EPS 1e-8
#define INF 99999999

using namespace std;

struct Point
{
	double x, y;
	Point(double x, double y) : x(x), y(y) {}
	Point operator - (Point a)
	{
		return Point(x - a.x, y - a.y);
	}
};

double det(Point v1, Point v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

int cmp(double x, double y)
{
	if (x < y - EPS)
		return -1;
	if (x > y + EPS)
		return 1;
	return 0;
}

bool jud[100100];

int main()
{
	freopen("1.in", "r", stdin);
	int n;
	double H;
	scanf("%d %lf", &n, &H);
	vector<int> tow;
	vector<Point> p;
	for (int i = 0; i < n; i++)
	{
		int z;
		double x, y;
		scanf("%lf %lf %d", &x, &y, &z);
		p.push_back(Point(x, y));
		if (z)
			tow.push_back(i);
	}
	vector<Point> c;
	vector< pair<double , int> > seg;
	for (int i = 0; i < tow.size(); i++)
	{
		cout << tow[i] << endl;
		for (int k = 0; k < c.size(); k++)
			cout << c[k].x << " " << c[k].y << endl;
		cout << endl;
		int m;
		int now = tow[i];
		double x = p[now].x;
		double y = p[now].y;
		Point p0 = p[now];
		while ((m = c.size()) > 1 && cmp(det(c[m - 2] - p0, c[m - 1] - p0), 0) > -1)
			c.pop_back();
		while (c.size() && cmp(c[c.size() - 1].y, p0.y) < 1)
			c.pop_back();
		if (!c.size())
		{
			seg.push_back(make_pair(-INF, -(now + 1)));
			c.push_back(p0);
			continue;
		}
		m = c.size() - 1;
		double tmp = x + (c[m].x - x) * ((H - y) / (c[m].y - y));
		seg.push_back(make_pair(tmp, -(now + 1)));
		c.push_back(p0);
	}
	c.clear();
	for (int i = tow.size() - 1; i >= 0; i--)
	{
		int m;
		int now = tow[i];
		double x = p[now].x;
		double y = p[now].y;
		Point p0 = p[now];
		while ((m = c.size()) > 1 && cmp(det(c[m - 2] - p0, c[m - 1] - p0), 0) < 1)
			c.pop_back();
		while (c.size() && cmp(c[c.size() - 1].y, p0.y) < 1)
			c.pop_back();
		if (!c.size())
		{
			seg.push_back(make_pair(INF, now + 1));
			c.push_back(p0);
			continue;
		}
		m = c.size() - 1;
		double tmp = x + (c[m].x - x) * ((H - y) / (c[m].y - y));
		seg.push_back(make_pair(tmp, now + 1));
		c.push_back(p0);
	}
	int ans = 0, done = 0;
	sort(seg.begin(), seg.end());
	for (int i = 0; i < seg.size(); i++)
		cout << seg[i].first << " " << seg[i].second << endl;
	for (int i = 0; i < seg.size(); i++)
	{
		int now = seg[i].second;
		if (now <= 0)
			continue;
		if (!jud[now - 1])
		{
			ans++;
			while (done < i)
			{
				if (seg[done].second < 0)
				jud[-seg[done].second - 1] = true;
				done++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
