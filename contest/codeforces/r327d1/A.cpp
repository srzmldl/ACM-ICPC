#include <bits/stdc++.h>
#define MAXN 512345

using namespace std;

int a[MAXN];
int find(int p, int lim) {
    for (int i = p; i < lim; ++i) {
        if (a[i + 1] == a[i]) return i;
    }
}

int findEnd(int q, int lim) {
    int i = q;
    for (; i + 1 <= lim && a[i + 1] == a[q]; ++i);
    return i;
}
int main() {
    // freopen("A.in", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    a[0] = a[1];
    a[n + 1] = a[n];
    int p = 0;
    int last = -1;
    int ans = 0;
    for (;;) {
        int q = find(p, n + 1);
        if (last >= 0) {
            if (a[last] != a[q]) {
                int len = (q - 1 - last) / 2;
                for (int i = 1; i <= len; ++i) {
                    a[last + i] = a[last];
                    a[q - i] = a[q];
                }
                ans = max(ans, len);
            } else {
                int len = q - 1 - last;
                for (int i = 1; i <= len; ++i)
                    a[last + i] = a[last];
                ans = max(ans, ((len + 1) / 2));
            }
        }
        last = findEnd(q, n + 1);
        if (last >= n + 1) break;
        p = last + 1;
    }
    printf("%d\n", ans);
    for (int i = 1; i <= n; ++i)
        printf("%d%c", a[i], " \n"[i == n]);
    return 0;
}