//#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#define MAXN 60

using namespace std;

char st[MAXN][MAXN];
int up = MAXN + 1, dw = -1, le = MAXN + 1, ri = -1;

int R, C;

void getMax(int &x, int y)
{
    if (y > x) x = y;
}

void getMin(int &x, int y)
{
    if (y < x) x = y;
}

void work(int i, int j)
{
    getMax(dw, i);
    getMin(up, i);
    getMax(ri, j);
    getMin(le, j);
}

void modiAdd(int i, int j)
{
    if (st[i][j] != '*')
        st[i][j] = '+';
}

int checkAddOrStar(int i, int j)
{
    if (i < 0 || j < 0 || i >= R || j >= C) return 0;
    return st[i][j] == '+' || st[i][j] == '*';
}

int checkUp(int i, int j)
{
    for (int k = 0; k < i; ++k)
        if (st[k][j] != '.') return 0;
    return 1;
}

int checkDown(int i, int j)
{
    for (int k = i + 1; k < R; ++k)
        if (st[k][j] != '.') return 0;
    return 1;
}

int main()
{
    //  freopen("in.txt", "r", stdin);
    scanf("%d%d", &R, &C);
    for (int i = 0; i < R; ++i)
    {
        scanf("%s", st[i]);
        for (int j = 0; j < C; ++j)
            if (st[i][j] == 'X')
            {
                work(i - 1, j - 1);
                work(i + 1, j + 1);
            } else if (st[i][j] == '*')
            {
                work(i, j);
            }
    }
    int ans = 2 * (ri - le + dw - up);
    for (int i = le; i <= ri; ++i)
    {
        modiAdd(up, i);
        modiAdd(dw, i);
    }
    for (int i = up; i <= dw; ++i)
    {
        modiAdd(i, le);
        modiAdd(i, ri);
    }
    int flag = 1;
    for (; flag; )
    {
        flag = 0;

        //left up
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j + 1) && checkAddOrStar(i + 1, j) && checkUp(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        ans--;
                        flag = 1;
                    }

        
        for (int i = 0; i < R; ++i)
            for (int j = C - 1; j >= 0; --j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j - 1) && checkAddOrStar(i + 1, j) && checkUp(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        ans--;
                        flag = 1;
                    }

        
        for (int i = R - 1; i >= 0; --i)
            for (int j = 0; j < C; ++j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j + 1) && checkAddOrStar(i - 1, j) && checkDown(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        ans--;
                        flag = 1;
                    }

        
        for (int i = R - 1; i >= 0; --i)
            for (int j = C - 1; j >= 0; --j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j - 1) && checkAddOrStar(i - 1, j) && checkDown(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        ans--;
                        flag = 1;
                    }


        //====================
        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j + 1) && checkAddOrStar(i + 1, j - 1) && st[i + 1][j] != 'X' && checkUp(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        modiAdd(i + 1, j);
                        flag = 1;
                    }

        
        for (int i = 0; i < R; ++i)
            for (int j = C - 1; j >= 0; --j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j - 1) && checkAddOrStar(i + 1, j + 1) && st[i + 1][j] != 'X' && checkUp(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        modiAdd(i + 1, j);
                        flag = 1;
                    }

        
        for (int i = R - 1; i  >= 0; --i)
            for (int j = 0; j < C; ++j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j + 1) && checkAddOrStar(i - 1, j - 1) && st[i - 1][j] != 'X' && checkDown(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        modiAdd(i - 1, j);
                        flag = 1;
                    }

        
        for (int i = R - 1; i >= 0; --i)
            for (int j = C - 1; j >= 0; --j)
                if (st[i][j] == '+')
                    if (checkAddOrStar(i, j - 1) && checkAddOrStar(i - 1, j + 1) && st[i - 1][j] != 'X' && checkDown(i, j))
                    {
                        if (flag) break;
                        st[i][j] = '.';
                        modiAdd(i - 1, j);
                        flag = 1;
                    }
    }
    cout << ans << endl;
    return 0;
}
