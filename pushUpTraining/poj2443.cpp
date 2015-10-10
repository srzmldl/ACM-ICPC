#include <cstdio>
#include <cstring>
#define MAXN 1010
#define MAXNUM 11234

using namespace std;

long long vis[MAXNUM][30];


int main()
{
    //  freopen("in.txt", "r", stdin);
    int N;
    for (; scanf("%d", &N) != EOF; )
    {
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i < N; ++i)
        {
            int u = i / 60;
            long long v = i % 60;
            v = 1LL << v;
            int tot;
            scanf("%d", &tot);
            for (int j = 0; j < tot; ++j)
            {
                int x;
                scanf("%d", &x);
                vis[x][u] |= v;
            }
        }
        int m;
        scanf("%d", &m);
        for (int i = 1; i <= m; ++i)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            int ok = 0;
            int lim = N / 60 + 1;
            for (int i = 0; i <= lim && !ok; ++i)
                if (vis[l][i] & vis[r][i])
                    ok = 1;
            if (ok) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
