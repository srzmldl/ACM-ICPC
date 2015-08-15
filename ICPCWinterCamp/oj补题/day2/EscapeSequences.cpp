#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) n; ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset(a, b, sizeof(a))

#define MAXN 212345

using namespace std;

char s[MAXN], t[MAXN];
int arrS[MAXN], arrT[MAXN], fail[MAXN];
int numS, numT, lenS, lenT, headS, headT, tailS, tailT;

int findMax(int add, int lim, int base, int goal)
{
	REP(i, lim)
		if ((base << i) + add >= goal)
			return i;
	return lim;
}

void getBpos(char *ch, int* g, int &num, int &head, int &tail)
{
	int len = strlen(ch);
	head = len;
	REP(i, len)
		if (ch[i] == 'b')
		{
			head = i;
			break;
		}
	tail = len;
	for (int i = len - 1; i >= 0; --i)
		if (ch[i] == 'b')
		{
			tail = len - i - 1;
			break;
		}
	num = 0;
	int last = head;
	REPP(i, head + 1, len - 1 - tail)
		if (ch[i] == 'b')
		{
			g[num++] = i - last;
			last = i;
		}
}


int zeroB()
{
	if (headT == lenT)
	{
		int tmpAns = 100;
		if (tailS)
			tmpAns = min(tmpAns, findMax(0, 20, tailS, lenT));
		if (headS < lenS)
		{
			int maxB = headS + 1;
			REP(i, numS) maxB = max(maxB, arrS[i]);
			tmpAns = min(tmpAns, findMax(-1, 20, maxB, lenT));
		}
		printf("%d\n", tmpAns);
		return 1;
	}
	return 0;
}

int tMoreB()
{
	int bNumS = numS + 1;
	int bNumT = numT + 1;
	if (headS == lenS) bNumS = 0;
	if (headT == lenT) bNumT = 0;
	if (headS + tailS + 1 == lenS) bNumS = 1;
	if (headT + tailT + 1 == lenT) bNumT = 1;
	if (bNumS < bNumT)
	{
		printf("-1\n");
		return 1;
	}
	return 0;
}


int oneB()
{
	if (headT + tailT + 1 == lenT)
	{
		if (headS + tailS + 1 == lenS && tailS == 0 && tailT != 0)
		{
			printf("-1\n");
			return 1;
		}
		int tmpAns = 100;
		REP(i, numS)
		{
			int L = headS + 1;
			if (i) L = arrS[i - 1];
			int R = arrS[i];
			tmpAns = min(tmpAns, max(findMax(-1, 20, L, headT), findMax(-1, 20, R, tailT)));
		}
		int L, R = tailS;
		if (headS + tailS + 1 == lenS)
			L = headS + 1;
		else L = arrS[numS - 1];
		tmpAns = min(tmpAns, max(findMax(-1, 20, L, headT), findMax(0, 20, R, tailT)));
		printf("%d\n", tmpAns);
		return 1;
	}
	return 0;
}

void getNext(int* g, int n, int* f)
{
	f[0] = 0;
	f[1] = 0;
	int j = 0;
	REPP(i, 2, n)
	{
		for(; j && g[i - 1] != g[j]; ) j = f[j];
		if (g[i - 1] != g[j]) f[i] = 0;
		else f[i] = ++j;
	}
}

int checkKmp()
{
	int j = 0;
	REP(i, numS)
	{
		for (; j && arrS[i] != arrT[j]; ) j = fail[j];
		if (arrS[i] == arrT[j]) ++j;
		if (j >= numT)
		{
			int L, R;
			if (i == numS - 1) R = tailS;
			else R = arrS[i + 1] - 1;
			if (i == numT - 1) L = headS;
			else L = arrS[i - numT] - 1;
			if (L >= headT && R >= tailT) return 1;
		}
	}
	return 0;
}

int solve()
{
	arrS[numS] = -2;
	arrT[numT] = -1;
	getNext(arrT, numT, fail);
	if (checkKmp()) return 0;
	REPP(k, 1, 20)
	{
		headS = (headS + 1) * 2 -1;
		tailS = 2 * tailS;
		REP(i, numS) arrS[i] <<= 1;
		if (checkKmp()) return k;
	}
	return -1;
}

int main()
{
	freopen("EscapeSequences.txt", "r", stdin);
	scanf("%s", s);
	lenS = strlen(s);
	scanf("%s", t);
	lenT = strlen(t);
	getBpos(s, arrS, numS, headS, tailS);
	getBpos(t, arrT, numT, headT, tailT);
	if (tMoreB()) return 0;
	if (zeroB()) return 0;
	if (oneB()) return 0;
	printf("%d\n", solve());
	return 0;
}
