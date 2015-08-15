#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))

#define MAXN 2123456 

using namespace std;

int n;

struct node
{
	int son[26];
	int tot;
} a[MAXN];

char st[MAXN];


int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out2.txt", "w", stdout);
	int task;
	scanf("%d", &task);
	REPP(t, 1, task)
	{
		scanf("%d", &n);
		MST(a, 0);
		int root = 0, num = 0, ans = 0;
		a[root].tot = 100;
		REPP(i, 1, n)
		{
			scanf("%s", st);
			int tmp = root;
			int len = strlen(st);
			REP(j, len)
			{
				if (a[tmp].son[st[j] - 'a'])
					tmp = a[tmp].son[st[j] - 'a'];
				else 
				{
					a[tmp].son[st[j] - 'a'] = ++num;
					tmp = num;
				}
				a[tmp].tot++;
			}
			
			tmp = root;
			REP(j, len)
			{
				tmp = a[tmp].son[st[j] - 'a'];
				ans++;
				if (a[tmp].tot <= 1) break;
			}
		}
		printf("Case #%d: %d\n", t, ans);
	}
	return 0;
}
