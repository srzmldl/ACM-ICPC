#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#define MAXN 1123

using namespace std;


int com(node u, node v)
{
    return u.x < v.x;
}

int main()
{
    freopen("1003.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        int N, M;
        scanf("%d%d", &N, &M);
        int tot, ans = 0;
        scanf("%d", &tot);
        for (int i = 1; i <= tot; ++i)
            scanf("%d%d", &g[i].x, &g[i].y);
        printf("%d\n", ans);
    }
    return 0;
}
