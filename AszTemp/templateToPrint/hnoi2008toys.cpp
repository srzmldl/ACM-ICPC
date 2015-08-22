#include <bits/stdc++.h>
#define MAXN 51234

using namespace std;
typedef long long arrayN[MAXN];

deque < pair< pair<int, int> , int> > deq;
arrayN f, sum, c;
long long L;

long long sqr(long long x)
{
    return x * x;
}

long long trans(int l, int r)
{
    return sqr(1LL * r - (l + 1) - L + sum[r] - sum[l]) + f[l];
}
int myLowBound(pair <int, int> pr, int ori, int now) 
{
    int l = pr.first, r = pr.second;
    for (; l < r; )
    {
        int mid = l + r >> 1;
        if (trans(ori, mid) <= trans(now, mid)) l = mid + 1;
        else r = mid;
    }
    return l;
}

int main()
{
    int n;
    freopen("toys.in", "r", stdin);
    cin >> n >> L;
    for (int i = 1; i <= n; ++i)
    {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }
    deq.push_back(make_pair(make_pair(1, n), 0));
    for (int i = 1; i <= n; ++i)
    {
        for (; deq.front().first.second < i; deq.pop_front());
        f[i] = trans(deq.front().second, i);
        if (i == n) break;
        deq.front().first.first = i + 1;
        if (deq.front().first.second < i + 1) deq.pop_front();
        for (;!deq.empty() && trans(deq.back().second, deq.back().first.first) >= trans(i, deq.back().first.first); deq.pop_back());
        if (deq.empty()) deq.push_back(make_pair(make_pair(i + 1, n), i));

        else
        {
            int x = myLowBound(deq.back().first, deq.back().second, i);
            if (trans(i, x) >= (trans(deq.back().second, x))) x++;
            deq.back().first.second = x - 1;
            if (x <= n) deq.push_back(make_pair(make_pair(x, n), i));
        }
    }
    cout << f[n] << endl;
    return 0;
}
