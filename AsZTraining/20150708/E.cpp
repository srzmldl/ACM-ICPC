#include <bits/stdc++.h>
#define MAXN 1123456
#define ll long long
#define T3 tuple<ll, ll, ll>

using namespace std;

void sort(ll a, ll b, ll c)
{
    if (a < b) swap(a, b);
    if (a < c) swap(a, c);
    if (b < c) swap(b, c);
}

int main()
{
    freopen("eating.in", "r", stdin);
    freopen("eating.out", "w", stdout);
    for (;;)
    {
		long long a, b, c;
        cin >> a >> b >> c;
        if (a + b + c == 0) break;
        sort(a, b, c);
    }
    return 0;
}
