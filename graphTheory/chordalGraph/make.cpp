#include <bits/stdc++.h>

using namespace std;

int random(int x)
{
    return abs(rand() * rand() * rand()) % x + 1;
}
int main()
{
    freopen("in.txt", "w", stdout);
    srand(clock() % time(0));
    int n = 4;
    int m = 7;
    cout << n << ' ' << m << endl;
    for (int i = 2; i <= n; ++i)
        cout << i << ' ' << random(i - 1) << endl;
    for (int i = n; i <= m; ++i)
        cout << random(n) << ' ' << random(n) << endl;
    cout << 0 << ' ' << 0 << endl;
    return 0;
}
