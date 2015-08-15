#include <bits/stdc++.h>
#define MST(a, b) memset((a), (b), sizeof(a))
#define REP(i, n) for (int i = 0; i < (int) (n); ++i) 
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)

using namespace std;

int main()
{
	freopen("1.txt", "r", stdin);
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d", a + b);
	return 0;
}

