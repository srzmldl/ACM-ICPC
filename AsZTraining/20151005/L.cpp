#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAXCHAR 35
#define MAXN 200000
#include <map>
#include <string>
#include <iostream>
#define LIM 4
#define MO 1234567891LL

using namespace std;

int belong[MAXN], val[MAXN], tbel[MAXN];
int son[MAXN][26], lab[MAXN];
char st[MAXCHAR];

int cnt = 0, tot;

void trieInsert() {
    int len = strlen(st);
    int tmp = 1;
    for (int i = 0; i < len; ++i) {
        int x = st[i] - 'a';
        if (son[tmp][x] == 0) son[tmp][x] = tot++;
        tmp = son[tmp][x];
    }
    belong[tmp] = 1;
}

int com(int u, int v) {
    return val[u] < val[v];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    tot = 2;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", st);
        trieInsert();
    }
    for (int i = 0; i < tot; ++i) lab[i] = i;
    int cnt = 2;
    for (int i = 0; i < tot; ++i) {
        if (belong[i] == 0) belong[i] = 2;
        val[i] = belong[i];
    }
    sort(lab, lab + tot, com);
    while (1) {
        int flag = 0;
        for (int al = 0; al < 26; ++al) {
            int newCnt = 0;
            for (int i = 0; i < tot; ++i) {
                int j = i;
                for (; j + 1 < tot && belong[lab[j + 1]] == belong[lab[i]]; )
                    ++j;
                for (int k = i; k <= j; ++k) val[lab[k]] = belong[son[lab[k]][al]];
                sort(lab + i, lab + j + 1, com);
                for (int k = i; k <= j; ++k) {
                    int k1 = k;
                    ++newCnt;
                    for (; k1 + 1 <= j && val[lab[k1 + 1]] == val[lab[k]]; ++k1);
                    for (int k2 = k; k2 <= k1; ++k2)
                        tbel[lab[k2]] = newCnt;
                    k = k1;
                }
                i = j;
            }
            for (int i = 0; i < tot; ++i)
                belong[i] = tbel[i];
            if (newCnt > cnt) {
                cnt = newCnt;
                flag = 1;
                /*    printf("%c\n", al + 'a');
                for (int i = 1; i <= newCnt; ++i) {
                    printf("%d: ", i);
                    for (int j = 0; j < tot; ++j)
                        if (belong[j] == i)
                            printf("%d ", j);
                    printf("\n");
                    } */
            }
        }
        if (!flag) break;
    }
    //for (int i = 0; i < tot; ++i)
    //  cout << belong[i] << endl;
    // cout << tot << endl;
    int ttt = 0;
    for (int i = 0; i < tot; ++i)
        if (belong[0] == belong[i])
            ++ttt;
    if (ttt == 1) cnt--;
    printf("%d\n", cnt);
    return 0;
}