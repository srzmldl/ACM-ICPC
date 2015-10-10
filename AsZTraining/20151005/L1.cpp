#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAXCHAR 35
#define MAXN 200000
#include <ext/hash_map>
#include <string>
#include <iostream>
#define LIM 2

using namespace std;
using namespace __gnu_cxx;

int wq[LIM] = {1201, 313};//, 3131, 31313};
int MO[LIM] = {1000000007, 1000000003};

int pw[LIM][MAXN * 10];
int n, tot = 0;
char st[MAXCHAR];
int son[MAXN][26];
int leng[MAXN], term[MAXN];
hash_map <int, int> mp[LIM];
int haNum[LIM][MAXN];

int cnt = 0, ans = 0;

void trieInsert() {
    int len = strlen(st);
    int tmp = 0;
    for (int i = 0; i < len; ++i) {
        int x = st[i] - 'a';
        if (son[tmp][x] == 0) son[tmp][x] = tot++;
        tmp = son[tmp][x];
    }
    term[tmp] = 1;
}

void dfs(int x) {
    leng[x] = 2;
    if (term[x]) leng[x] += 2;
    for (int t = 0; t < LIM; ++t) {
        haNum[t][x] = '(';
        if (term[x]) haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + '(')  ;
    }
    leng[x] += 26;
    for (int i = 0; i < 26; ++i) {
        if (son[x][i]) {
            int v = son[x][i];
            dfs(son[x][i]);
            leng[x] += leng[v];
            for (int t = 0; t < LIM; ++t) {
                // haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + '(')  ;
                haNum[t][x] = (1LL * haNum[t][x] * pw[t][leng[v]]   + haNum[t][v])  ;
                haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + 'a' + i)  ;
            }
           // dep[x] = max(dep[x], dep[son[x][i]] + 1);
        } else {
            leng[x]++;
            for (int t = 0; t < LIM; ++t) {
                //haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + '(')  ;
                haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + '.')  ;
                haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + 'a' + i)  ;
            }
        }
    }

  //  cout << ha[x] << endl;
    int flag = 0;
    for (int t = 0; t < LIM; ++t) {
        haNum[t][x] = (1LL * haNum[t][x] * pw[t][1]   + ')')  ;
        if (!mp[t].count(haNum[t][x])) {
            mp[t][haNum[t][x]] = ++cnt;
            flag = 1;
        };
    } //haNum[x] = mp[ha[x]];
    if (flag) ans++;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    tot = 1;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", st);
        trieInsert();
    }
    for (int i = 0; i < LIM; ++i) {
        pw[i][0] = 1;
        for (int j = 1; j < MAXN * 10; ++j)
            pw[i][j] = 1LL * pw[i][j - 1] * wq[i];
    }
    dfs(0);
    //cout << tot << endl;
   // for (int i = 0; i < tot; ++i)
     //   lab[i] = i;
   // sort(lab, lab + tot, com);
   // for (int i = 0; i < tot; ++i) {
     //   int u = lab[i];
      //  int j = i;
      //  for (; j + 1 < tot && dep[lab[j + 1]] == dep[u]; ++j);

   // }
    printf("%d\n", ans);
    return 0;
}