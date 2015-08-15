#include <bits/stdc++.h>

using namespace std;

int main()
{
	//long long pre = 10000000000;
	long long pre = 4;
	long long now = pre;
	long long ans = 0;
	while (now > 0)
	{
		long long x = (pre - 2) / 2;
		if (2 * x + 2 <= pre)
			x++;
		ans += now - x + 1;
		now = (x - 2) / 2;
		if (now * 2 + 2 >= x)
			now--;
		pre = now;
	}
	cout << ans << endl;
	return 0;
}
