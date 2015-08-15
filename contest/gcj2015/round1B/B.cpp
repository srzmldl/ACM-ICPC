#include <bits/stdc++.h>

using namespace std;

int a[20][20];
int gx[4] = {0, 0, 1, -1};
int gy[4] = {1, -1, 0, 0};

int illegal(int x, int y, int R, int C)
{
    if (x < 0 || x >= R) return 1;
    if (y < 0 || y >= C) return 1;
    return 0;
}

void recover(int num, int &x, int &y, int R, int C)
{
    y = num % C;
    x = num / C;
}

int main()
{
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int R, C, N;
        scanf("%d%d%d", &R, &C, &N);
        int ans = R * C * 5;
        for (int i = 0; i < (1 << R * C); ++i)
        {
            int n = 0;
            for (int j = 0; j < R * C; ++j)
            {
                int x, y;
                recover(j, x, y, R, C);
                if (i & (1 << j)) a[x][y] = 1;
                else a[x][y] = 0;
                n += a[x][y];
            }
            if (n != N) continue;
            int tmp = 0;
            for (int x = 0; x < R; ++x)
                for (int y = 0; y < C; ++y)
                    if (a[x][y])
                        for (int p = 0; p < 4; ++p)
                        {
                            int nx = x + gx[p];
                            int ny = y + gy[p];
                            if (illegal(nx, ny, R, C)) continue;
                            if (a[nx][ny]) tmp++;
                    }
            ans = min(ans, tmp / 2);
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
