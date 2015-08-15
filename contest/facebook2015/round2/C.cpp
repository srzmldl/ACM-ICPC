#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define REPP(i, a, b) for(int i = (a); i <= (b); ++i)
#define MAXLEN 62334
#define INF 0x3f3f3f3f

using namespace std;

int T, N, K, root, sta[MAXLEN], num;
char st[MAXLEN];
int f[MAXLEN][111];

struct node
{
	int son[26];
	int tot;
	int term;
} a[MAXLEN];

int son[101];
int g0[222], g1[222];

int main()
{
	freopen("C.txt", "r", stdin);
	freopen("C.out", "w", stdout);
	scanf("%d", &T);
	REPP(task, 1, T)
	{
		scanf("%d%d", &N, &K);
		MST(a, 0);

		root = 0;
		num = 0;
		REPP(i, 1, N)
		{
			scanf("%s", st);
			
			int tmp = root;
			int len = strlen(st);
			REP(j, len)
			{
				a[tmp].tot++;
				if (a[tmp].son[st[j] - 'a'])
					tmp = a[tmp].son[st[j] - 'a'];
				else 
				{
					a[tmp].son[st[j] - 'a'] = ++num;
					tmp = num;
				}
				if (j == len - 1)
					a[tmp].term = 1;
			}
		}
		
		{
			int l = 1, r = 1;
			sta[1] = root;
			for (;l <= r; )
			{
				int tmp = sta[l++];
				REP(i, 26)
					if (a[tmp].son[i])
						sta[++r] = a[tmp].son[i];
			}
		}
		MST(f, 0x3f);
		for (int i = num + 1; i >= 0; --i)
		{
			int rt = sta[i];
			f[rt][0] = 0;
			son[0] = 0;
			REP(j, 26)
				if (a[rt].son[j])
					son[++son[0]] = a[rt].son[j];
			if (son[0] == 0) continue;
			f[rt][1] = 1;
			int j = min(K, a[rt].tot);
			REPP(i1, 0, j)
				g1[i1] = g0[i1] = INF;
			g0[0] = 0; 
			REPP(i1, 1, son[0])
			{
				int u = son[i1];
				g1[0] = 0;
				REPP(j1, 1, j) g1[j1] = INF;
				REPP(j1, 0, j)
				{
					g1[j1] = min(g1[j1], g0[j1]);
					if (j1 + 1 <= j)
						g1[j1 + 1] = min(g1[j1 + 1], g0[j1] + 1);
					REPP(k1, 2, j - j1)
					{
						g1[j1 + k1] = min(g1[j1 + k1], g0[j1] + f[u][k1] + k1); 
						if (a[u].term)
						{
							g1[j1 + k1] = min(g1[j1 + k1], g0[j1] + f[u][k1 - 1] + k1); 
						}
					}
				}
				REPP(j1, 0, j)
					g0[j1] = g1[j1];
			}
			REPP(i1, 2, j)
				f[rt][i1] = g0[i1];
		
		}

		printf("Case #%d: %d\n", task, f[0][K]);

		

	}
	return 0;
}
