#include <bits/stdc++.h>
#define MAXN 11234

using namespace std;

long long f[MAXN];
int pre[MAXN];

struct point
{
    int lab;
    long long v;
} a[MAXN];
 
struct node
{
    int lab;
    long long f;
    node (int lab = 0, long long f = 0) : lab(lab), f(f) {};
} ;

deque< node > sta;

vector < pair <int, int> > vec;

long long cross(int x1, long long y1, int x2, long long y2)
{
    return x1 * y2 - x2 * y1;
}

int com(point A, point B)
{
    return A.v < B.v;
}

int main()
{
    freopen("iq.in", "r", stdin);
    freopen("iq.out", "w", stdout);
    for (;;)
    {
        int n;
        cin >> n;
        if (n == 0) break;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].v;
            a[i].lab = i;
        }
        sort(a + 1, a + n + 1, com);
        sta.clear();
        sta.push_back(node(0, 0));
        
        memset(pre, -1, sizeof(pre));
        for (int i = 1; i <= n; ++i)
        {
            for (; sta.size() >= 2;)
            {
                node t1 = sta.front();
                sta.pop_front();
                node t2 = sta.front();
                long long ans1 = t1.f + a[i].v * (n - t1.lab);
                long long ans2 = t2.f + a[i].v * (n - t2.lab);
                if (ans1 < ans2)
                {
                    sta.push_front(t1);
                    break;
                }
            }
            node t1 = sta.front();
            long long ans1 = t1.f + a[i].v * (n - t1.lab);
            f[i] = ans1;
            pre[i] = t1.lab;
            
            for (; sta.size() >= 2;)
            {
                node t2 = sta.back();
                sta.pop_back();
                node t1 = sta.back();
                node t3 = node(i, f[i]);
                if (cross(t2.lab - t1.lab, t2.f - t1.f, t3.lab - t2.lab, t3.f - t2.f) > 0)
                {
                    sta.push_back(t2);
                    break;
                }
            }

            node t3 = node(i, f[i]);
            sta.push_back(t3);
        }
        cout << f[n] << endl;
        vec.clear();
        for (int x = n; x > 0; x = pre[x])
        {
            vec.push_back(make_pair(pre[x] + 1, x));
        }
        cout << vec.size() << endl;
        for (; !vec.empty(); vec.pop_back())
        {
            cout << vec.back().second - vec.back().first + 1 << ' ';
            for (int i = vec.back().first; i <= vec.back().second; ++i)
                cout << a[i].lab << " \n"[i == vec.back().second];
        }
    }
    return 0;
}
