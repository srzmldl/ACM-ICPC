#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 51234
#define MAXM 21234567

using namespace std;

typedef int arrayN[MAXN], arrayM[MAXM];

arrayN fir;
arrayM nxt;

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d%d", &n, &m);
    num = 1;
    for (int i = 1; i <= m; ++i) {
        int k;
        scanf("%d", &k);
        int last = 0;
        for (int j = 1; j <= k; ++j) {
            int x;
            scanf("%d", &x);
            if (last) link(last, x);
            last = x;
        }
    }
    return 0;
}