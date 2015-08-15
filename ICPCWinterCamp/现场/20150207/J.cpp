#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 2e5 + 5;

int f[N], tot;
char s[N], str[N];
pair<int, int> p[N * 20];


void getfail(char *s) {
	f[0] = f[1] = 0;
	REPP(i, 1, n - 1) {
		int j = f[i];
		while (j && s[j] != s[i]) j = fail[j];
		f[j] = s[j] == s[i] ? j + 1 : 0;
	}
}

void go(char *s) {
	int now = 0;
	int len = strlen(s);
	REP(i, len) {
		while (s[i] != str[now]) now = fail[now];
		if (s[i] == str[now]) {
			now++;
			if (now == 

		}

	}
	


}

int main() {
	ios :: sync_with_stdio(0);

	scanf("%s", str);
	 tot = strlen(str);
	int n;
	cin >> n;
	flow.init(1, 2);
	REPP(i, 1, n) {
		scanf("%s", s[i]);
		getfail(s[i]);
		go(s[i]);
	}
	cout << flow.mincost() << endl;


	return 0;
}

