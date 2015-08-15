#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 1e5 + 5;
int tmp[N];

int main() {
	ios :: sync_with_stdio(0);
    freopen("els.in", "w", stdout);
	srand(time(0) % clock());
    int T = 1;
    cout << T << endl;
	int n = 100, m = 3;
	cout << n << endl;
	REPP(i, 1, n)
    {
        int x = 2;
        cout << x << endl;
        int t1 = rand() % 11;
        int t2 = 10 - t1;
        cout << t1 / 10.0 << ' ' << t2 / 10.0 << endl;
        for (int j = 1; j <= x; ++j)
        {
            int lim = 1000;
            for (int k = 1; k < n; ++k)
            {
                int tt = rand() % (lim + 1);
                lim -= tt;
                cout  << tt / 1000.0 << ' ';
            }
            cout << lim / 1000.0 << endl;
        }
    }
	return 0;
}
