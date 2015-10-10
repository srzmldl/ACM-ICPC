#include <bits/stdc++.h>

using namespace std;

void solveOddRow(int sum, int n, int m)
{
    printf("%d\n", sum);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m - 1; ++j)
            if (i & 1) printf("L");
            else printf("R");
        if (i != n - 1) printf("D");
    }
}

void solveOddCol(int sum, int n, int m)
{
    printf("%d\n", sum);
    for (int j = 0; j < m; ++j)
    {
        for (int i = 0; i < n - 1; ++i)
            if (j & 1) printf("U");
            else printf("D");
        if (j != m - 1) printf("R");
    }
}

void solveOddRemainRow(int ans, int ti, int tj, int n, int m)
{
    printf("%d\n", ans);
    int flag = 0;
    int i = 0, j = 0;
    for (;;)
    {
        if (!flag && ti - i == 1)
        {
            for (j = 0; j < tj; j += 2)
                printf("DRUR");
            for (; j < m - 1; ++j)
            {
                if (j & 1) printf("RU");
                else printf("RD");
            }
            ++i;
            if (i < n - 1)
            {
                ++i;
                printf("D");
                for (int j = 0; j < m - 1; ++j)
                    printf("L");
                printf("D");
                ++i;
            } else break;
            
            flag = 1;
        } else
        {
            for (int j = 0; j < m - 1; ++j)
                printf("R");
            if (i < n - 1)
            {
                ++i;
                printf("D");
                for (int j = 0; j < m - 1; ++j)
                    printf("L");
                printf("D");
                ++i;
            } else break;
        }
    }
}

void solveOddRemainCol(int ans, int ti, int tj, int n, int m)
{
    printf("%d\n", ans);
    int flag = 0;
    int i = 0, j = 0;
    for (;;)
    {
        if (!flag && tj - j == 1)
        {
            for (i = 0; i < ti; i += 2)
                printf("RDLD");
            for (; i < n - 1; ++i)
            {
                if (i & 1) printf("DL");
                else printf("DR");
            }
            ++j;
            if (j < m - 1)
            {
                ++j;
                printf("R");
                for (int i = 0; i < n - 1; ++i)
                    printf("U");
                printf("R");
                ++j;
            } else break;
            
            flag = 1;
        } else
        {
            for (int i = 0; i < n - 1; ++i)
                printf("D");
            if (j < m - 1)
            {
                ++j;
                printf("R");
                for (int i = 0; i < n - 1; ++i)
                    printf("U");
                printf("R");
                ++j;
            } else break;
        }
    }
}

int main()
{
    // freopen("g.in", "r", stdin);
    int n, m;
    for (; scanf("%d%d", &n, &m) != EOF;)
    {
        int sum = 0;
        int mi = 1123;
        int ti, tj;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
            {
                int x;
                scanf("%d", &x);
                sum += x;
                if (((i + j) & 1) && x < mi)
                {
                    mi = x;
                    ti = i, tj = j;
                }
            }
        if (n & 1) solveOddRow(sum, n, m);
        else if (m & 1) solveOddCol(sum, n, m);
        else if (ti & 1) solveOddRemainRow(sum - mi, ti, tj, n, m);
        else solveOddRemainCol(sum - mi, ti, tj, n, m);
        printf("\n");
    }
    return 0;
}
