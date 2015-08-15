#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))
#define MAXN 212345
#define MAXM 75

using namespace std;
typedef int arrayM[MAXM];

int n, m;

arrayM lab, vis;
long long a[MAXN][3], pw[MAXM], ans[2];

char st[MAXN][MAXM];

void yasuo(int l, int r, int k)
{
	REPP(i, 1, n)
	{
		for (int j = r; j >= l; --j)
			if (vis[j] && (st[i][lab[j] - 1] - '0'))
				a[i][k] = a[i][k] * 2 + 1;
			else a[i][k] = a[i][k] * 2;
	}
}

int last = 0;

void xiaoyuan(int l, int r, int k)
{
	for (int i = r; i >= l; --i)
		if (vis[i])
		{
			int haveOne = 0;
			if (last == n) break;
			if (a[last + 1][k] & (1LL << (i - l)))
				haveOne = 1;
			REPP(j, last + 2, n)
				if (a[j][k] & (1LL << (i - l)))
				{
					if (haveOne)
					{
						a[j][0] ^= a[last + 1][0];
						a[j][1] ^= a[last + 1][1];
					} else 
					{
						a[last + 1][0] ^= a[j][0];
						a[last + 1][1] ^= a[j][1];
						a[j][0] ^= a[last + 1][0];
						a[j][1] ^= a[last + 1][1];
						haveOne = 1;
					}
				}
			if (haveOne) ++last;
		}
	
}

int pt = 1;

int gethbt(long long x)
{
	int hbt = -1;
	for (int i = 36; i >= 0; --i)
		if (x & (1LL << i)) 
			return i;
	return hbt;
}


void gass(int ln, int rn, int l, int r, int k)
{	
	int oldLast = last;
	last = pt - 1;
	for (int i = r; i >= l; --i)
		if (vis[i])
		{
			int haveOne = 0;
			if (last == oldLast) break;
			if (a[last + 1][k] & (1LL << (i - l)))
				haveOne = 1;
			REPP(j, last + 2, n)
				if (a[j][k] & (1LL << (i - l)))
				{
					if (haveOne)
					{
						a[j][0] ^= a[last + 1][0];
						a[j][1] ^= a[last + 1][1];
					} else 
					{
						a[last + 1][0] ^= a[j][0];
						a[last + 1][1] ^= a[j][1];
						a[j][0] ^= a[last + 1][0];
						a[j][1] ^= a[last + 1][1];
						haveOne = 1;
					}
				}
			if (haveOne) ++last;
		}	
}

void work(int l, int r, int k)
{
	for (int i = r; i >= l; --i)
	{
		int u = 2 * i, v = 2 * i - 1;
		long long t1 = (a[pt][k] & (1LL << (u - (2 * l) + 1)));
		int oneu = 0, onev = 0;
		if (t1) oneu = 1;
		long long t2 = (a[pt][k] & (1LL << (v - (2 * l) + 1)));
		if (t2) onev = 1;
		if (pt > last) return;
		if (oneu + onev == 0) continue;
		
		if (oneu && onev) //xiaoyuan
		{
			//xiaoyuan;
			
			a[pt][k] = a[pt][k] -t1 - t2;
			a[pt][!k] = a[pt][!k];
			gass(pt, last, l * 2 - 1, r * 2, k);
			
			/*	int hbt1 = gethbt(a[pt][k]);
			int hbt2 = gethbt(a[pt + 1][k]);

			if (hbt1 > hbt2)
			{
				
				
			} else 
			{
				++last;
				a[last][k] = a[pt][k];
				a[last][!k] = a[pt][!k]; 
				REPP(h, pt + 1, last - 1)
				{
					int hbt = 0;
					for (int high = 36; high>= 0; --high)
						if ((1LL << high) & a[h][k])
						{
							hbt = high; 
							break;
						}
					if ((1LL << hbt) & a[last][k])
					{
						a[last][0] ^= a[h][0];
						a[last][1] ^= a[h][1];
					}
					
				}
				++pt;
				}*/
			
		} 

		else if (oneu && (!onev))
		{
			ans[0] ^= a[pt][0];
			ans[1] ^= a[pt][1];

			if (pt < last && (a[pt + 1][k] & (1LL << (v - 2 * l + 1))))
				pt += 2;
			else pt++;
			
		} else
		{
			pt++;
		}
		
		
	}
}


long long calcLastAns(int l, int r, int k)
{
	long long tmp = 0;
	REPP(i, l, r)
	{
		int u = 2 * i, v = 2 * i - 1;
		if (ans[k] & (1LL << (u - 2 * l + 1))) 
			tmp += pw[i];
		if (ans[k] & (1LL << (v - 2 * l + 1))) 
			tmp -= pw[i];
	}
	return tmp;
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("H.in", "r", stdin);

	scanf("%d%d\n", &n, &m);
	REPP(i, 1, n)
	{
		scanf("%s", st[i]);
	}
	
	pw[0] = 1;
	REPP(i, 1, 35)
		pw[i] = pw[i - 1] * 3LL;
	
	REPP(i, 1, m)
	{
		int u, v, tmp;
		scanf("%d%d", &u, &v);
		if (u == 1) tmp = v * 2;
		else tmp = v * 2 - 1;
		lab[tmp] = i;
		vis[tmp] = 1;
	}

	yasuo(1, 34, 0);
	yasuo(35, 70, 1);

	

	
	xiaoyuan(35, 70, 1);
	xiaoyuan(1, 34, 0);


	//REPP(i, 1, n)
 	//	REPP(k, 0, 1)
	//	cout << a[i][k] << endl;
	
	long long lastAns = 0;
	if (last != 0)
	{
		work(18, 35, 1);
		work(1, 17, 0);

		lastAns += calcLastAns(1, 17, 0);
		lastAns += calcLastAns(18, 35, 1);
	}
	cout << lastAns << endl;
	
	return 0;
}
