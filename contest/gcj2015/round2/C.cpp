#include <bits/stdc++.h>
#define MAXN 1123

using namespace std;

map <string, int> mp;

int mpCnt, cnt[MAXN], a[MAXN][MAXN];
int visEng[5000], visFre[5000];

int get(int &id)
{
    char ch;
    for (;;)
    {
        scanf("%c", &ch);
        if (ch >= 'a' && ch <= 'z') break;
    }
    string st = "";
    st += ch;
    for (;;)
    {
        int tmp = 0;
        (tmp = scanf("%c", &ch));
        if (tmp != EOF && ch >= 'a' && ch <= 'z')
            st += ch;
        else
        {
            if (mp.find(st) == mp.end())
            {
                mpCnt++;
                mp[st] = mpCnt;
                id = mpCnt;
            } else id = mp[st];
            if (ch == ' ') return 0;
            return 1;
        }
    }
}

int main()
{
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d: ", t);
        int N;
        scanf("%d", &N);
        mp.clear();
        mpCnt = 0;
        for (int i = 1; i <= N; ++i)
        {
            cnt[i] = 0;
            for (;;)
            {
                int id;
                int sta = get(id);
                a[i][++cnt[i]] = id;
                if (sta == 1) break;
            }
        }
        for (int i = 0; i <= mpCnt; ++i)
            visEng[i] = visFre[i] = 0;
        for (int i = 1; i <= cnt[1]; ++i)
            visEng[a[1][i]]++;
        int tmp = 0;
        int ans = 0;
        for (int i = 1; i <= cnt[2]; ++i)
        {
            visFre[a[2][i]]++;
            if (visEng[a[2][i]] && visFre[a[2][i]] == 1)
                tmp++;
        }
        ans = mpCnt;
        int ttt = tmp;
        for (int sta = 0; sta < (1 << (N - 2)); ++sta)
        {
            tmp = ttt;
            for (int i = 0; i < N - 2; ++i)
                if (sta & (1 << i))
                {
                    for (int j = 1; j <= cnt[i + 3]; ++j)
                    {
                        visFre[a[i + 3][j]]++;
                        if (visFre[a[i + 3][j]] == 1 && visEng[a[i + 3][j]])
                            tmp++;
                    }
                } else
                {
                    for (int j = 1; j <= cnt[i + 3]; ++j)
                    {
                        visEng[a[i + 3][j]]++;
                        if (visEng[a[i + 3][j]] == 1 && visFre[a[i + 3][j]])
                            tmp++;
                    }
                }

             for (int i = 0; i < N - 2; ++i)
                 if (sta & (1 << i))
                     for (int j = 1; j <= cnt[i + 3]; ++j)
                         visFre[a[i + 3][j]]--;
                 else
                     for (int j = 1; j <= cnt[i + 3]; ++j)
                         visEng[a[i + 3][j]]--;
            ans = min(ans, tmp);
        }
        printf("%d\n", ans);
    }
    return 0;
}
