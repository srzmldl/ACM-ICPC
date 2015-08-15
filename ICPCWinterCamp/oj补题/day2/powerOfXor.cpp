#include <bits/stdc++.h>
#define MAXN 45
#define CUT 26
#define MAXSTA ((1 << 18) - 1)
#define MOD 1000000007

using namespace std;

int n, k, powk[100];
int f[CUT + 5][MAXSTA + 10], g[CUT + 5][MAXSTA + 10];
int oneCnt[1 << 14];
//oneNum[(1 << 26) + 5];
long long a[50];

const int pl = 26, pr = 18;
const int lll = 14;

void add(int &u, int v)
{
        u += v;
        if (u > MOD) u -= MOD;
}

void Gauss()
{
        int last = 0;
        for (int i = 43; i >= 0 && last < n; --i)
        {
                int now = 0;
                for (int j = last + 1; j <= n; ++j)
                        if ((1LL << i) & a[j])
                        {now = j; break;}
                if (now)
                {
                        swap(a[now], a[last + 1]);
                        last++;
                        for (int j = 1; j <= n; ++j)
                                if (j != last && ((1LL << i) & a[j]))
                                        a[j] ^= a[last];
                }
        }
}

int oneNum(int x)
{
	return oneCnt[x >> lll] + oneCnt[x & ((1 << lll) - 1)];
}

void addOne(long long sta)
{
        long long L = sta >> pr;
        int tmp = L;
        add(f[oneNum(tmp)][sta - (L << pr)], 1);
}

void dfs(int now, long long sta, int lim)
{
	if (now == lim)
	{
		addOne(sta);
		return ;
	}
	now++;
	dfs(now, sta, lim);
	dfs(now, sta ^ a[now], lim);
}

/*void dfsOneNum(int now, int num, int lim, int sta)
  {
  oneNum[sta] = num;
        if (now == lim) return ;
        now++;
        dfsOneNum(now, num, lim, sta);
        dfsOneNum(now, num + 1, lim, sta + (1 << (now - 1)));
        }*/

int findLast()
{
        long long tmp = (1LL << pl) - 1;
        tmp <<= pr;
        for (int i = 1; i <= n; ++i)
                if (!(a[i] & tmp)) return i - 1;
        return n;
}

int mul(int u, int v)
{
        return (int) (1LL * u * v % MOD);
}

int quick_pow(int x, int e)
{
        if (e == 0) return 1;
        long long tmp = x;
        for (e--; e; e >>= 1)
        {
                if (e & 1) tmp = tmp * x % MOD;
                x = 1LL * x * x % MOD;
        }
        return (int) tmp;
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (int i = 1; i <= 1 << lll; ++i)
		oneCnt[i] = __builtin_popcount(i);
	//dfsOneNum(0, 0, pl, 0);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%lld", a + i);
	//n = 44; 
//	k = 1000000000;
	//for (int i = 1; i <= n; ++i) a[i] = (1LL << (n - 1));
        Gauss();
        int endOne = findLast();
        dfs(0, 0, endOne);

		int mo18 = (1 << pr) - 1;
        for (int ii = endOne + 1; ii <= n; ++ii)
        {
			for (int j = 0; j <= pl; ++j)
					for (int k = 0; k < (1 << pr); ++k)
						g[j][k] = 0;
			int laNum = a[ii] & mo18;
			for (int j = 0; j <= pl; ++j)
					for (int k = 0; k < (1 << pr); ++k)
						if (f[j][k])
						{
							add(g[j][k], f[j][k]);
							int tmp = k ^ laNum;
							add(g[j][tmp], f[j][k]);
						}
				for (int j = 0; j <= pl; ++j)
						for (int k = 0; k < (1 << pr); ++k)
							f[j][k] = g[j][k];
        }
        int ans = 0;
        for (int i = 1; i <= 44; ++i)
                powk[i] = quick_pow(i, k);
        for (int i = 0; i <= pl; ++i)
                for (int j = 0; j < (1 << pr); ++j)
                        add(ans, mul(f[i][j], powk[i + oneNum(j)]));
        printf("%d\n", ans);
        return 0;
}
