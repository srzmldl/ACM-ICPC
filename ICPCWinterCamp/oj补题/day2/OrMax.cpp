#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) n; ++i)
#define REPP(i, a, b) for(int i = (int) a; i <= (int) b; ++i)
#define MAXN 112345

using namespace std;

int ans[MAXN], a[MAXN], nearOneL[MAXN][20];
int n, L[MAXN], R[MAXN];
int nearOneR[MAXN][20], lSum[20], rSum[20];
vector <int> sta;

struct node
{
	int shift, pos;
	node(int sft = 0, int ps = 0)
		{
			shift = sft;
			pos = ps;
		}
} lft[20], rgt[20];

void getMax(int &u, int v)
{
	if (v > u) u = v;
}

int com(node u, node v)
{
	return u.pos < v.pos;
}

int main()
{
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	REP(i, n) scanf("%d", &a[i]);
	REP(i, 16)
	{
		int weight = 1 << i;
		int lastOne = -1;
		REP(j, n)
		{
			if (a[j] & weight)
				lastOne = j;
			nearOneL[j][i] = lastOne;
		}
		lastOne = n;
		for (int j = n - 1; j >= 0; --j)
		{
			if (a[j] & weight)
				lastOne = j;
			nearOneR[j][i] = lastOne;
		}
	}

	sta.clear();
	REP(i, n)
	{
		for(;!(sta.empty()) && (a[sta.back()] <= a[i]);)
			sta.pop_back();
		if (sta.empty()) L[i] = -1;
		else L[i] = sta.back();
		sta.push_back(i);
	}

	sta.clear();
	for (int i = n - 1; i >= 0; --i)
	{
		for (;!sta.empty() && a[sta.back()] <= a[i];)
			sta.pop_back();
		if (sta.empty()) R[i] = n;
		else R[i] = sta.back();
		sta.push_back(i);
	}

	REP(i, n)
	{
		getMax(ans[1], 2 * a[i]);
		int lNum = 0, rNum = 0;
		REP(j, 16)
			if (nearOneL[i][j] > L[i])
				lft[lNum++] = node(j, nearOneL[i][j]);
		REP(j, 16)
			if (nearOneR[i][j] < R[i])
				rgt[rNum++] = node(j, nearOneR[i][j]);
		sort(lft, lft + lNum, com);
		sort(rgt, rgt + rNum, com);

		int tmp = a[i];
		for (int j = lNum - 1; j >= 0; --j)
		{
			tmp |= (1 << lft[j].shift);
			lSum[j] = tmp;
			getMax(ans[i - lft[j].pos + 1], lSum[j] + a[i]);
		}
		tmp = a[i];
		for (int j = 0; j < rNum; ++j)
		{
			tmp |= (1 << rgt[j].shift);
			rSum[j] = tmp;
			getMax(ans[rgt[j].pos - i + 1], rSum[j] + a[i]);
		}
		for (int j = lNum - 1; j >= 0; --j)
			for (int k = 0; k < rNum; ++k)
				getMax(ans[rgt[k].pos - lft[j].pos + 1], (rSum[k] | lSum[j]) + a[i]);
		
	}

	REPP(i, 2, n) getMax(ans[i], ans[i - 1]);
	REPP(i, 1, n) printf("%d\n", ans[i]);
	return 0;
}

