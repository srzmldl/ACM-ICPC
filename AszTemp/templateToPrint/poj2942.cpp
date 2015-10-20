#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAXN = 1010;
const int MAXM = 2000010;
struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];

int Index,top;
int block;//点双连通分量的个数
bool Instack[MAXN];
bool can[MAXN];
bool ok[MAXN];//标记
int tmp[MAXN];//暂时存储双连通分量中的点
int cc;//tmp的计数
int color[MAXN];//染色
void addedge(int u,int v) {
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
bool dfs(int u,int col)//染色判断二分图
{
    color[u] = col;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        int v = edge[i].to;
        if( !ok[v] )continue;
        if(color[v] != -1)
        {
            if(color[v]==col)return false;
            continue;
        }
        if(!dfs(v,!col))return false;
    }
    return true;
}
void Tarjan(int u,int pre) {
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if(v == pre)continue;
        if( !DFN[v] )
        {
            Tarjan(v,u);
            if(Low[u] > Low[v])Low[u] = Low[v];
            if( Low[v] >= DFN[u])
            {
                block++;
                int vn;
                cc = 0;
                memset(ok,false,sizeof(ok));
                do
                {
                    vn = Stack[--top];
                    Belong[vn] = block;
                    Instack[vn] = false;
                    ok[vn] = true;
                    tmp[cc++] = vn;
                }
                while( vn!=v );
                ok[u] = 1;
                memset(color,-1,sizeof(color));
                if( !dfs(u,0) )
                {
                    can[u] = true;
                    while(cc--)can[tmp[cc]]=true;
                }
            }
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
}
void solve(int n)
{
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    Index = block = top = 0;
    memset(can,false,sizeof(can));
    for(int i = 1;i <= n;i++)
        if(!DFN[i])
            Tarjan(i,-1);
    int ans = n;
    for(int i = 1;i <= n;i++)
        if(can[i])
            ans--;
    printf("%d\n",ans);
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
}
int g[MAXN][MAXN];
int main()
{
    int n,m;
    int u,v;
    while(scanf("%d%d",&n,&m)==2)
    {
        if(n==0 && m==0)break;
        init();
        memset(g,0,sizeof(g));
        while(m--)
        {
            scanf("%d%d",&u,&v);
            g[u][v]=g[v][u]=1;
        }
        for(int i = 1;i <= n;i++)
            for(int j = 1;j <= n;j++)
                if(i != j && g[i][j]==0)
                    addedge(i,j);
        solve(n);
    }
    return 0;
}