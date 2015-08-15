#include <bits/stdc++.h>

using namespace std;

int vis[100][100];

int main()
{
	srand(time(0) % clock());
	freopen("walk.in", "w", stdout);
	int limx = 10, limy = 10;
	int x1 = rand() % limx;
	int y1 = rand() % limy;
	int x2 = rand() % limx;
	int y2 = rand() % limy;
	printf("%d %d %d %d\n", x1, y1, x2, y2);
	int n = 56;
	printf("%d\n", n);
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; ++i)
	{
		int x1 = rand() % limx;
		int y1 = rand() % limy;
		if (vis[x1][y1]) 
		{
			--i;
			continue;
		}
		printf("%d %d %d %d\n", x1, y1, x1 + 1, y1 + 1);
	}
	printf("0 0 0 0\n");
	return 0;
}
