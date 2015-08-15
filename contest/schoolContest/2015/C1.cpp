#include <bits/stdc++.h>
#define MAXN 512
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;
typedef int arrayN[MAXN];

map<string, int> mp;
int d[MAXN][MAXN], vote[MAXN];
string g[MAXN];

int main()
{
    //  freopen("C.in", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        string st;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            char ch[15];
            string st;
            scanf("%s", ch);
            st.assign(&ch[0], &ch[strlen(ch)]);
            mp[st] = i;
            g[i] = st;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                char ch[15];
                scanf("%s", ch);
                string st;
                st.assign(&ch[0], &ch[strlen(ch)]);
                int x = mp[st];
                d[i][x] = j;
            }
        for (int i = 1; i <= n; ++i)
            vote[i] = m;
        int ans = m;
        for (int i = m - 1; i >= 1; --i)
        {
            int tmp = 0;
            for (int j = 1; j <= n; ++j)
            {
                if (d[j][i] < d[j][ans])
                    vote[j] = i;
                if (vote[j] == i) tmp++;
            }
            if (tmp * 2 >= n) ans = i;
        }
        cout << "Case #" << t << ": " << g[ans] << endl;
    }
    return 0;
}
