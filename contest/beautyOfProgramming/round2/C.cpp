#include <bits/stdc++.h>
#define MO 100007
#define MAXN 210000
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

int c[200][200], sex[200];

int main()
{
    // freopen("C.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        int N, M, Q;
        scanf("%d%d%d", &N, &M, &Q);
        for (int i = 1; i <= N; ++i)
            scanf("%d", &sex[i]);
        MST(c, 0);
        long long ans = 0;
        for (int i = 1; i <= M; ++i)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            c[u][v] = c[v][u] = w;
            if (sex[u] != sex[v])
                ans += c[u][v];
        }
        cout << "Case #" << t << ":" << endl;
        for (; Q; Q--)
        {
            int k;
            scanf("%d", &k);
            if (k == 3)
            {
                cout << ans << endl;
            } else if (k == 2)
            {
                int u, v, w;
                scanf("%d%d%d", &u, &v, &w);
                if (sex[u] != sex[v])
                {
                    ans += 1LL * w - c[u][v];
                }
                c[u][v] = c[v][u] = w;
            } else
            {
                int u;
                scanf("%d", &u);
                sex[u] = 1 - sex[u];
                for (int i = 1; i <= N; ++i)
                    if (sex[u] == sex[i])
                        ans -= c[u][i];
                    else ans += c[u][i];
            }
        }
    }
    return 0;
}
