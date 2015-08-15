#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int)(b); ++i)
#define MAXN 60000
using namespace std;


int a[MAXN];
int n, k;
double sum[MAXN], sumSq[MAXN];

int main() {
    freopen("in.txt", "r", stdin);
    int task;
    for (scanf("%d", &task); task; --task)
    {
        scanf("%d%d", &n, &k);
        sum[0] = sumSq[0] = 0;
        REPP(i, 1, n) scanf("%d", a +i);
        sort(a +1, a + n +1);
        REPP(i, 1, n)
        {
            sum[i] = sum[i - 1] +a[i];
            sumSq[i] = sumSq[i - 1] +1.0 *a[i] *a[i];
        }
        double ans = 1e20;
        if (k >= n) ans = 0.0;
        else
        {
            REPP(i, 1, k +1)
            {
                int r = i +n - k - 1;
                double x = (sum[r] - sum[i - 1]) / (n - k);
                double tmp = (n - k) * x *x + sumSq[r] - sumSq[i - 1] - 2 *x *(sum[r] - sum[i - 1]);
                ans = min(ans, tmp);
            }
        }
        printf("%.10f\n", ans);
    }
    return 0;

}

