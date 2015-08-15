#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

double t[1010], x[1010], y[1010];

double sqr(double x)
{
    return x * x;
}

double dist(int g, int h)
{
    return sqrt(sqr(x[g] - x[h]) + sqr(y[g] - y[h]));
}

int main()
{
    int ttt;
    scanf("%d", &ttt);
    while (ttt--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%lf %lf %lf", &t[i], &x[i], &y[i]);
        double ans = 0;
        for (int i  = 1; i < n; i++)
            ans = max(ans, dist(i, i - 1) / (t[i] - t[i - 1]));
        printf("%.10f\n", ans);
    }
    return 0;
}

