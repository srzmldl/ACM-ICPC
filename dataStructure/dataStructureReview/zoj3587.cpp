#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REDD(i, a, b) for(int i = (int) (a); i >= (int) (b); --i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXLEN 112345

using namespace std;

char S[MAXLEN], T[MAXLEN];
int cnt1[MAXLEN], cnt2[MAXLEN];
int lS, lT, nxt[MAXLEN];

void reverse(char *st)
{
	int len = strlen(st);
	REPP(i, 1, len / 2)
		swap(st[i - 1], st[len - i]);
}

void getNext() //统一写法，nxt[i]表示0base的字符串在T[i]失配时跳转到的新比较位置
{
	nxt[0] = nxt[1] = 0;
	REPP(i, 1, lT - 1)
	{
		int j = nxt[i];
		while (j && T[j] != T[i]) j = nxt[j];
		nxt[i + 1] = (T[j] == T[i] ? j + 1 : 0);
		//	if (T[i + 1] == T[nxt[i + 1]]) nxt[i + 1] = nxt[nxt[i + 1]]; //数据结构复习发现的小优化，但是这个题不能加，因为要统计答案
	}
}

void kmp(int *cnt)
{
	getNext();
	int j = 0;
	REPP(i, 0, lS - 1)
	{
		while (j && T[j] != S[i]) j = nxt[j];
		if (T[j] == S[i]) cnt[++j]++;
	}
	REDD(i, lT, 2)
		if (nxt[i])
			cnt[nxt[i]] += cnt[i];
}

int main()
{
	freopen("zoj3587.in", "r", stdin);
	int task;
	for (scanf("%d", &task); task; task--)
	{
		scanf("%s", S);
		scanf("%s", T);
		lS = strlen(S);
		lT = strlen(T);
		MST(cnt1, 0);
		MST(cnt2, 0);
		kmp(cnt1);
		reverse(S);
		reverse(T);
		kmp(cnt2);
		long long ans = 0;
		REPP(i, 1, lT - 1)
			ans += 1LL * cnt1[i] * cnt2[lT - i];
		printf("%lld\n", ans);
	}
	return 0;
}
