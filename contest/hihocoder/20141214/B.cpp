#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MO 3214567
#define MU 31
#define MAXN 111111

using namespace std;

struct node
{int x, y;} a[MAXN];

int sqr(int x)
{return x * x;};
int main()
{
	freopen("Bin.txt", "r", stdin);
	int task, n;
	for (scanf("%d", &task); task; --task)
	{
		double ans = 0;
		scanf("%d", &n);
		printf("%d\n", n);
		REP(i, n) scanf("%d%d", &a[i].x, &a[i].y);
		REP(i, n)
		{
			node u = a[i];
			node v = a[(i + 1) % n];
			ans += 0.5 * (v.y - u.y) * (sqr(v.x) - sqr(u.x));
			ans += 0.5 * (sqr(v.y) - sqr(u.y)) * (v.x - u.x);
		}
		printf("%.2f\n", ans);
	}
	return 0;
}
