#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        int ans = 0;
        int R, C;
        scanf("%d%d", &R, &C);
        if (R == 1)
        {
            if (C >= 3) ans = 1;
            else ans = 0;
        }
        else if (R == 2)
        {
            if (C >= 3) ans += 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}