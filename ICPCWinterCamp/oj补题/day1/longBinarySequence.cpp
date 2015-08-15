#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MAXN 1123
#define MOD1 1000000009
#define MOD2 1000000007 
#define MODHASH 3214567

using namespace std;

struct node
{
	int x, y;
	node(int x = 0, int y = 0) : x(x), y(y) {};
}g[MAXN * MAXN], d[MAXN * MAXN];

const int hashWeight1 = 31;
const int hashWeight2 = 313;

int n, m, a[MAXN];
long long ans = 0;
int firhs[MODHASH + 10], ehs1[MAXN * MAXN], nxths[MAXN * MAXN], numhs, ehs2[MAXN * MAXN];
int fir[MAXN * MAXN], nxt[MAXN * MAXN];

int getHash(int x1, int x2)
{
	int tmp = x1 % MODHASH;
	for (int p = firhs[tmp]; p; p = nxths[p])
		if (ehs1[p] == x1 && ehs2[p] == x2) return p;
	ehs1[++numhs] = x1;
	ehs2[numhs] = x2;
	nxths[numhs] = firhs[tmp];
	firhs[tmp] = numhs;
	return numhs;
}

int com(node u, node v)
{
	return u.y > v.y;
}

long long calc(int x)
{
	int cnt = 0;
	for (int p = fir[x]; p; p = nxt[p])
		d[cnt++] = g[p];
	sort(d, d + cnt, com);
	long long tmp = 0;
	int last = 0;
	REP(i, cnt)
	{
		int newLast = d[i].x;
		int j = i;
		for (; d[j + 1].y == d[i].y && j + 1 < cnt; ++j)
			newLast = max(newLast, d[j + 1].x);
		if (newLast > last)
		{
			tmp += 1LL * d[i].y * (newLast - last);
			last = newLast;
		}
		i = j;
	}
	return tmp;
}

void mul(int MOD, int &u, int v)
{
	u = (int)(1LL * u * v % MOD);
}

void add(int MOD, int &u, int v)
{
	u =  (u + v) % MOD;
}

int quickPow(int MOD, int x, int w)
{
	if (!w) return 1;
	int tmp = x;
	for (w--; w; w >>= 1)
	{
		mul(MOD, tmp, tmp);
		if (w & 1) mul(MOD, tmp, x);
	}
	return tmp;
}

int num = 0;

void link(int x,int L, int R)
{
	nxt[++num] = fir[x];
	fir[x] = num;
	g[num] = node(L, R);
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	REP(i, m) 
	{
		scanf("%d", a + i);
		if (i == 0) ans = max(ans, a[i] - 1LL);
		else ans = max(ans, a[i] - a[i - 1] - 1LL);
	}
	if (m == 0) ans = n;
	else ans = max(ans, 1LL * n - a[m - 1]);
	REP(i, m)
	{
		int tmp1 = 0, last = a[i];
		int tmp2 = 0;
		int L = a[0], R;
		if (i) L = a[i] - a[i - 1];
		REPP(j, i, m - 1)
		
		{
			mul(MOD1, tmp1, quickPow(MOD1, hashWeight1, a[j] - last));
			add(MOD1, tmp1, 1);
		
			mul(MOD2, tmp2, quickPow(MOD2, hashWeight2, a[j] - last));
			add(MOD2, tmp2, 1);	
			last = a[j];
			R = n - a[m - 1] + 1;
			if (j < m - 1) R = a[j + 1] - a[j];
			int hs = getHash(tmp1, tmp2);
			link(hs, L, R);
		}
	}
	REPP(i, 1, numhs)
		if (fir[i])
			ans += calc(i);
	cout << ans << endl;
	return 0;
}
