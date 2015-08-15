#include <bits/stdc++.h>
#define MAXN 12
#define MAXSTA 70000

using namespace std;

//int dp[MAXN][MAXSTA];
//int pw[MAXN];
//int g[MAXSTA][1100];

/*void initg()
{
    int cnt[10];
    for (int i = 0; i < pw[10]; ++i)
        for (int j = 0; j <= (1 << 10); ++j)
        {
            memset(cnt, 0, sizeof(cnt));
            int ti = i;
            int tj = j;
            int tmp = 0;
            for (int k = 0; k <= 9; ++k)
            {
                cnt[k] += ti % 3;
                cnt[k] += tj % 2;
                ti /= 3;
                tj /= 2;
            }
            int last = 0;
            for (int k = 0; k <= 9; ++k)
            {
                if (last > cnt[k])
                {
                    tmp = 0;
                    break;
                }
                if (last)
                {
                    tmp += pw[k - 1] * last;
                    cnt[k] -= last;
                }
                last = cnt[k];
            }
            if (last) tmp = 0;
            g[i][j] = tmp;
        }
}

void calc()
{
    pw[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        pw[i] = pw[i - 1] * 3;
    initg();
    for (int ca = 1;; ++ca)
    {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        memset(dp, 0, sizeof(dp));
        for (int sta = 1; sta < (1 << (n + 1)); ++sta)
            if (g[0][sta])
                dp[n - 1][g[0][sta]]++;
        for (int i = n - 1; i >= 1; --i)
            for (int sta = 0; sta < pw[i + 1]; ++sta)
                for (int j = 0; j < (1 << (i + 1)); ++j)
                    if (g[sta][j] > 0)
                        dp[i - 1][g[sta][j]] += dp[i][sta];
        printf("Case #%d: %d\n", ca, dp[0][1]);
    }
    } */

int main()
{
    freopen("immetric.in", "r", stdin);
    freopen("immetric.out", "w", stdout);
    // calc();  //It's used to calc ans
    int ans[10] = {0, 1, 2, 5, 14, 43, 140, 474, 1648, 5839};
    for (int ca = 1; ; ++ca)
    {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        printf("Case #%d: %d\n", ca, ans[n]);
    }
    return 0;
}
