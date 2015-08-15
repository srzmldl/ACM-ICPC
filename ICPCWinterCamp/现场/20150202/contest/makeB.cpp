#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

int main() {
	//ios :: sync_with_stdio(0);
	srand(time(0) % clock());
	int n = 15, m = 6;
	REPP(i, 1, n)
	{
		if (rand() & 1) putchar('a');
		else putchar('b');
	 }
	putchar('\n');
	REPP(i, 1, m)
	{
		if (rand() & 1) putchar('a');
		else putchar('b');
	}
	putchar('\n');
	return 0;
}
