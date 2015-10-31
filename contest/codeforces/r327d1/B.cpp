#include <bits/stdc++.h>

using namespace std;

const double esp = 1e-8;
int vmax, t;
struct point {
    int x, y;
    point(int x = 0, int y = 0) : x(x), y(y) {};
} A, B, C, hA;

int cmp(double u, double v) {
    if (u > v + esp) return 1;
    if (u < v - esp) return -1;
    return 0;
}

double sqr(double x) {
    return 1.0 * x * x;
}
double dot(point u, point v) {
    return 1.0 * v.x * u.x + 1.0 * v.y * u.y;
}

double len(point v) {
    return sqrt(sqr(v.x) + sqr(v.y));
}
double reflect(point u, point v) {
    double dt = dot(u, v);
    return dt / len(v);
}

double solveI(point pp, int kind) {
    int vx = pp.x, vy = pp.y;
    double tt, vv;
    if (vx == 0 && vy == 0) {
        tt = sqrt(sqr(A.x) + sqr(A.y)) / vmax;
        vv = vmax;
    } else {
        point tmp = point(vx, 0);
        double px = reflect(tmp, A);
        double py = reflect(tmp, hA);
        tmp = point(0, vy);
        px += reflect(tmp, A);
        py += reflect(tmp, hA);
        double vnow = sqrt(sqr(vmax) - sqr(py));
        vnow += px;
        tt = len(A) / vnow;
        vv = vnow;
    }
    if (kind == 0) return tt;
    else return vv;
}
double solveII(int x1, int y1, int x2, int y2, point pp) {
    int vx = pp.x, vy = pp.y;
    int nx = x1 + t * B.x;
    int ny = y1 + t * B.y;
    A = point(x2 - nx, y2 - ny);
    double d = len(A);
    if (vx == 0 && vy == 0) {
        return d / vmax;
    }
    double cs = dot(A, C) / len(A) / len(C);
    double a = sqr(vx) + sqr(vy) - sqr(vmax);
    double b = -2 * len(pp) * t - 2 * d * len(pp) * cs;
    double c = sqr(d) + 2 * d * len(pp) * t * cs;
    return max(((-b) - sqrt(sqr(b) - 4 * a * c)) / 2 / a, ((-b) + sqrt(sqr(b) - 4 * a * c)) / 2 / a);
}

int main() {
    freopen("B.in", "r", stdin);
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    scanf("%d%d", &vmax, &t);
    double x;
    int vx, vy, wx, wy;
    scanf("%d%d%d%d", &vx, &vy, &wx, &wy);
    if (x1 == x2 && y1 == y2) x = 0;
    else {
        A = point(x2 - x1, y2 - y1);
        hA = point(A.y, -A.x);
        B = point(vx, vy);
        C = point(wx, wy);
        x = solveI(B, 0);
        if (cmp(x, t) > 0) x = solveII(x1, y1, x2, y2, C);
    }
    printf("%.9f\n", x);
    return 0;
}