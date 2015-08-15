#include <bits/stdc++.h>
#define MAXN 1123

using namespace std;
int a[MAXN];

int check(int n, int lim, int cutTime)
{
    for (int i = n; i >= 1; --i)
    {
        if (a[i] <= lim) break;
        cutTime -= (a[i] - 1) / lim;
    }
    return cutTime >= 0;
}

int main()
{
    freopen("pancake.in", "r", stdin);
    freopen("pancake.out", "w", stdout);
    int T;
    scanf("%d", &T);
    int n;
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        sort(a + 1, a + n + 1);
        int ans = a[n];
        for (int cutTime = a[n]; cutTime >= 0; --cutTime)
        {
            int l = 1, r = a[n];
            for (; l < r; )
            {
                int mid = l + r >> 1;
                if (check(n, mid, cutTime)) r = mid;
                else l = mid + 1;
            }
            ans = min(ans, l + cutTime);
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
