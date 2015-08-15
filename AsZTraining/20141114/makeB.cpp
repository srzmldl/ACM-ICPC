#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define mem(a) memset(a, 0, sizeof(a))

using namespace std;

int main()
{
	srand(time(0) % clock());
	freopen("E.in", "w", stdout);
    int T = 50;
    int task = 50;
    printf("%d\n", task);
    REP(t, task)
    {
		int n = 50;
		int m = 1000;
		int k = 5;
		int lim = 1000;
		printf("%d %d %d\n", n, m, k);
        REPP(i, 1, m)
        {
            int u = rand() % n +1;
            int v = rand() % n +1;
            for (; v == u; v = rand() % n +1);
            int w = rand() % lim + 1;
            printf("%d %d %d\n", u, v, w);
        }
    }
	return 0;
}
