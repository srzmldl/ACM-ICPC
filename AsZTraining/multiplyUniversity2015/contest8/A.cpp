#include <bits/stdc++.h>
#define MAXN 412345

using namespace std;

struct node
{
    int a, buy, sell;
} g[MAXN];


int main()
{
    freopen("in.txt", "r", stdin);
    int ca;
    for (scanf("%d", &ca); ca; --ca)
    {
        int N, C;
        scanf("%d%d", &N, &C);
        for (int i = 1; i <= N; ++i)
            scanf("%d", &g[i].a);
        g[0].a = 0;
        for (int i = 0; i <= N; ++i)
            scanf("%d%d", &g[i].buy, &g[i].sell);
        long long ans = -1LL * C * g[0].buy;
        deque < pair <int, int> > deq;
        deq.push_back(make_pair(C, g[0].buy));
        for (int i = 1; i <= N; ++i)
        {
            int tmp = g[i].a - g[i - 1].a;
            for (; tmp ;)
            {
                int cnt = deq.front().first;
                int price = deq.front().second;
                deq.pop_front();
                int tcnt = min(cnt, tmp);
                tmp -= tcnt;
                cnt -= tcnt;
                if (cnt) deq.push_front(make_pair(cnt, price));
            }
            tmp = (g[i].a - g[i - 1].a);
            for (; !deq.empty();)
            {
                int cnt = deq.back().first;
                int price = deq.back().second;
                deq.pop_back();
                if (price >= g[i].buy)
                {
                    ans += 1LL * price * cnt;
                    tmp += cnt;
                } else
                {
                    deq.push_back(make_pair(cnt, price));
                    break;
                }
            }
            ans -= 1LL * tmp * g[i].buy;
            deq.push_back(make_pair(tmp, g[i].buy));

            tmp = 0;
            for (;;)
            {
                int cnt = deq.front().first;
                int price = deq.front().second;
                deq.pop_front();
                if (price <= g[i].sell) tmp += cnt;
                else
                {
                    deq.push_front(make_pair(cnt, price));
                    break;
                }
            }
            if (tmp) deq.push_front(make_pair(tmp, g[i].sell));

            /*  deque < pair <int, int> > :: iterator it = deq.begin();
            for (; it != deq.end(); it++)
                cout << (*it).first << ' ' << (*it).second << endl;
            cout << i << endl;
            cout << endl; */
        }
        for (;!deq.empty();)
        {
            ans += 1LL * deq.front().first * deq.front().second;
            deq.pop_front();
        }
        cout << -ans << endl;
    }
    return 0;
}
