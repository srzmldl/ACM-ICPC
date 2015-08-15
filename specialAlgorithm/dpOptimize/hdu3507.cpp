#include <deque>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>

#define MAXN 512345

using namespace std;
typedef long long arrayN[MAXN];

struct node
{
    long long x, y, f;
    node (long long tx = 0, long long ty = 0, long long tf = 0)
    {
        x = tx, y = ty, f = tf;
    }
    //y = f + sum^2, x = sum
}g[MAXN];

long long sqr(long long x)
{
    return x * x;
}

long long cross(long long x1, long long y1, long long x2, long long y2)
{
    return x1 * y2 - x2 * y1;
}


deque < int > deq;

int main()
{
    freopen("hdu3507.in", "r", stdin);
    int N, M;
    for (; scanf("%d%d", &N, &M) != EOF; )
    {
        deq.clear();
        g[0] = node(0, 0, 0);
        deq.push_back(0);
        for (int i = 1; i <= N; ++i)
        {
            int x;
            scanf("%d", &x);
            g[i].x = g[i - 1].x + x;
            long long lim = g[i].x << 1;
            for (; deq.size() > 1; deq.pop_front())
            {
                node u = g[deq[0]];
                node v = g[deq[1]];
                if ((v.y - u.y) > lim * (v.x - u.x))
                    break;
            }
            node pt = g[deq.front()];
            g[i].f = pt.f + sqr(g[i].x - pt.x) + M;
            g[i].y = sqr(g[i].x) + g[i].f;
            for (; deq.size() >= 2; deq.pop_back())
            {
                node A = g[deq[deq.size() - 2]];
                node B = g[deq[deq.size() - 1]];
                node C = g[i];
                if (cross(B.x - A.x, B.y - A.y, C.x - B.x, C.y - B.y) > 0) break;
            }
            deq.push_back(i);
        }
        cout << g[N].f << endl;
    }
    return 0;
}
