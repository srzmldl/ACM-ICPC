#include <cstdio>
#include <iostream>
#include <cstring>
#define INF 0x3f3f3f3f

using namespace std;

int f[110][60];
int ori[110];
int d[60][60];

int main()
{
freopen("1.in", "r", stdin);
    int ttt;
    scanf("%d", &ttt);
    while (ttt--)
    {
        memset(f, 0, sizeof(f));
        int n, m;
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &d[i][j]);
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &ori[i]);
            if (ori[i] != -1)
                ori[i]--;
        }

        if (ori[0] == -1)
            for (int i = 0; i < m; i++)
                f[0][i] = 0;
        else
            for (int i = 0; i < m; i++)
                f[0][i] = -INF;
        if (ori[0] != -1)
            f[0][ori[0]] = 0;
//        for (int i = 0; i < n; i++)
//            for (int j = 0; j < m; j++)
//                printf("%d%c", f[i][j], j == m - 1 ? '\n' : ' ');

        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++)
            {
                if (ori[i] == -1)
                {
                    for (int k = 0; k < m; k++)
                        f[i][j] = max(f[i][j], f[i - 1][k] + d[k][j]);
                } else
                {
                    if (ori[i] == j)
                        for (int k = 0; k < m; k++)
                            f[i][j] = max(f[i][j], f[i - 1][k] + d[k][j]);
                    else
                        f[i][j] = -INF;
                }
            }
        int ans = 0;
        for (int i = 0; i < m; i++)
            ans = max(f[n - 1][i], ans);
        cout << ans << endl;
    }
    return 0;
}
