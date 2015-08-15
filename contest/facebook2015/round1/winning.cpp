#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))

#define MAXN 4123 
#define MO 1000000007

using namespace std;

int n;

struct node
{
	int son[26];
	int tot;
} a[MAXN];

char st[MAXN];
int f[MAXN][MAXN];

int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out3.txt", "w", stdout);
	int task;
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		int n, m;
		scanf("%d-%d", &n, &m);
		MST(f, 0);
		f[1][0] = 1;
		REPP(i, 2, n)
			REPP(j, 0, i - 1)
		{
			f[i][j] = f[i - 1][j];
			if (j > 0) 
				f[i][j] = (f[i][j] + f[i][j - 1]) % MO;
		}
		
		int ans1 = f[n][m];
		MST(f, 0);
		f[0][0] = 1;
		REPP(i, 0, m)
			REPP(j, 0, i)
		{
			if (i > 0) f[i][j] = (f[i][j] + f[i - 1][j]) % MO;
			if (j > 0) f[i][j] = (f[i][j] + f[i][j - 1]) % MO;
		}
		int ans2 = f[m][m];
		
		printf("Case #%d: %d %d\n", t, ans1, ans2);
	}
	return 0;
}
