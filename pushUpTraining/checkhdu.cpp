#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
#define N 200005
typedef long long ll;
int n;
int l[N], r[N], c[N];

struct Node{
    ll cost;
    int id;
    Node(ll _cost, ll _id){
        cost = _cost;
        id = _id;
    }
    Node(){}
    bool operator<(const Node &X)const{
        if (X.cost == cost){
            return id < X.id;
        }
        return cost < X.cost;
    }
};

set<Node> from;
set<int> now;
vector<int> wait;
ll dp[N];

int main(){
    freopen("in.txt", "r", stdin);
    freopen("outstd.txt", "w", stdout);
    int _;
    scanf("%d", &_);
    while (_--){
        scanf("%d", &n);
        for (int i = 1; i <= n; ++ i){
            scanf("%d", &l[i]);
        }
        for (int i = 1; i <= n; ++ i){
            scanf("%d", &r[i]);
        }
        for (int i = 1; i <= n; ++ i){
            scanf("%d", &c[i]);
        }
        from.clear();
        now.clear();
        for (int i = 1; i <= n; ++ i){
            dp[i] = -1;
        }

        from.insert(Node(c[1], 1));
        dp[1] = 0;
        for (int i = 2; i <= n; ++ i){
            now.insert(i);
        }

        while (!from.empty()){
            int k = (*from.begin()).id; from.erase(from.begin());

            wait.clear();
            set<int>::iterator it = now.lower_bound(l[k] + k);
            while (it != now.end()){
                int to = (*it);
                if (to > r[k] + k) break;
                dp[to] = dp[k] + 1ll * c[k];
                wait.push_back(to);
                ++ it;
            }
            for (int i = 0; i < wait.size(); ++ i){
                now.erase(wait[i]);
                from.insert(Node(dp[wait[i]] + 1ll * c[wait[i]], wait[i]));
            }

            wait.clear();
            it = now.upper_bound(k - l[k]);
            if (it == now.begin()) continue;
            do{
                -- it;
                int to = (*it);
                if (to < k - r[k]) break;
                dp[to] = dp[k] + 1ll * c[k];
                wait.push_back(to);                
            }while(it != now.begin());
            for (int i = 0; i < wait.size(); ++ i){
                now.erase(wait[i]);
                from.insert(Node(dp[wait[i]] + 1ll * c[wait[i]], wait[i]));
            }
        }
        for (int i = 1; i <= n; ++ i){
            printf("%lld%c", dp[i], i == n ? '\n' : ' ');
        }
    }
    return 0;
}
