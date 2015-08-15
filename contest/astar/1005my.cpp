#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 112345

using namespace std;


const int oo = 12345678;
    
struct node
{
    int value, pos;
    node (int val = 0, int pos = 0) : value(val), pos(pos){};
}g[MAXN];

int cnt, A[MAXN];

int main()
{
    freopen("1005.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        int N;
        cnt = 0;
        scanf("%d", &N);
        g[0] = node(-oo, 0);
        for (int i = 1; i <= N; ++i)
            scanf("%d", A + i);
        for (int i = 1; i <= N; ++i)
        {
            if (!cnt || (A[i] > g[cnt].value && A[i] - g[cnt].value >= i - g[cnt].pos))
                g[++cnt] = node(A[i], i);
            else
            {
                int l = 0, r = cnt;
                for (; l < r; )
                {
                    int mid = l + r + 1 >> 1;
                    if (A[i] - g[mid].value >= i - g[mid].pos)
                        l = mid;
                    else r = mid - 1;
                }
                if (A[i] - g[l].value >= i - g[l].pos)
                    g[l + 1] = node(A[i], i);
            }
        }
        printf("%d\n", N - cnt);
    }
    return 0;
}
