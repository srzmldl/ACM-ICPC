#include <bits/stdc++.h>
#define MAXN 2123

using namespace std;

char a[MAXN][MAXN];
int dp[MAXN][MAXN], flag[MAXN][MAXN], le[MAXN], up[MAXN];


int solve(int h, int w)
{
    memset(le, 0x3f, sizeof(le));
    memset(up, 0x3f, sizeof(up));
    int ans = 0;
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
        {
            flag[i][j] = 0;
            if (a[i][j] == '#')
            {
                le[i] = min(le[i], j);
                up[j] = min(up[j], i);
            }
            if (i - 1 >= 0 && j - 1 >= 0)
                flag[i][j] |= (a[i - 1][j - 1] == '#');
            if (i - 1 >= 0)
                flag[i][j] |= flag[i- 1][j];
            if (j - 1 >= 0)
                flag[i][j] |= flag[i][j - 1];
        }
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j)
            if (a[i][j] == '#')
            {
                if (!flag[i][j]) dp[i][j] = 0;
                else if (a[up[j]][le[i]] == '#')
                    dp[i][j] = dp[up[j]][le[i]] + 1;
                else dp[i][j] = 1;
                ans = max(ans, dp[i][j]);
            }
    return ans;
}

int main()
{
	freopen("jinxiety.in", "r", stdin);
    freopen("jinxiety.out", "w", stdout);

    for (;;)
    {
        int h, w;
        scanf("%d%d", &h, &w);
        if (h + w == 0) break;
        for (int i = 0; i < h; ++i)
            scanf("%s", a[i]);
        int ans = solve(h, w);
        for (int i = 0; i < h; ++i)
            reverse(a[i], a[i] + w);
        ans = max(ans, solve(h, w));
        printf("%d\n", ans);
    }
    return 0;
}
