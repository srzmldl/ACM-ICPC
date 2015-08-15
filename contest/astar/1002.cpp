#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 1123

using namespace std;

int cnt, a[MAXN][MAXN];

int gx[2] = {1, 0};
int gy[2] = {0, 1};

struct node
{
    int u, v, w;
}g[MAXN * MAXN * 4];

int N, M, f[MAXN * MAXN * 4];

int getfa(int x)
{
    return (x == f[x]) ? f[x] : (f[x] = getfa(f[x]));
}
int check(int x, int y)
{
    return x < N && y < M;
}

int abs(int x)
{
    return x < 0 ? -x : x;
}

int com(node u, node v)
{
    return u.w < v.w;
}

int get(int x, int y)
{
    return x * M + y + 1;
}

int main()
{
    // freopen("1002.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                scanf("%d", &a[i][j]);
        int tot = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                for (int p = 0; p < 2; ++p)
                {
                    int nx = i + gx[p];
                    int ny = j + gy[p];
                    if (check(nx, ny))
                    {
                        g[++tot].u = get(i, j);
                        g[tot].v = get(nx, ny);
                        g[tot].w = abs(a[i][j] - a[nx][ny]);
                    }
                }
        sort(g + 1, g + tot + 1, com);
        int lim = N * M;
        for (int i = 1; i <= lim; ++i)
            f[i] = i;
        int ans = 0;
        for (int i = 1; i <= tot; ++i)
        {
            int fu = getfa(g[i].u);
            int fv = getfa(g[i].v);
            if (fu != fv)
            {
                ans += g[i].w;
                f[fu] = fv;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
