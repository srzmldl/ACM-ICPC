#include <bits/stdc++.h>
#define MAXN 1123

using namespace std;

int n;
char st[MAXN];

int main()
{
    freopen("ovation.in", "r", stdin);
    freopen("ovation.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d%s", &n, st);
        int ans = 0;
        int sum = 0;
        for (int i = 0; i <= n; ++i)
        {
            int x = st[i] - '0';
            if (sum < i) ans = max(ans, i - sum);
            sum += x;
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}

