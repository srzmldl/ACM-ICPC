#include <bits/stdc++.h>
#define MAXN 112345
#define ESP 1e-5

using namespace std;

struct node
{
    long long f;
    int b;
    int a;
} g[MAXN];

deque <node> deq;

long long dp(node u, node v)
{
    return u.f + 1LL * u.b * v.a;
}

double cross(node A, node B, node C)
{
    return 1.0 * (B.b - A.b) * (C.f - B.f) - 1.0 * (B.f - A.f) * (C.b - B.b);
}
int main()
{
    //  freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &g[i].a);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &g[i].b);
    g[1].f = 0;
    deq.push_back(g[1]);
    for (int i = 2; i <= n; ++i)
    {
        for (; deq.size() >= 2; )
        {
            node u = deq.front();
            deq.pop_front();
            node v = deq.front();
            long long fu = dp(u, g[i]);
            long long fv = dp(v, g[i]);
            if (fu < fv)
            {
                deq.push_front(u);
                break;
            }
        }
        g[i].f = dp(deq.front(), g[i]);
        for (; deq.size() >= 2;) {
            node u = deq.back();
            deq.pop_back();
            node v = deq.back();
            if (cross(g[i], u, v) > ESP) {
                deq.push_back(u);
                break;
            }
        }
        deq.push_back(g[i]);
    }
    cout << g[n].f << endl;
    return 0;
}