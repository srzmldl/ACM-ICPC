#include <bits/stdc++.h>
#define MAXN 112345
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];


int a[MAXN], b[MAXN], c[MAXN];

int work2(int n, int &newN, int[] arr)
{
    for (int i = 1; i <= n; ++i) b[i] = arr[i];
    int ans = moveAll(n, newN, 1);
    ans = min(ans, calc(1, n, nl, nr, 2));
}

int work3(int n, int newN, int col)
{
    for (int i = 1; i <= n; ++i) c[i] = a[i];
    int tmp = moveAll(cn, newN, col, c);
    tmp += work2(n, newN, c);
}

int main()
{
    freopen("C.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
        int ans = 0;
        int newN;
        if (k == 1) ans = 0;
        else if (k == 2) ans = work2(n, newN);
        else
        {
            ans = min(work3(n, nr, 1), work3(n, nr, 2));
            ans = min(work3(n, nr, 3), ans);
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}
