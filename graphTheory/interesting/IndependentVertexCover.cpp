#include <bits/stdc++.h>
#define MAXN 212345

using namespace std;

const int INF = 1e9 + 10, MO = 1e9 + 7;

typedef int arrayN[MAXN];

arrayN a, minP;

int main() {
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    int ok = 1;
    int one = INF, two = INF;
    minP[n + 1] = n + 1;
    a[n + 1] = INF;
    for (int i = n; i >= 1 && ok; --i) {
        if (a[i] >= two) ok = 0;
        else if (a[i] >= one) two = min(two, a[i]);
        else one = a[i];
        if (a[i] < a[minP[i + 1]]) minP[i] = i;
        else minP[i] = minP[i + 1];
    }

    if (!ok) {
        cout << 0 << endl;
        return 0;
    }

    int tot = 0;
    for (int p = 1; p <= n;) {
        int q = minP[p + 1];
        if (a[q] > a[p]) {
            ++tot;
            ++p;
        } else {
            int mxp = p;
            for (int i = p + 1; i <= q; ++i)
                if (a[i] > a[mxp]) mxp = i;
            a[q] = a[mxp];
            p = q;
        }
    }
    long long ans = 1;
    for (int i = 1; i <= tot; ++i)
        ans = ans * 2 % MO;
    cout << ans << endl;
    return 0;
}