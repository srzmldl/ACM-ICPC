#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 112
#define INFDouble 1e20
#define EPS 1e-6

using namespace std;
typedef int arrayN[MAXN];

arrayN S, T, match;
int n;
double lx[MAXN], ly[MAXN], w[MAXN][MAXN];

struct node
{
	int x, y;
}a[MAXN], b[MAXN];

int sqr(int x)
{
	return x * x;
}

int cmp(double x)
{
	if (fabs(x) < EPS)
		return 0;
	if (x > 0) return 1;
	return -1;
}

double dist(node A, node B)
{
	return sqrt(1.0 * sqr(A.x - B.x) + sqr(A.y - B.y));
}

int dfs(int x)
{
	S[x] = 1;
	REPP(i, 1, n)
		if (cmp(lx[x] + ly[i] - w[x][i]) == 0 && !T[i])
		{
			T[i] = 1;
			if (!match[i] || dfs(match[i]))
			{
				match[i] = x;
				return 1;                
			}
		}
	return 0;
}

void update()
{
	double minSl = INFDouble;
	REPP(i, 1, n)
		REPP(j, 1, n)
		if (S[i] && !T[j])
			minSl = min(minSl, lx[i] + ly[j] - w[i][j]);
	REPP(i, 1, n)
	{
		if (S[i]) lx[i] -= minSl;
		if (T[i]) ly[i] += minSl;
	}
}
void KM()
{
	REPP(i, 1, n)
	{
		lx[i] = -INFDouble;
		ly[i] = 0.0;
		match[i] = 0;
		REPP(j, 1, n)
			lx[i] = max(lx[i], w[i][j]);
	}
	REPP(i, 1, n)
	{
		for(;;)
		{
			MST(S, 0);
			MST(T, 0);
			if (dfs(i)) break;
			else update();
		}
	}
}
int main()
{
	freopen("in.txt", "r", stdin);
	int flag = 0;
	for (; scanf("%d", &n) != EOF; )
	{
		if (flag) printf("\n");
		++flag;
		REPP(i, 1, n)
			scanf("%d%d", &b[i].x, &b[i].y);
		REPP(i, 1, n)
			scanf("%d%d", &a[i].x, &a[i].y);
		REPP(i, 1, n)
			REPP(j, 1, n)
			w[i][j] = -1.0 * dist(a[i], b[j]);
		
		KM();
        double ans = 0;
		REPP(i, 1, n) {
			printf("%d\n", match[i]);
            ans += w[match[i]][i];
        }
        printf("%lf\n", ans);
	}
	return 0;
}
