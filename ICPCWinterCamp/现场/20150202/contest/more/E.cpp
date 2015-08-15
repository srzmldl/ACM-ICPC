#include <bits/stdc++.h>

using namespace std;

void print(long long x, long long y)
{
	cout << x << " " << y << endl;
}

int main()
{
	long long s, l;
	cin >> l >> s;

	if (2 + 2 * s < l)
	{
		cout << "-1" << endl;
		return 0;
	}

 	long long a = l / 4, b = l / 2 - a;
	long long ds = a * b - s;
	if (ds < 0)
	{
		cout << "-1" << endl;
		return 0;
	}

	if (!ds)
	{
		cout << 4 << endl;
		print(0, 0);
		print(0, a);
		print(b, a);
		print(b, 0);
		return 0;
	}

	long long x = ds / (a - 1);
	long long y = ds % (a - 1);



	if (y)
	{
		if (x)
			cout << 8 << endl;
		else
			cout << 6 << endl;
		print(0, a);
		print(b - x - 1, a);
		print(b - x - 1, a - y);
		print(b - x, a - y);
		if (x)
		{
			print(b - x, 1);
			print(b, 1);
		}
		print(b, 0);
		print(0, 0);
	} else
	{
		if (x)
			cout << 6 << endl;
		else
			cout << 4 << endl;
		print(0, a);
		print(b - x, a);
		if (x)
		{
			print(b - x, 1);
			print(b, 1);
		}
		print(b, 0);
		print(0, 0);
	}

	return 0;
}
