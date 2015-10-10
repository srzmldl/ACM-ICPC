#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAXN 112
#define EPS 1e-6
#define INF 1e20

using namespace std;

double lx[MAXN], ly[MAXN], w[MAXN][MAXN];
int match[MAXN], S[MAXN], T[MAXN];
int n;

struct node {
    int x, y;
} a[MAXN], b[MAXN];

int sqr(int x) {
    return x * x;
}

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0) return 1;
    return -1;
}

double dist(node A, node B) {
    return sqrt(1.0 * sqr(A.x - B.x) + sqr(A.y - B.y));

}

int dfs(int x) {
    S[x] = 1;
    for (int i = 1; i <= n; ++i) {
        if (cmp(lx[x] + ly[i] - w[x][i]) == 0 && !T[i]) {
            T[i] = 1;
            if (!match[i] || dfs(match[i])) {
                match[i] = x;
                return 1;
            }
        }
    }
    return 0;
}
void update() {
    double minSl = INF;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (S[i] && !T[j])
                minSl = min(minSl, lx[i] + ly[j] - w[i][j]);
    for (int i = 1; i <= n; ++i) {
        if (S[i]) lx[i] -= minSl;
        if (T[i]) ly[i] += minSl;
    }
}
void KM() {
    for (int i = 1; i <= n; ++i) {
        lx[i] = -INF;
        ly[i] = 0;
        match[i] = 0;
        for (int j = 1; j <= n; ++j)
            lx[i] = max(lx[i], w[i][j]);
    }
    for (int i = 1; i <= n; ++i) {
        for (;;) {
            memset(S, 0, sizeof(S));
            memset(T, 0, sizeof(T));
            if (dfs(i)) break;
            else update();
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &b[i].x, &b[i].y);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            w[i][j] = -1 * dist(a[i], b[j]);
    KM();
    for (int i = 1; i <= n; ++i)
        printf("%d\n", match[i]);
    return 0;
}