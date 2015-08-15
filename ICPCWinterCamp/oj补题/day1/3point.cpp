#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for (int i = 0; i < (int) (n); ++i) 
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)

using namespace std;

struct node
{
	int x, y;
} a[3];

double sqr(int x)
{
	return 1.0 * x * x;
}

double dist(node A, node B)
{
	return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}

int main()
{
	freopen("3point.txt", "r", stdin);
	REP(i, 3)
		scanf("%d%d", &a[i].x, &a[i].y);
	printf("%.7lf", dist(a[2], a[0]) + 2 * dist(a[2], a[1]));
	return 0;
}

