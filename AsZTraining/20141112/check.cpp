#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 350
using namespace std;

int n,m,ans;
int sx,sy,ex,ey;
int x[maxn],y[maxn];
int xx[maxn],yy[maxn];
int mp[maxn][maxn];
int up[maxn][maxn],down[maxn][maxn];
int le[maxn][maxn],ri[maxn][maxn];
int dx[]= {-3,3,0,0};
int dy[]= {0,0,-3,3};
bool vis[maxn][maxn][4];  // 三维判重 x+y+方向
struct Node
{
    int l,d,r,u;
} rect[maxn];
struct node
{
    int mx,my;
    int d,cnt;   // 方向 转向次数
} cur,now,q[maxn*maxn];

void showxxyy()  // 输出离散化后的x y
{
    int i,j;
    printf("xx:\n");
    for(i=1; i<=m; i++)
    {
        printf("%d ",xx[i]);
    }
    printf("\n");
    printf("yy:\n");
    for(i=1; i<=m; i++)
    {
        printf("%d ",yy[i]);
    }
    printf("\n");
}
void showmap()  // 输出地图
{
    int i,j;
    printf("showmap:\n");
    printf("       1  2  3  4  5  6  7  8  9  10 11 12 \n");
    for(i=1; i<=3*xx[m]; i++)
    {
        printf("%3d: ",i);
        for(j=1; j<=3*yy[m]; j++)
        {
            printf("%d",mp[i][j]);
        }
        printf("\n");
    }
}
void disc()   // 离散化
{
    int i,j;
    m=2*n+2;
    sort(x+1,x+m+1);
    xx[1]=1;
    for(i=2; i<=m; i++)
    {
        if(x[i]==x[i-1]) xx[i]=xx[i-1];
        else xx[i]=xx[i-1]+1;
    }
    sort(y+1,y+m+1);
    yy[1]=1;
    for(i=2; i<=m; i++)
    {
        if(y[i]==y[i-1]) yy[i]=yy[i-1];
        else yy[i]=yy[i-1]+1;
    }
//    showxxyy();
}
int find(int v,int k)   // 找到离散化对应的点
{
    int i,j;
    if(k)
    {
        for(i=1; i<=m; i++)
        {
            if(y[i]==v) return yy[i];
        }
    }
    else
    {
        for(i=1; i<=m; i++)
        {
            if(x[i]==v) return xx[i];
        }
    }
}
void buildgraph()  // 将1*1的方格转化为3*3的方格后建图
{
    int i,j,ni,nj,k,l,d,r,u;
    memset(mp,0,sizeof(mp));
    memset(up,1,sizeof(up));
    memset(down,1,sizeof(down));
    memset(le,1,sizeof(le));
    memset(ri,1,sizeof(ri));
    for(k=1; k<=n; k++)  // 将矩形在地图上涂黑
    {
        l=3*find(rect[k].l,0)+1;
        d=3*find(rect[k].d,1)+1;
        r=3*find(rect[k].r,0)-1;
        u=3*find(rect[k].u,1)-1;
//        printf("l:%d d:%d r:%d u:%d\n",l,d,r,u);
        for(i=l; i<=r; i++)
        {
            for(j=d; j<=u; j++)
            {
                mp[i][j]=1;
            }
        }
    }
    for(i=1; i<=xx[m]; i++)  // 记录是否能走 是否是‘L’型区域
    {
        for(j=1; j<=yy[m]; j++)
        {
            ni=3*i;
            nj=3*j;
            if(mp[ni-1][nj-1]&&mp[ni+1][nj+1])
            {
                up[ni][nj]=down[ni][nj]=le[ni][nj]=ri[ni][nj]=-1;
            }
            else if(mp[ni+1][nj-1]&&mp[ni-1][nj+1]) up[ni][nj]=down[ni][nj]=le[ni][nj]=ri[ni][nj]=-2;
            if(mp[ni-1][nj-1]&&mp[ni-1][nj+1]) up[ni][nj]=0;
            if(mp[ni+1][nj-1]&&mp[ni+1][nj+1]) down[ni][nj]=0;
            if(mp[ni-1][nj-1]&&mp[ni+1][nj-1]) le[ni][nj]=0;
            if(mp[ni-1][nj+1]&&mp[ni+1][nj+1]) ri[ni][nj]=0;
        }
    }
//    showmap();
}
bool bfs() // 图建好了 就是简单的bfs了
{
    int i,j,nx,ny,nd,ncnt,tx,ty;
    int head=0,tail=-1;
    memset(vis,0,sizeof(vis));
    sx=3*find(sx,0);
    sy=3*find(sy,1);
    ex=3*find(ex,0);
    ey=3*find(ey,1);
//    printf("sx:%d sy:%d ex:%d ey:%d\n",sx/3,sy/3,ex/3,ey/3);
    cur.mx=sx;
    cur.my=sy;
    cur.d=-1;
    cur.cnt=0;
    vis[sx][sy][0]=vis[sx][sy][1]=vis[sx][sy][2]=vis[sx][sy][3]=1;
    q[++tail]=cur;
    while(head<=tail)
    {
        now=q[head];
        head++;
        nx=now.mx;
        ny=now.my;
        nd=now.d;
        ncnt=now.cnt;
//        printf("nx:%d ny:%d nd:%d ncnt:%d\n",nx/3,ny/3,nd,ncnt);
        if(nx==ex&&ny==ey)
        {
            ans=ncnt;
            return true ;
        }
        for(i=0; i<4; i++)
        {
            if(i==0&&!up[nx][ny]||i==1&&!down[nx][ny]||i==2&&!le[nx][ny]||i==3&&!ri[nx][ny]) continue ; // 判断是否能往这个方向走
            if(up[nx][ny]==-1)    // 对‘L’型区域特判
            {
                if(i==0&&(nd==0||nd==3)) continue ;
                else if(i==1&&(nd==1||nd==2)) continue ;
                else if(i==2&&(nd==2||nd==1)) continue ;
                else if(i==3&&(nd==3||nd==0)) continue ;
            }
            else if(up[nx][ny]==-2)
            {
                if(i==0&&(nd==0||nd==2)) continue ;
                else if(i==1&&(nd==1||nd==3)) continue ;
                else if(i==2&&(nd==2||nd==0)) continue ;
                else if(i==3&&(nd==3||nd==1)) continue ;
            }
            tx=nx+dx[i];
            ty=ny+dy[i];
            while(tx>=1&&tx<=3*xx[m]&&ty>=1&&ty<=3*yy[m]&&!mp[tx][ty]) // 每次向一个方向搜索
            {
                if(!vis[tx][ty][i])
                {
                    vis[tx][ty][i]=1;
                    cur.mx=tx;
                    cur.my=ty;
                    cur.d=i;
                    cur.cnt=ncnt;
                    if(cur.d!=nd&&nd!=-1) cur.cnt++;
                    q[++tail]=cur;
                }
                if(i==0&&!up[tx][ty]||i==1&&!down[tx][ty]||i==2&&!le[tx][ty]||i==3&&!ri[tx][ty]) break ;
                if(up[tx][ty]==-1||up[tx][ty]==-2) break ;
                tx+=dx[i];
                ty+=dy[i];
            }
        }
    }
    return false ;
}
int main()
{
    int i,j;
    int x1,y1,x2,y2,l,d,r,u;
    while(scanf("%d%d%d%d",&sx,&sy,&ex,&ey),sx||sy||ex||ey)
    {
        scanf("%d",&n);
        for(i=1; i<=n; i++)
        {
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            l=min(x1,x2);
            r=max(x1,x2);
            d=min(y1,y2);
            u=max(y1,y2);
            x[i]=rect[i].l=l;
            x[i+n]=rect[i].r=r;
            y[i]=rect[i].d=d;
            y[i+n]=rect[i].u=u;
        }
        x[2*n+1]=sx;
        x[2*n+2]=ex;
        y[2*n+1]=sy;
        y[2*n+2]=ey;
        disc();
        buildgraph();
        if(bfs()) printf("%d\n",ans);
        else printf("-1\n");
    }
    return 0;
}
/*

// 绕路   2
1 1 1 4
1
0 2 2 3

// 直走  0
1 1 1 4
1
3 3 4 5

// 沿着边直走  0
0 1 0 7
2
0 2 2 3
-1 4 0 5

// 沿着边直走  0
0 1 0 7
2
0 2 2 3
0 3 2 4

// 无法穿过缝隙，绕路   2
0 1 0 7
2
0 2 2 3
-1 3 0 5

// 无法到达  -1
0 0 5 5
4
-1 1 1 2
1 -1 2 1
-1 -1 1 -2
-1 1 -2 -1

// 同点经过两次。  5
1 3 4 1
10
-1 -1 3 2
3 -1 7 0
7 -1 11 3
9 3 11 7
-1 7 11 9
0 5 4 7
-1 2 0 7
2 2 4 3
4 3 5 4
5 4 8 6
*/
