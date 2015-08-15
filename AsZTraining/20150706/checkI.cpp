#include <bits/stdc++.h>
#define MAXN 11234

using namespace std;

long long a[MAXN], f[MAXN];
int pre[MAXN];

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
            cin >> a[i];
        sort(a + 1, a + n + 1);
        memset(pre, -1, sizeof(pre));
        memset(f, 0x3f, sizeof(f));
        f[0] = 0;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                long long tmp = f[j] + a[i] * (n - j);
                if (tmp <= f[i])
                {
                    f[i] = tmp;
                    pre[i] = j;
                }
            }
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
            cout << vec.back().first << ' ';
            cout << vec.back().second << endl;
        }
    }
    return 0;
}
