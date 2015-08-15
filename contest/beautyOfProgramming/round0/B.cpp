#include <bits/stdc++.h>
#define MO 100007
#define MAXN 30

using namespace std;

char st[1123];
int f[MAXN][MAXN];

int main()
{
    // freopen("in.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%s", st);
        int len = strlen(st);
        for (int i = 0; i < len; ++i)
            f[i][i] = 1;
        int ans = len;
        for (int k = 1; k <= len - 1; ++k)
            for (int i = 0; i + k <= len - 1; ++i)
            {
                int j = i + k;
                f[i][j] = 0;
                if (st[i] == st[j])
                {
                    f[i][j] = 1;
                    for (int i1 = i + 1; i1 < j; ++i1)
                        for (int j1 = i1; j1 < j; ++j1)
                                f[i][j] = (f[i][j] + f[i1][j1]) % MO;
                }
                ans = (ans + f[i][j]) % MO;
            }
        printf ("Case #%d: %d\n", t, ans);
    }
    return 0;
}
