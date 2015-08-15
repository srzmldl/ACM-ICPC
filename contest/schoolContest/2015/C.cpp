#include <bits/stdc++.h>
#define MAXN 512
#define MST(a, b) memset(a, b, sizeof(a));
using namespace std;
typedef int arrayN[MAXN];

map<string, int> mp;
int d[MAXN][MAXN], b[MAXN];
string g[MAXN];

int check(int u, int v)
{
    int betterV = 0;
    int betterU = 0;
    int lab = 1;
    for (int i = 1; i <= d[v][0] && lab <= d[v][0]; ++i)
    {
        for (; lab <= d[v][0] && d[u][i] > d[v][lab]; ++lab);
        if (lab <= d[v][0]) betterU++;
    }
    lab = 1;
    for (int i = 1; i <= d[v][0] && lab <= d[v][0]; ++i)
    {
        for (; lab <= d[u][0] && d[v][i] > d[u][lab]; ++lab);
        if (lab <= d[v][0]) betterV++;
    }
    return betterV > betterU;
}

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
            d[i][0] = 0;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                char ch[15];
                scanf("%s", ch);
                string st;
                st.assign(&ch[0], &ch[strlen(ch)]);
                int x = mp[st];
                d[x][++d[x][0]] = j;
            }
        int ans = 1;
        for (int i = 1; i <= m; ++i)
        {
            //sort(d[i] + 1, d[i] + n + 1);
            for (int j = 1; j <= m; ++j)
                b[j] = 0;
            for (int j = 1; j <= d[i][0]; ++j)
                b[d[i][j]]++;
            d[i][0] = 0;
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= b[j]; ++k)
                d[i][++d[i][0]] = j;  
        }
        for (int i = 2; i <= m; ++i)
            if (check(ans, i)) ans = i;
        cout << "Case #" << t << ": " << g[ans] << endl;
    }
    return 0;
}
