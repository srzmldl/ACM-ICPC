#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MO 3214567
#define MU 31
#define MAXN 111111

using namespace std;

char S[MAXN], T[MAXN];
long long hs[MAXN], ht[MAXN], wq[MAXN];
int K, ns, nt;

int getSub(long long *arr, int l, int r, int kk)
{
	return ((arr[r] - arr[l - 1] + MO) % MO) * wq[kk] % MO;
}

int find(int xs, int xt)
{
	if (getSub(ht, xt, nt, xs + xt - 1) == getSub(hs, xs + xt - 1, xs + nt - 1, xt)) return nt + 1;
	if (getSub(ht, xt, xt, xs + xt - 1) != getSub(hs, xs + xt - 1, xs + xt - 1, xt)) return xt;
	int l = xt + 1, r = nt;
	for (; l < r; )
	{
		int mid = (l + r) >> 1;
		if (getSub(ht, xt, mid, xs + xt - 1) != getSub(hs, xs + xt - 1, xs + mid - 1, xt)) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main()
{
	freopen("ccin.in", "r", stdin);
	for (;scanf("%s", S) != EOF;)
	{
		scanf("%s", T);
		scanf("%d", &K);
		ns = strlen(S);
		nt = strlen(T);
		hs[0] = 0;
		ht[0] = 0;
		hs[ns + 1] = 0;
		ht[nt + 1] = 0;
		wq[1] = 1;
		REPP(i, 1, ns)
		{
			hs[i] = (hs[i - 1] + (S[i - 1] - 'a') * wq[i]) % MO;
			wq[i + 1] = wq[i] * MU % MO;
		}
		wq[1] = 1;
		REPP(i, 1, nt)
		{
			ht[i] = (ht[i - 1] + wq[i] * (T[i - 1] - 'a')) % MO;
			wq[i+1] = wq[i] * MU % MO;
		}
		
		int ans = 0;
		REPP(i, 1, ns)
		{
			int j = 1;
			if (i + nt - 1 > ns) break;
			int h = 0;
			for (; ;)
			{
				j = find(i, j);
				if (j <= nt)
				{
					++h;
					if (h > K) break;
					++j;
				}
				if (j > nt)
				{
					ans ++;
					break;
				}
			}
		}
		printf("%d\n", ans);

	}
	return 0;
}
