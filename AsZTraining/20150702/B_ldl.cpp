#include <bits/stdc++.h>
#define MAXN 70
#define ull unsigned long long

using namespace std;

char st[MAXN];
int nxt[MAXN];

void kmp(int m)
{
    nxt[0] = 0;
    int j = -1;
    for (int i = 1; i < m; ++i)
    {
        for (;j >= 0 && st[i] != st[j + 1]; j = nxt[j]);
        if (st[i] == st[j + 1]) nxt[i] = j + 1;
        else nxt[i] = -1;
    }
}

ull calc(int m, int n)
{
    kmp(m);
    ull tmp = 1;
    tmp <<= (n - m);
    for (int i = 0; i < m; ++i)
        if (nxt[i] >= 0)
            tmp -= 1ull << (n - m - (i + 1));
    return tmp;
}

int main()
{
    freopen("borderless.in", "r", stdin);
    freopen("borderless.out", "w", stdout);
    for (;;)
    {
        int n;
        ull k;
        cin >> n >> k;
        if (n == 0 && k == 0) break;
        for (int i = 0; i < n; ++i)
        {
            st[i] = 'a';
            ull tmp = calc(i + 1, n);
            if (tmp < k)
            {
                st[i] = 'b';
                k -= tmp;
            }
            cout << st[i];
        }
        cout << endl;
    }
    return 0;
}
