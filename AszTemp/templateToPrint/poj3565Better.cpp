#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

const int N = 110 + 1;
const double INF = 1e12, EPS = 1e-6;

int n, p[N][N], fa[N];
bool used[N];
double w[N][N], u[N][N], v[N][N],  minv[N];
// smallest match
void km(int lev) {
	int i = lev;
	lev++;
	for (int j = 0; j <= n; ++j) {
		u[lev][j] = u[i][j];
		v[lev][j] = v[i][j];
		p[lev][j] = p[i][j];
		minv[j] = INF;
		used[j] = false;
	}
	p[lev][n] = i;
	int j0 = n;
	do {
		used[j0] = true;
		int i0 = p[lev][j0], j1;
        double delta = INF;
		for (int j = 0; j < n; ++j) {
			if (!used[j]) {
				double cur = w[i0][j] - u[lev][i0] - v[lev][j];
				if (cmp(cur - minv[j]) < 0) {
					minv[j] = cur;
					fa[j] = j0;
				}
				if (cmp(minv[j] - delta) < 0) {
					delta = minv[j];
					j1 = j;
				}
			}
		}
		for (int j = 0; j <= n; ++j) {
			if (used[j]) {
				u[lev][p[lev][j]] += delta, v[lev][j] -= delta;
			} else {
				minv[j] -= delta;
			}
		}
		j0 = j1;
	} while (p[lev][j0] != -1);
	do {
		int j1 = fa[j0];
		p[lev][j0] = p[lev][j1];
		j0 = j1;
	} while (j0 != n);
}

int main()
{
    for (int i = 0; i <= n; ++i) {
        u[0][i] = v[0][i] = 0;
        p[0][i] = -1, fa[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            w[i][j] = 1.0 * dist(a[i], b[j]);
        w[i][n] = 0;
    }
    for (int i = 0; i < n; ++i) km(i);
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += w[p[n][i]][i];
        printf("%d\n", p[n][i] + 1);
    }
}
