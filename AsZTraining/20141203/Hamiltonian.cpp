#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MOD 9901
#define MAXN 330

using namespace std;
typedef int arrayN[MAXN];

struct node
{int u, v;} ed[MAXN];
arrayN f, deg, sizeNum, jcdiv2;
int N, K, tpow[20], jc[MAXN];

int getfa(int x)
{
	return x == f[x] ? x : (f[x] = getfa(f[x]));
}

int getBitNum(int x)
{
	int tmp = 0;
	for (; x; x >>= 1)
		tmp += (x & 1);
	return tmp;
}

int getAns(int sta)
{
	REPP(i, 1, N)
	{
		f[i] = i, deg[i] = 0;
		sizeNum[i] = 1;
	}
	REP(i, K)
		if ((1 << i) & sta)
		{
			int u = ed[i].u;
			int v = ed[i].v;
			deg[u]++, deg[v]++;
			if (deg[u] >= 3 || deg[v] >= 3) return 0;
			int fu = getfa(u), fv = getfa(v);
			if (fu != fv) f[fu] = fv, sizeNum[fv] += sizeNum[fu];
			else return 0;
		}
	int a = 0, b = 0;
	REPP(i, 1, N)
		if (f[i] == i)
		{
			if (sizeNum[i] == 1) ++b;
			else ++a;
		}
	if (a == 0) return jcdiv2[b - 1];
	return (jc[a + b - 1] * tpow[a - 1] % MOD);
}

int main()
{
	freopen("Hamiltonian.txt", "r", stdin);
	int task, ca;
	scanf("%d", &task);
	tpow[0] = 1;
	REPP(i, 1, 16) tpow[i] = tpow[i - 1] * 2 % MOD;
	jc[0] = 1;
	REPP(i, 1, MAXN - 1) jc[i] = jc[i - 1] * i % MOD;
	jcdiv2[0] = jcdiv2[1] = jcdiv2[2] = 1;
	REPP(i, 3, MAXN - 1) jcdiv2[i] = jcdiv2[i - 1] * i % MOD;
	for (ca = 1; ca <= task; ++ca)
	{
		scanf("%d%d", &N, &K);
		REP(i, K) scanf("%d%d", &ed[i].u, &ed[i].v);
		int ans = 0;
		REP(i, (1 << K))
		{
			int bitNum = getBitNum(i);
			int signal = 1;
			if (bitNum & 1) signal = -1;
			ans = (ans + signal * getAns(i) + MOD) % MOD;
		}
		printf("Case #%d: %d\n", ca, ans);
	}
	return 0;
}
