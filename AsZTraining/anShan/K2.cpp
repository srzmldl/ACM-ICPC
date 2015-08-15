#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#define EPS 1e-8
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int)(b); ++i)
#define LL long long
#define MOD 1000000007
#define pi 3.14159265358979

using namespace std;

struct point
{
    int id;
    double x, y;
    point (double a = 0, double b = 0, int dd = 0): x(a), y(b), id(dd) {}
    point operator - (point a)
    {
        return point(x - a.x, y - a.y, id);
    }
    void print()
    {
        printf("(%f, %f):%d\n", x, y, id);
    }
} p[60];

const point O = point(0, 0, -1);
const point ex = point(1, 0, -1);

int mp[60][60];

int cmp(double x) {
    if (fabs(x) < EPS) return 0;
    else if (x > 0) return 1;
    else return -1;
}

double d_mul(point g, point h)
{
    return g.x * h.x + g.y * h.y;
}

double v_mul(point g, point h)
{
    return g.x * h.y - g.y * h.x;
}

double sqr(double x)
{
    return x * x;
}

double dist(point g, point h)
{
    return sqrt(sqr(g.x - h.x) + sqr(g.y - h.y));
}

bool cmp2(point g, point h)
{
    if (!cmp(dist(g, O)))
        return 0;
    if (!cmp(dist(h, O)))
        return 1;
    double ang1 = atan2(g.x, g.y);
    double ang2 = atan2(h.x, h.y);
    if (!cmp(ang1 - ang2))
        return dist(g, O) < dist(h, O);
    return ang1 < ang2;
//    double s1 = v_mul(ex, g);
//    double s2 = v_mul(ex, h);
//    if (!cmp(s1 - s2))
//        return dist(g, O) < dist(h, O);
//    if (cmp(s1) * cmp(s2) > 0)
//        return cmp(v_mul(g, h)) > 0;
//    else
//        return cmp(s1) > 0;
}

point rota(point v, double ang)
{
    return point(v.x * cos(ang) - v.y * sin(ang), v.x * sin(ang) + v.y * cos(ang));
}

LL qp(LL x, LL y) {
    LL ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % MOD;
        y >>= 1;
        x =  x * x % MOD;
    }
    return ans;
}

void add(LL &x, LL y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

LL gcd(LL x, LL y) {
    return y ? gcd(y, x % y) : x;
}

LL calc(int d, int n, int c)
{
    return qp(c, gcd(n, d));
}

int nex(int x, int y, int n)
{
    return (x + y) % n;
}

int main() {
    //freopen("1.in", "r", stdin);

    int ttt;
    scanf("%d", &ttt);
    while (ttt--)
    {
        int n, m, c;
        scanf("%d %d %d", &n, &m, &c);
        double ox = 0, oy = 0;
        for (int i = 0; i < n; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            p[i] = point(x, y, i);
            ox += x, oy += y;
        }
        ox /= n, oy /= n;
        point cen = point(ox, oy);
        REP(i, n)
        {
            p[i] = p[i] - cen;
        }
        sort(p, p + n, cmp2);

//        REP(i, n)
//            p[i].print();

        memset(mp, 0, sizeof(mp));
        REP(i, m)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            u--, v--;
            mp[u][v] = mp[v][u] = 1;
        }
//        REP(i, n)
//            REP(j, n)
//                printf("%d%c", mp[i][j], j == n - 1 ? '\n' : ' ');
        int now = 0;
        while (now < n && cmp(dist(p[now], O)))
            now++;
        LL ans = 0;
        int num = 0;
        REP(i, now)
        {
            bool flag = true;
            REP(j, now)
                REP(k, now)
                {
                    int jj = nex(j, i, now);
                    int kk = nex(k, i, now);
                    //printf("%d %d %d %d\n", j, k, jj, kk);
                    //printf("%d %d %d %d\n", p[j].id, p[k].id, p[jj].id, p[kk].id);
                    if (mp[p[j].id][p[k].id] ^ mp[p[jj].id][p[kk].id])
                    {
                        flag = false;
                        break;
                    }
                }
            if (!flag)
                continue;
            double ang, tmp1 = asin(v_mul(p[0], p[i]) / dist(p[0], O) / dist(p[i], O));
            if (cmp(tmp1) == 0 && cmp(d_mul(p[0], p[i])) < 0) tmp1 = -pi;
            else {
                if (cmp(tmp1) > 0 && cmp(d_mul(p[0], p[i])) < 0) tmp1 = pi - tmp1;
                else {
                    if (cmp(tmp1) < 0 && cmp(d_mul(p[0], p[i])) < 0) tmp1 = -pi - tmp1;
                }
            }
            ang = tmp1;
            //cout << ang << endl;
            REP(j, now)
            {
                int k = nex(j, i, now);
                REPP(jj, now, n - 1)
                    if (mp[p[jj].id][p[j].id] ^ mp[p[jj].id][p[k].id])
                    {
                        flag = false;
                        break;
                    }
                if (cmp(dist(p[k], rota(p[j], ang))) != 0)
                {
                    flag = false;
                    break;
                }
            }
            if (!flag)
                continue;
            //cout << "hehe" << i << endl;
            add(ans, calc(i, now, c));
           // cout << ans << endl;
            num++;
        }
       //cout << ans << ' ' << num << endl;
        ans = ans * qp(num, MOD - 2) % MOD;
        ans = ans * qp(c, n - now) % MOD;
        printf("%I64d\n", ans);
    }

    return 0;
}
