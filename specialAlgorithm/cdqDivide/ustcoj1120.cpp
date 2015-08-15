#include <bits/stdc++.h>
#define MAXN 2123

typedef int arrayN[MAXN];

using namespace std;

arrayN a, b;

int main()
{
    freopen("1120.in", "r", stdin);
    freopen("1120.out", "w", stdout);
    for (;;)
    {
        int n, m;
        vector <int> vec;
        scanf("%d%d", &n, &m);
        if (n + m == 0) break;
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a + i);
            vec.push_back(a[i]);
        }
        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", b + i);
            vec.push_back(b[i]);
        }
        sort(vec.begin(), vec.end());
        vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
        for (int i = 1; i <= n; ++i)
            a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
        for (int i = 1; i <= m; ++i)
            b[i] = lower_bound(vec.begin(), vec.end(), b[i]) - vec.begin();
        
    }
    return 0;
}
