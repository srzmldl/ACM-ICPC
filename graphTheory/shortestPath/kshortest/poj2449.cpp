#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define REP(i,a,b) for(int i=a;i<=b;i++)
#define foreach(i,vec) for(unsigned i=0;i<vec.size();i++)
#define pb push_back
#define RD3(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define MP make_pair
#define Clear(x) memset(x,0,sizeof(x))
#define PII pair< int, int>

using namespace std;
//g(n) 是在状态空间中从初始节点到n节点的实际代价，
//h(n) 是从n到目标节点最佳路径的估计代价。
//t 第k次出堆即得k短

using namespace std;

const int MAXN = 1e3+5;
const int INF = 1e9;

vector< PII > adj[MAXN];
vector< PII > radj[MAXN];
int dis[MAXN], id[MAXN], n,m;
bool use[MAXN];

struct node{
    int x,g,h;
    node(){}
    node(int a,int b,int c){
        x = a;
        g = b;
        h = c;
    }
    friend bool operator < (node a,node b){
        return a.g+a.h>b.g+b.h;
    }
};

void spfa(int s){
    queue<int> q;
    q.push(s);
    rep1(i,n)
        dis[i] = INF;
    dis[s] = 0;
    memset(use,false,sizeof(use));
    while(q.size()){
        int x = q.front();
        q.pop();
        use[x] = false;
        foreach(i,radj[x]){
            int y = radj[x][i].first;
            int t = radj[x][i].second + dis[x];
            if(dis[y]>t){
                dis[y] = t;
                if(!use[y]){
                    use[y] = true;
                    q.push(y);
                }
            }
        }
    }
}

int Astar(int s,int t,int k){
    if(dis[s]==INF)return -1;
    if(s==t)k ++;

    Clear(id);

    priority_queue< node > q;
    q.push( node( s,0,dis[s] ) );

    while(q.size()){
        node p = q.top();
        q.pop();
        int x = p.x;

        id[x] ++;
        if(id[x]>k)continue;
        if(id[t]==k)return p.g+p.h;

        foreach(i,adj[x]){
            int y = adj[x][i].first;
            int w = adj[x][i].second;
            q.push( node( y,p.g+w,dis[y] ) );
        }
    }
    return -1;
}

int main(){
    while(cin>>n>>m){
        rep1(i,n){
            adj[i].clear();
            radj[i].clear();
        }
        int x,y,z;
        while(m--){
            RD3(x,y,z);
            adj[x].pb( MP(y,z) );
            radj[y].pb( MP(x,z) );
        }

        int s,t,k;
        RD3(s,t,k);
        spfa(t);
        cout<<Astar(s,t,k)<<endl;
    }
	return 0;
}