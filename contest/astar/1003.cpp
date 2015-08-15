#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#define MAXN 512

using namespace std;

int vis[MAXN][MAXN];

int gx[4] = {-1, 0, 1, 0};
int gy[4] = {0, 1, 0, -1};

vector < pair <int, int> > vec;

int l[MAXN * MAXN], r[MAXN * MAXN];

int legal(int x, int y, int n, int m)
{
    return x > 0 && x <= n && y > 0 && y <= m;
}

int check(int x, int y, int n, int m)
{
    for (int i = 0; i < 4; ++i)
    {
        int ux = x + gx[i];
        int uy = y + gy[i];
        int v = (i + 1) % 4;
        int vx = x + gx[v];
        int vy = y + gy[v];
        if (legal(ux, uy, n, m) && legal(vx, vy, n, m) && vis[ux][uy] && vis[vx][vy]) return 1;
    }
    return 0;
}

int main()
{
    //freopen("1003.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        int N, M;
        scanf("%d%d", &N, &M);
        int tot, ans = 0;
        scanf("%d", &tot);

        //N = 500;
        //M = 500;
        //tot = 500;
        vec.clear();
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= tot; ++i)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            // x = i, y = i;

            if (vis[x][y]) continue;
            vis[x][y] = 1;
            vec.push_back(make_pair(x, y));
            ans++;
        }

        for (; !vec.empty(); )
        {
            pair <int, int> tmp = vec.back();
            vec.pop_back();
            for (int p = 0; p < 4; ++p)
            {
                int nx = tmp.first + gx[p];
                int ny = tmp.second + gy[p];
                if (legal(nx, ny, N, M) && !vis[nx][ny] && check(nx, ny, N, M))
                {
                    vis[nx][ny] = 1;
                    ans++;
                    vec.push_back(make_pair(nx, ny));
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
