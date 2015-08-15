#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int)(b); ++i)
#define LL long long

using namespace std;

const int N = 100005;
int p[N], vis[N], tot;
int cnt[N], a[N];

void GetPrime() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) p[tot++] = i;
        for (int j = 0; j < tot && i * p[j] < N; ++j) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}

LL cal(int x) {
    LL ans = 0;
    ans = 1ll * x * (x - 1) * (x - 2) / 6;
    return ans;
}

int fac[40], fcnt;

void dfs(int dep, int now, int odd, int &ans) {
    if (dep == fcnt) {
        if (odd) ans -= cnt[now];
        else ans += cnt[now];
    }
    else {
        REP(i, 2) {
            dfs(dep + 1, now, odd, ans);
            now *= fac[dep];
            odd ^= 1;
        }
    }
}

LL getans(int x, int n) {
    int tmp = x;
    fcnt = 0;
    for (int j = 0; j < tot && p[j] * p[j] <= tmp; ++j) {
        if (tmp % p[j] == 0) {
            fac[fcnt] = p[j];
            while (tmp % p[j] == 0) {
                tmp /= p[j];
            }
            fcnt++;
        }
    }
    if (tmp > 1) {
        fac[fcnt++] = tmp;
    }
    int co = 0;
    dfs(0, 1, 0, co);
    return 1ll * (co) * (n - 1 - co);
}

int main() {
    ios :: sync_with_stdio(0);
    //freopen("in.txt", "r", stdin);

    int t, n;

    GetPrime();
    cin >> t;
    while (t--) {
        cin >> n;
        REPP(i, 1, N - 1) cnt[i] = 0;
        REPP(i, 1, n) {
            cin >> a[i];
            for (int j = 1; j * j <= a[i]; ++j) {
                if (a[i] % j == 0) {
                    cnt[j]++;
                    if (j != a[i] / j) cnt[a[i] / j]++;
                }
            }
        }

        //REPP(i, 1, 10) cout << i << ' ' << cnt[i] << endl;

        LL ans = cal(n), tmp = 0;
       // cout << ans << endl;
        REPP(i, 1, n) if (a[i] != 1){
            //cout << getans(a[i], n) << endl;
            tmp += getans(a[i], n);
        }
        //cout << tmp << endl;
        cout << ans - tmp / 2 << endl;
    }


    return 0;
}
