#include <bits/stdc++.h>

int calc(int C, int W)
{
    if (W == 1) return C;
    if (C == W) return W;
    if (C % W != 0) return C / W + W;
    return C / W + W - 1;
}

int main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int R, C, W;
        scanf("%d%d%d", &R, &C, &W);
        printf("Case #%d: %d\n", t, R * calc(C, W));
    }
    return 0;
}
