#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAXN 111123

using namespace std;

long long A[MAXN];
int ans;

long long gcd(long long u, long long v)
{
    if (!u || !v) return u + v;
    return gcd(v, u % v);
}

int main()
{
    // freopen("1004.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        char st[20];
        scanf("%s", st);
        int len = strlen(st);
        long long ten = 1;
        long long fz = st[0] - '0';
        long long fm = 1;
        for (int i = 2; i < len; ++i)
        {
            fz = fz * 10 + st[i] - '0';
            fm *= 10;
        }
        long long tmp = gcd(fz, fm);
        fz /= tmp;
        fm /= tmp;
        ans = 0;
        for (int i = 1; i <= 99; ++i)
        {
            int j = i;
            if (i >= 10) j = (i % 10) * 10 + i / 10;
            if (fz * i == fm * j) A[++ans] = i;
        }
        ten = 10LL;
        for (int k = 1; k <= 8; ++k)
        {
            ten *= 10LL;
            for (int a = 1; a <= 9; ++a)
                for (int c = 0; c <= 9; ++c)
                {
                    long long tl = fz * 10 - fm * 10;
                    long long tr = (ten * c + a) * fm - (ten * a + c) * fz;
                    if (tl < 0) tl *= -1, tr *= -1;
                    if (tr < 0) tl *= -1, tr *= -1;
                    if (tl < 0) continue;
                    if (tr == 0)
                    {
                        A[++ans] = ten * a + c;
                        continue;
                    }
                    if (tr % tl == 0)
                    {
                        long long tmp = tr / tl;
                        if (tmp < ten / 10)
                            A[++ans] = ten * a + tmp * 10 + c;
                    }
                }
        }
        cout << ans << endl;
        sort(A + 1, A + ans + 1);
        for (int i = 1; i <= ans; ++i)
            cout << A[i] << " \n"[i == ans];
    }
    return 0;
}
