#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;
#define MAXN 400000

int sg[MAXN], vis[MAXN], ok[MAXN];
int pow3[10], isLast[MAXN];

int g[8][3] =
{
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 4, 8}, 
	{2, 4, 6},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8}
};

int checkSta(int sta)
{
	int a[9];
	REP(i, 9) 
	{
		a[i] = sta % 3;
		sta /= 3;
	}
	REP(p, 8)
	{
		int oneLine = 1;
		int flag = a[g[p][0]];
		REPP(i, 1, 2)
			if (a[g[p][i]] != flag)
				oneLine = 0;
		if (oneLine)
		{
			if (flag == 1) return 1;
			else if (flag == 2) return -1;
		}
	}
	return 0;
}

void maxMin(int sta, int player)
{
	if (vis[sta]) return;
	vis[sta] = 1;
	int winNow = checkSta(sta);
	if (winNow != 0)
	{
		sg[sta] = winNow;
		isLast[sta] = 1;
		return ;
	}
	sg[sta] = 0;
	int tot = 0;
	int a[9], tmp = sta;
	REP(i, 9)
	{
		a[i] = tmp % 3;
		tmp /= 3;
		if (a[i]) ++tot;
	}
	if (tot == 9)
	{
		isLast[sta] = 1;
		return ;
	}
	int tmpSta;
	if (player == 1) // findMax
	{
		sg[sta] = -2;
		REP(i, 9)
			if (a[i] == 0)
			{
				tmpSta = sta + pow3[i];
				maxMin(tmpSta, 3 - player);
				sg[sta] = max(sg[sta], sg[tmpSta]);
			}
	} else //findMin
	{
		sg[sta] = 2;
		REP(i, 9)
			if (a[i] == 0)
			{
				tmpSta = sta + 2 * pow3[i];
				maxMin(tmpSta, 3 - player);
				sg[sta] = min(sg[sta], sg[tmpSta]);
			}
	}	
}

void dfsOk(int sta, int player)
{
	ok[sta] = 1;
	if (isLast[sta]) return ;
	int a[9], tmp = sta;
	REP(i, 9)
	{
		a[i] = tmp % 3;
		tmp /= 3;
	}
	int tmpSta;
	REP(i, 9)
		if (a[i] == 0)
		{
			tmpSta = sta + player * pow3[i];
			if (sg[tmpSta] == sg[sta])
				dfsOk(tmpSta, 3 - player);
		}
}

int main() {
	ios :: sync_with_stdio(0);
	freopen("K.in", "r", stdin);
//	freopen("K.out", "w", stdout);
	pow3[0] = 1;
	REPP(i, 1, 9)
		pow3[i] = pow3[i - 1] * 3;
	MST(vis, 0);
	MST(isLast, 0);
	MST(ok, 0);
	ok[0] = 1;
	maxMin(0, 1);
	dfsOk(0, 1);
	int task;
	scanf("%d", &task);
//	REPP(i, 0, 8)
//		printf("%d\n", sg[pow3[i]]);
	REPP(t, 1, task)
	{
		char st[5];
		int wq = 0, sta = 0, a[9];
		int oneNum = 0, twoNum = 0;
		REPP(i, 0, 2)
		{
			scanf("%s", st);
			REPP(j, 0, 2)
			{
				a[wq] = 0;
				if (st[j] == 'O')
				{
					a[wq] = 1;
					oneNum++;
					sta += pow3[wq];
				}
				else if (st[j] == 'X')
				{
					a[wq] = 2;
					twoNum++;
					sta += 2 * pow3[wq];
				}
				wq++;
			}
		}
		int ha[3];
		ha[0] = 0, ha[1] = 0, ha[2] = 0;
		{
			REP(p, 8)
			{
				if ((a[g[p][0]] == a[g[p][1]]) && (a[g[p][0]] == a[g[p][2]]))
					ha[a[g[p][0]]]++;	
			}
		}
		
		if (ha[1] && ha[2])
		{
			printf("INVALID\n");
			continue;
		}
		if (ha[2] && oneNum == twoNum + 1)
		{	
			printf("INVALID\n");
			continue;
		}
		
		if (ha[1] && oneNum != twoNum + 1)
		{
			printf("INVALID\n");
			continue;
		
		}

		if ((oneNum == twoNum) || (oneNum == twoNum + 1))
		{
			if (ok[sta]) printf("REACHABLE\n");
			else printf("UNREACHABLE\n");
		} else printf("INVALID\n");
	}
	return 0;
}
