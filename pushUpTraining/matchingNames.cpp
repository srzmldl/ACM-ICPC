#include <bits/stdc++.h>
#define MAXN 112345
#define MAXCH 812345

using namespace std;

int n, tot;
char st[MAXCH];

struct node
{
    int son[26];
    vector <int> vec[2];
    int cnt[2];
} g[MAXCH];

void tireAdd(char *st, int k, int lab)
{
    int p = 1;
    int len = strlen(st);
    for (int i = 0; i < len; ++i)
    {
        g[p].cnt[k]++;
        int u = st[i] - 'a';
        if (g[p].son[u] == 0)
            g[p].son[u] = ++tot;
        p = g[p].son[u];
    }
    g[p].cnt[k]++;
    g[p].vec[k].push_back(lab);
}

void mergeVec(node &u, node &v, int k)
{
    if (u.vec[k].size() < v.vec[k].size())
        swap(u.vec[k], v.vec[k]);
    for (; v.vec[k].size();)
    {
        u.vec[k].push_back(v.vec[k].back());
        v.vec[k].pop_back();
    }
}
void dfs(int x)
{
    for (int p = 0; p < 26; ++p)
        if (g[x].son[p])
        {
            int u = g[x].son[p];
            dfs(u);
            for (int i = 0; i <= 1; ++i)
                if (g[u].vec[i].size())
                    mergeVec(g[x], g[u], i);
        }
    
    for (;g[x].vec[0].size() && g[x].vec[1].size();)
    {
        int u = g[x].vec[1].back();
        int v = g[x].vec[0].back();
        cout << u << ' ' << v << endl;
        g[x].vec[1].pop_back();
        g[x].vec[0].pop_back();
    }

}

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    tot = 1;
    for (int i = 1; i <= 2 * n; ++i)
    {
        scanf("%s", st);
        tireAdd(st, i <= n ? 1 : 0, i <= n ? i : i - n);
    }
    long long ans = 0;
    for (int i = 1; i <= tot; ++i)
        for (int j = 0; j < 26; ++j)
            if (g[i].son[j])
                ans += 1LL * min(g[g[i].son[j]].cnt[0], g[g[i].son[j]].cnt[1]);
    cout << ans << endl;
    dfs(1);
    return 0;
}