#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int random(int x)
{
	return rand() % x;
}
int main() {
	ios :: sync_with_stdio(0);
	srand(time(0) % clock());
	freopen("D.in", "w", stdout);
	int n = 100;
	printf("%d\n", n);
	REPP(i, 1, n)
	{
		int x1 = random(50), y1 = random(50);
		int x2 = x1, y2 = y1;
		if (rand() & 1) x2++;
		else y2++;
		printf("%d %d %d %d\n", x1, y1, x2, y2);
	}
	return 0;
}
