#include <bits/stdc++.h>
#define MAXN 112345

using namespace std;

int a[MAXN], b[MAXN];

long long calc(int d1, int n)
{
    long long tmp = 0;
    
    for (int i = 1; i <= n; ++i)
        if (b[i] == d1)
        {
            int j = i;
            for (; j + 1 <= n && b[j + 1] == d1; ++j);
            int len = j - i + 1 + 1;
            tmp += 1LL * len * (len - 1) / 2;
            i = j;
        }
    return tmp;
}

int main()
{
    //	freopen("in.txt", "r", stdin);
    int n, d1, d2;
    for (;scanf("%d%d%d", &n, &d1, &d2) != EOF;)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i < n; ++i)
            b[i] = a[i + 1] - a[i];
        long long ans = n;
        --n;
        if (d1 == d2)
        {
            ans += calc(d1, n);
        } else
        {
            for (int i = 1; i <= n; ++i)
                if (b[i] == d1)
                {
                    int j = i;
                    for (; j + 1 <= n && b[j + 1] == d1; ++j);
                    int k = j;
                    for (; k + 1 <= n && b[k + 1] == d2; ++k);
                    int l1 = j - i + 1;
                    int l2 = k - j;
                    ans += 1LL * l1 * l2;
                    i = k;
                }
            ans += calc(d2, n) + calc(d1, n);
        }
        cout << ans << endl;
    }
	return 0;
}
