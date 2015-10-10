#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#define MAXN 1123

using namespace std;

struct node
{
    int mx[MAXN][MAXN];
    int rs[MAXN], cs[MAXN];
    int n, m;
    void init(int n1, int m1)
    {
        n = n1, m = m1;
        memset(rs, 0, sizeof(rs));
        memset(cs, 0, sizeof(cs));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                scanf("%d", &mx[i][j]);
                rs[i] += mx[i][j];
                cs[j] += mx[i][j];
            }
    }
} a, b, c;


int main()
{
    // freopen("in.txt", "r", stdin);
    int N, P, M;
    for (; scanf("%d%d%d", &N, &P, &M) != EOF; )
    {
        a.init(N, P);
        b.init(P, M);
        c.init(N, M);
        int ansr = 0;
        for (int i = 1; i <= a.n; ++i)
        {
            int tmp = 0;
            for (int j = 1; j <= a.m; ++j)
                tmp += a.mx[i][j] * b.rs[j];
            if (tmp != c.rs[i])
            {
                ansr = i;
                break;
            }
        }
        if (ansr == 0)
        {
            printf("Yes\n");
            continue;
        } else
        {
            printf("No\n");
            for (int j = 1; j <= c.m; ++j)
            {
                int tmp = 0;
                for (int k = 1; k <= b.n; ++k)
                    tmp += a.mx[ansr][k] * b.mx[k][j];
                if (tmp != c.mx[ansr][j])
                {
                    printf("%d %d\n", ansr, j);
                    printf("%d\n", tmp);
                    break;
                }
            }
        }
    }
    return 0;
}
