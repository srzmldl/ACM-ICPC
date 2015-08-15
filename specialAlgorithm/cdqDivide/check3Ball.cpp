#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define REDD(i, a, b) for(int i = (int) (a); i >= (int) (b); --i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 111111

using namespace std;
int zLim;

int t, g[MAXN *4], n;
struct node
{
    int x, y, z, f;
} a[MAXN];


int ok(node A, node B)
{
    return A.x <= B.x && A.y <= B.y && A.x <= B.z;
}

void link(int u, int v)
{
    e[++num] = v, nxt[num] = fir[u];
    fir[u] = num;
}

int main()
{
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    REPP(i, 1, n)
    {
        scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
        a[i].f = 1;
    }
    num = 0;
    MST(fir, 0);
    REPP(i, 1, n)
        REPP(j, 1, n)
            if (i != j && ok(a[i], a[j]))
                link(i, j);
    return 0;
}
