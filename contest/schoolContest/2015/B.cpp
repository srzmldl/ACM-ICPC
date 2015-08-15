#include <bits/stdc++.h>
#define MAXN 312345
#define MST(a, b) memset(a, b, sizeof(a));
#define MO 10000007

using namespace std;

int f[MAXN][2];

void calc(int n)
{
    MST(f, 0);
    f[1][0] = 1;
    f[1][1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        f[i][1] = f[i - 1][0] % MO;
        f[i][0] = (f[i - 1][0] + f[i - 1][1]) % MO;
    }
    printf("%d\n", (f[n][0] + f[n][1] - 1 + MO) % MO);
}

int getin()
{
    char ch;
    int flag = 0, tmp = 0;
    for (ch = getchar(); ch < 48 || ch > 57; ch = getchar())
        if (ch == int('-')) break;
    if (ch == int('-')) flag = 1; else tmp = int(ch) - 48;
    for (ch = getchar(); 48 <= ch && ch <= 57; ch = getchar())
        tmp = tmp * 10 + int(ch) - 48;
    return (flag) ? -tmp : tmp;
}

int main()
{
    //freopen("B.in", "r", stdin);
    int m, n;
    for (; scanf("%d%d", &m, &n);)
    {
        if (n == -1 && m == -1) break;
        int ttt = sqrt(1.0 * m) + 1;
        int tmp = 1;
        for (int i = 2; i <= ttt; ++i)
        {
            int cnt = 1;
            for (; m % i == 0; )
            {
                cnt++;
                m /= i;
            }
            tmp = tmp * (cnt % 2) % 2;
        }
        if (m != 1) tmp = 0;
        if (tmp % 2 == 0)
        {
            printf("No girl\n");
            continue;
        } else
        {
            calc(n);
        }
    }
    return 0;
}
