#include <bits/stdc++.h>
#define MAXN 112345

using namespace std;

int a[MAXN], b[MAXN];
long long x;
int n, d;
//x is 64-bit variable;
long long getNextX() {
    x = (x * 37 + 10007) % 1000000007;
    return x;
}
void initAB() {
    for(int i = 0; i < n; i = i + 1) {
        a[i] = i + 1;
    }
    for(int i = 0; i < n; i = i + 1) {
        swap(a[i], a[getNextX() % (i + 1)]);
    }
    for(int i = 0; i < n; i = i + 1) {
        if (i < d)
            b[i] = 1;
        else
            b[i] = 0;
    }
    for(int i = 0; i < n; i = i + 1) {
        swap(b[i], b[getNextX() % (i + 1)]);
    }
}

struct myComp
{
    bool operator()(const int &u,const int &v)
    {
        return a[u] > a[v];
    }
};
set <int, myComp> s;
vector <int> vec;

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d%d%lld", &n, &d, &x);
    initAB();
    int lim = 200;
    for (int i = 0; i < n; ++i) {
        s.insert(i);
        if (b[i] == 1) vec.push_back(i);
        set <int, myComp>::iterator it = s.begin();
        int ans = 0;
        for (int j = 1; j <= lim && it != s.end(); ++j, it++) {
            if (b[i - *it]) {
                ans = a[*it];
                break;
            }
        }
        if (ans == 0) {
            for (int j = 0; j < vec.size(); ++j) {
                ans = max(ans, a[i - vec[j]]);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}