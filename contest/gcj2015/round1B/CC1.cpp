#include <bits/stdc++.h>

using namespace std;

struct Per
{
	double pos, ti, ver;
	Per() {}
	Per(double p, double t)
	{
		pos = p;
		ti = t;
		ver = 360.0 / ti;
	}
};

int main()
{
	freopen("C-small-1-attempt4.in", "r", stdin);
	freopen("C-small-1-attempt4.out", "w", stdout);
	// freopen("C.in", "r", stdin);
	// freopen("C1.out", "w", stdout);
	// freopen("1.in", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int ca = 1; ca <= T; ca++)
	{
		int n;
		scanf("%d", &n);
		vector<Per> per;
		for (int i = 0; i < n; i++)
		{
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			for (int j = 0; j < y; j++)
				per.push_back(Per(x, z + j));
		}

		// if (cmp(per[0].ti, per[1].ti) == 0)
		// {
		// 	printf("Case #%d: %d\n", ca, 0);
		// 	continue;
		// }

		int ans = 0;
		if (per[0].pos > per[1].pos)
			swap(per[0], per[1]);

		if (per[0].ti > per[1].ti)
		{
			double t1 = (360.0 - per[0].pos) / 360.0 * per[0].ti;
			double t2 = (720.0 - per[1].pos) / 360.0 * per[1].ti;
			if (t1 >= t2)
				ans = 1;
		} else
		{
			double tmp = (per[1].pos - per[0].pos) * 1.0 / (360.0 / per[0].ti + 360.0 / per[1].ti);
			for (int i = 0; i < 2; i++)
				per[i].pos += tmp * 360.0 / per[i].ti;
			if (per[0].pos < 360.0)
			{
				swap(per[0], per[1]);
				double t1 = (360.0 - per[0].pos) / 360.0 * per[0].ti;
				double t2 = (720.0 - per[1].pos) / 360.0 * per[1].ti;
				if (t1 <= t2)
					ans = 1;
			}
		}
        printf("Case #%d: %d\n", ca, ans);

		// if (cmp(per[0].ti, per[1].ti) == 0)
		// {
		// 	printf("Case #%d: %d\n", ca, 0);
		// 	continue;
		// }

		// if (cmp(per[0].ver, per[1].ver) == -1)
		// {
		// 	double ti = 360.0 - per[1].pos + per[0].pos;
		// 	ti /= per[1].ver - per[0].ver;
		// 	double des = per[0].pos + ti * per[0].ver;
		// 	if (cmp(des, 360.0) < 0)
		// 		printf("Case #%d: %d\n", ca, 1);
		// 	else
		// 		printf("Case #%d: %d\n", ca, 0);
		// 	continue;
		// }

		// if (cmp(per[0].ver, per[1].ver) == 1)
		// {
		// 	double t1 = per[1].pos - per[0].pos;
		// 	if (cmp(per[0].pos, per[1].pos) == 0)
		// 		t1 += 360;
		// 	t1 /= per[0].ver - per[1].ver;
		// 	double des1 = per[1].pos + t1 * per[1].ver;

		// 	if (cmp(des1, 360.0) > -1)
		// 	{
		// 		printf("Case #%d: %d\n", ca, 0);
		// 		continue;
		// 	}

		// 	double t2 = per[1].pos - per[0].pos + 360.0;
		// 	if (cmp(per[0].pos, per[1].pos) == 0)
		// 		t2 += 360;
		// 	t2 /= per[0].ver - per[1].ver;
		// 	double des2 = per[1].pos + t2 * per[1].ver;
		// 	if (cmp(des2, 360.0) < 0)
		// 		printf("Case #%d: %d\n", ca, 1);
		// 	else
		// 		printf("Case #%d: %d\n", ca, 0);
		// 	continue;
		// }
	}

	return 0;
}
