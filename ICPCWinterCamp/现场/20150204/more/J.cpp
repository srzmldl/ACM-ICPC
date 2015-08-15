#include <bits/stdc++.h>

using namespace std;

vector <int> a[2];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		int x;
		scanf("%d", &x);
		a[0].push_back(x);
	}

	int now = 1, pre = 0;
	int ans = 0;
	for (int k = 30; k >= 0; k--)
	{
		int z = 1 << k;
		vector<int> b;
		for (int i = 0; i < a[pre].size(); i++)
			if (a[pre][i] & z)
				b.push_back(i);
		if (b.size() % 2)
		{
			ans += z;
			continue;
		}
		int sub = 0;
		for (int i = 0; i < b.size(); i += 2)
			sub += b[i + 1] - b[i];
		if (a[pre].size() - sub < m)
		{
			ans += z;
			continue;
		}
		int p1, p2;
		p1 = p2 = 0;
		a[now].clear();
		while (p1 < a[pre].size())
		{
			if (p2 < b.size() && p1 == b[p2])
			{
				int tmp = 0;
				for (int i = b[p2]; i <= b[p2 + 1]; i++)
					tmp ^= a[pre][i];
				a[now].push_back(tmp);
				p1 = b[p2 + 1] + 1;
				p2 += 2;
			} else
			{
				a[now].push_back(a[pre][p1]);
				p1++;
			}
		}
//		for (int i = 0; i < a[now].size(); i++)
//			printf("%d%c", a[now][i], " \n"[i == a[now].size() - 1]);
//		for (int i = 0; i < b.size(); i++)
//			printf("%d%c", b[i], " \n"[i == b.size() - 1]);
		now = pre, pre ^= 1;
	}

	cout << ans << endl;

	return 0;
}
