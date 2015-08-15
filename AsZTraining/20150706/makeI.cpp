#include <bits/stdc++.h>

using namespace std;

int main()<
{
    srand(clock() % time(0));
    freopen("iq.in", "w", stdout);
    int n = 10, lim = 100000;
    cout << n << endl;
    for (int i = 1; i <= n; ++i)
        //cout << lim << ' ';
        cout << abs(rand() * rand() * rand()) % lim + 1 << ' ';
    cout << endl;
    cout << 0 << endl;
    return 0;
}
