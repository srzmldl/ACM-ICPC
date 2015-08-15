#include <bits/stdc++.h>
#define MAXN 3123

using namespace std;

int ad, ab, w[12][12], visGe[12], visGo[12];
int visdp[MAXN][MAXN];
double dp[MAXN][MAXN];

int check(int kind, int cnt)
{
    if (kind == 1) return cnt & 1;
    return cnt >= ad;
}
double dfs(int cnt, int ge, int go, int kind)
{
    if (visdp[ge][go] == 1) return dp[ge][go];
    visdp[ge][go] = 1;
    dp[ge][go] = 0;
    if (cnt == 2 * ad)
    {
        if (ge > go) return dp[ge][go] = 1.0;
        else return dp[ge][go] = 0;
    }
    if (check(kind, cnt)) //Go
    {
        for (int i = 1; i <= ab; ++i)
        {
            double smin = 1.0 + 1;
            for (int j = 0; j < ad; ++j)
                if (!visGo[j])
                {
                    visGo[j] = 1;
                    smin = min(smin, dfs(cnt + 1, ge, go + i * w[ab][j], kind));
                    visGo[j] = 0;
                }
            dp[ge][go] += smin;
        }
    }else
    {
        for (int i = 1; i <= ab; ++i)
        {
            double smax = -1;
            for (int j = 0; j < ad; ++j)
                if (!visGe[j])
                {
                    visGe[j] = 1;
                    smax = max(smax, dfs(cnt + 1, ge + i * w[ab][j], go, kind));
                    visGe[j] = 0;
                }
            dp[ge][go] += smax;
        }
    }
    return dp[ge][go] /= ab;
}

void solve(int d, int b)
{
    ad = d, ab = b;
    memset(visdp, 0, sizeof(visdp));
    printf("%.7lf ", dfs(0, 0, 0, 1)); //even ge, odd go
    memset(visdp, 0, sizeof(visdp));
    printf("%.7lf\n", dfs(0, 0, 0, 2));
}
int main()
{
    freopen("greater.in", "r", stdin);
    freopen("greater.out", "w", stdout);
    for (int i = 2; i <= 10; ++i)
    {
        w[i][0] = 1;
        for (int j = 1; j <= 9; ++j)
            w[i][j] = w[i][j - 1] * (i + 1);
    }
    for (;;)
    {
        int d, b;
        scanf("%d%d", &d, &b);
        if (d + b == 0) break;
        solve(d, b);
    }
    return 0;
}
