#include <cstdio>
#include <cstring>
using namespace std;
int n, m;
bool g[1024][1024], used[1024];
int lable[1024], set[1024];  //lable存储图新的编号，set存弦图计算的编号

void Relable() {
    memset(used, false, sizeof(used));
    used[1] = true;
    for (int num=n-1; num>0; num--) {
        memset(lable, 0, sizeof(lable));
        for (int i=1; i<=n; i++) {
            if (!used[i]) {
                for (int j=1; j<=n-num; j++) {
                    if (g[i][set[n-j+1]])
                        lable[i]++;
                }
            }
        }
        int maxv = 0, max;
        for (int i=1; i<=n; i++) {
            if (lable[i] > maxv) {
                maxv = lable[i];
                max = i;
            }
        }
        set[num] = max;
        used[max] = true;
    }

}
bool check() {
    int temp[1024];
    for (int i=1; i<=n; i++) {
        memset(temp, 0, sizeof(temp));
        int t = 0;
        for (int j=i+1; j<=n; j++) {
            if (g[set[i]][set[j]]) {
                t++;
                temp[t] = set[j];
            }
        }
        for (int j=2; j<=t; j++) {
            if (!g[temp[j]][temp[1]])
                return false;
        }
    }
    return true;
}
int main() {
    freopen("in.txt", "r", stdin);
    freopen("std.out", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        if (n == 0 && m == 0) break;
        memset(g, false, sizeof(g));

        int a, b;
        for (int i=0; i<m; i++) {
            scanf("%d%d", &a, &b);
            g[a][b] = g[b][a] = true;
        }
        set[n] = 1;
        Relable();
        if (check()) printf("Perfect\n");
        else printf("Imperfect\n");
        printf("\n");
    }
    return 0;
}
