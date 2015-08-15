#include <bits/stdc++.h>

using namespace std;

int main()
{
    srand(time(0) % clock());
    int n = 5, l = 5;
    printf("%d %d\n", n, l);
    int lim = 10;
    for (int i = 1; i <= n; ++i) printf("%d ", rand() % lim + 1);
    return 0;
}
