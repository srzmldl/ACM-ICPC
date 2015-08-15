#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 300000

using namespace std;


char s[MAXN * 10], t[MAXN], tmp[MAXN * 10];

int find()
{
	int n = strlen(t);
	int m = strlen(s);
	REP(i, m)
		if (i + n - 1 <= m - 1)
		{
			int flag = 1;
			REPP(j, i, i + n - 1)
				if (s[j] != t[j - i])
				{
					flag = 0; 
					break;
				}
			if (flag) return 1;
		}
	return 0;
}

int main() {
	ios :: sync_with_stdio(0);
	
	scanf("%s", s);
	scanf("%s", t);
	for (int k = 0; k <= 6; ++k)
	{
		if (find())
		{
			printf("%d\n", k);
			return 0;
		}
		int len = strlen(s);
		for (int i = 0; i < len; ++i)
		{
			tmp[i * 2] = 'a'; 
			tmp[i * 2 + 1] = s[i];
		}
		tmp[2 * len] = '\0';
		REPP(i, 0, 2 * len)
			s[i] = tmp[i];
	}
	printf("-1\n");
	return 0;
}
