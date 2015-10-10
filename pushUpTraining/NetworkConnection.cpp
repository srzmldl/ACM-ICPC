#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define MAXM 112345
#define MAXN 2123

using namespace std;

vector <int> vec;

int f[MAXM], h[MAXM];

struct node
{
    int l, r;
} g[MAXN];
int main()
{
    // freopen("in.txt", "r", stdin);
    int m, n;
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; ++i)
    {
        int x;
        scanf("%d", &x);
        vec.push_back(x);
    }
    sort(vec.begin(), vec.end());
    vector <int> a;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        a.push_back(x);
    }
    sort(a.begin(), a.end());
    memset(f, 0, sizeof(f));
    const int INF = n * 1000010;
    for (int i = 0; i < n; ++i)
    {
        int pos = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
        g[i].l = max(0, pos - n);
        g[i].r = min(m, pos + n);
        for (int j = g[i].l; j <= g[i].r; ++j)
        {
            h[j] = abs(vec[j] - a[i]);
            if (i)
            {
                int x = min(j - 1, g[i - 1].r);
                if (x < g[i - 1].l) h[j] = INF;
                else h[j] += f[x];
            }
            if (j > g[i].l) h[j] = min(h[j], h[j - 1]);
        }
        for (int j = g[i].l; j <= g[i].r; ++j) f[j] = h[j];
    }
    printf("%d\n", f[g[n - 1].r]);
    return 0;
}
