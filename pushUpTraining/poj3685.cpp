#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n = 5;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            printf("%8d ", i * i + 100000 * i + j * j - 100000 * j + i *j);
        printf("\n");
    }
    return 0;
}
