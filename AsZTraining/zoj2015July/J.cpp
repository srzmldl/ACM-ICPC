#include <bits/stdc++.h>
#define MAXN 50000

using namespace std;

int n, a[30][30], d[MAXN];

int gx[4] = {1, 0, -1, 0};
int gy[4] = {0, -1, 0, 1};

int calc(int x, int y, int dir, int ifCoin, int ifCave)
{
    //ifCave == 0, in cave
    //ifCoin ==0, no coin
    //dir 0:right, 1:down, 2:left
    return ((((x * n + y) * 4 + dir) * 2 + ifCoin) * 2) + ifCave;
}

void rec(int sta, int &x, int &y, int &dir, int &ifCoin, int &ifCave)
{
    ifCave = sta % 2;
    sta /= 2;
    ifCoin = sta % 2;
    sta /= 2;
    dir = sta % 4;
    sta /= 4;
    y = sta % n;
    x = sta / n;
}

int legal(int x, int y)
{
    if (x < 0 || y < 0 || x >= n || y >= n) return 0;
    if (a[x][y] == 1 || a[x][y] == 2) return 0;
    return 1;
}

int main()
{
    freopen("J.in", "r", stdin);
    freopen("J.out", "w", stdout);
    int ca;
    for (scanf("%d", &ca); ca; --ca)
    {
        scanf("%d", &n);
        memset(a, 0, sizeof(a));
        int k, x, y;
        memset(d, 0x3f, sizeof(d));
        for (; scanf("%d%d%d", &k, &x, &y);)
        {
            if (k == -1 && x == -1 && y == -1) break;
            a[x][y] = k;
        }
        d[0] = 0;
        deque <int> deq;
        int ans = -1;
        deq.push_back(0);
        for (; !deq.empty();)
        {
            int x, y, dir, ifCoin, ifCave;
            rec(deq.front(), x, y, dir, ifCoin, ifCave);
            if (x == 0 && y == 0 && ifCoin == 1 && ifCave == 1)
            {
                ans = 1000 - 10 * d[deq.front()];
                break;
            }
            int u = deq.front(), v;
            deq.pop_front();
            if (ifCave == 1) continue;
            //go forward
            int nx = x + gx[dir];
            int ny = y + gy[dir];
            if (legal(nx, ny))
            {
                v = calc(nx, ny, dir, ifCoin, ifCave);
                if (d[v] > d[u] + 1)
                {
                    d[v] = d[u] + 1;
                    deq.push_back(v);
                }
            }
            
            //turn left
            
            int ndir = (dir - 1 + 4) % 4;
            v = calc(x, y, ndir, ifCoin, ifCave);
            if (d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                deq.push_back(v);
            }
            
            
            //turn right
            
            ndir = (dir + 1) % 4;
            v = calc(x, y, ndir, ifCoin, ifCave);
            if (d[v] > d[u] + 1)
            {
                d[v] = d[u] + 1;
                deq.push_back(v);
            }
            //grab gold

            if (a[x][y] == 3 && ifCoin == 0)
            {
                
                v = calc(x, y, dir, 1, ifCave);
                if (d[v] > d[u] + 1)
                {
                    d[v] = d[u] + 1;
                    deq.push_back(v);
                }
            }
            
            //climb out
            if (x == 0 && y == 0 && ifCoin == 1)
            {
                
                v = calc(x, y, dir, ifCoin, 1);
                if (d[v] > d[u] + 1)
                {
                    d[v] = d[u] + 1;
                    deq.push_back(v);
                }
            }
        }
        if (ans < 0) ans = -1;
        cout << ans << endl;
    }
    return 0;
}
