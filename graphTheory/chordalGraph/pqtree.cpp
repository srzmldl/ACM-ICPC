#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
#include<ctime>
#include<set>
#include<queue>
#include<cmath>
#include<vector>
#include<functional>
#define pb push_back
using namespace std;

typedef long long LL;
typedef double ld;

const int MAX=500+10;

int n,m,hash[MAX],nowTest;
char g[MAX][MAX];

void fail()
{
    printf("NO\n");
    exit(0);
}

struct node
{
    vector<int> ch;
    int kind;//P:0 or Q:1
    int leaf;//when it is leaf it is the same with its number
    int color;//zero 0 half 1 full 2
    node(){kind=leaf=0;}
}tree[MAX*MAX];
int Ncnt,Root;

void Add(int u,int v)
{
    tree[v].ch.pb(u);
}

void initTree()
{
    int i;
    Root=++Ncnt;
    for(i=1;i<=n;++i)
    {
        ++Ncnt;
        tree[Ncnt].leaf=i;
        Add(Ncnt,Root);
    }
}

void paint(int u)
{
    if(tree[u].leaf)
    {
        if(hash[tree[u].leaf])tree[u].color=2;
        else tree[u].color=0;
        return;
    }
    int v,zero=1,full=1,half=0,j;
    for(j=0;j<(int)tree[u].ch.size();++j)
    {
        v=tree[u].ch[j];
        paint(v);
        if(tree[v].color)zero=0;
        if(tree[v].color==0)full=0;
        if(tree[v].color==1)half=1;
    }
    if((!full && !zero) || half)tree[u].color=1;
    else if(full)tree[u].color=2;
    else if(zero)tree[u].color=0; 
}

void clear(int u)
{
    int j,v;
    vector<int> newson;
    for(j=0;j<(int)tree[u].ch.size();++j)
    {
        v=tree[u].ch[j];
        if(tree[v].leaf)
        {
            newson.pb(v);
            continue;
        }
        if((int)tree[v].ch.size()==1)
            newson.pb(tree[v].ch[0]);
        else newson.pb(v);
    }
    tree[u].ch=newson;
    if((int)tree[u].kind==1 && (int)tree[u].ch.size()<=2)
        tree[u].kind=0;
}

void Arrange(int u)
{
    vector<int> son=tree[u].ch,emp,ful;
    if(tree[u].leaf)return;
    int d=0,i,j=0,v,p=0;
    for(j=0;j<(int)tree[u].ch.size();++j)
    {
        v=tree[u].ch[j];
        if(tree[v].color==1)
        {
            if(d)fail();
            if(!d)d=v,p=j;
        }
        if(tree[v].color==0)emp.pb(j);
        if(tree[v].color==2)ful.pb(j);
    }
    if(d)Arrange(d);
    int nemp=(int)emp.size(),nful=(int)ful.size();
    if(tree[u].kind)
    {
        if( ( nemp && emp[nemp-1]-emp[0]+1!=nemp ) || (nful && ful[nful-1]-ful[0]+1!=nful ) )
            fail();
        if(d)
        {
            if(nemp && nful)
            {
                if(emp[0]<ful[0] && d==son[0])
                    fail();
                else if(emp[0]>ful[0] && d==son[(int)son.size()-1])
                    fail();
            }
        }
        if(nemp && nful)
        {
            if(emp[0]>ful[0])
            {
                reverse(emp.begin(),emp.end());
                reverse(ful.begin(),ful.end());
            }
        }
        if(nemp && !nful && d)
            if(emp[0]>p)reverse(emp.begin(),emp.end());
        if(nful && !nemp && d)
            if(ful[0]<p)reverse(ful.begin(),ful.end());
        vector<int> newson;
        for(i=0;i<(int)emp.size();++i)
            newson.pb(son[emp[i]]);
        if(d)
        {
            for(j=0;j<(int)tree[d].ch.size();++j)
                newson.pb(tree[d].ch[j]);
        }
        for(i=0;i<(int)ful.size();++i)
            newson.pb(son[ful[i]]);
        tree[u].ch=newson;
    }
    else
    {
        tree[u].kind=1;
        vector<int> newson;
        if(nemp)
        {
            ++Ncnt;
            for(i=0;i<nemp;++i)
                tree[Ncnt].ch.pb(son[emp[i]]);
            clear(Ncnt);
            newson.pb(Ncnt);
        }
        if(d)
        {
            for(j=0;j<(int)tree[d].ch.size();++j)
                newson.pb(tree[d].ch[j]);
        }
        if(nful)
        {
            ++Ncnt;
            for(i=0;i<nful;++i)
                tree[Ncnt].ch.pb(son[ful[i]]);
            clear(Ncnt);
            newson.pb(Ncnt);
        }
        tree[u].ch=newson;
    }
    clear(u);
}

void Goto(int u)
{
    if(tree[u].leaf)return;
    int v,j,cnt=0,full=0,i;
    for(j=0;j<(int)tree[u].ch.size();++j)
    {
        v=tree[u].ch[j];
        if(tree[v].color==1)++cnt;
        if(tree[v].color==2)full=1;
    }
    if(cnt>=3)
        fail();
    if(full || cnt>1)
    {
        vector<int> son=tree[u].ch,hf,ff;
        for(j=0;j<(int)tree[u].ch.size();++j)
        {
            v=tree[u].ch[j];
            if(tree[v].color==1)hf.pb(j);
            if(tree[v].color==2)ff.pb(j);
        }
        int nhf=(int)hf.size(),nff=(int)ff.size();
        if(tree[u].kind==1)
        {
            if(nff && ff[nff-1]-ff[0]+1!=nff)
                fail();
            for(j=0;j<nhf;++j)
                if(nff && hf[j]!=ff[0]-1 && hf[j]!=ff[nff-1]+1)
                    fail();
            vector<int> newson;
            for(j=0;j<(int)son.size();++j)
            {
                if(tree[son[j]].color!=1)
                    newson.pb(son[j]);
                else
                {
                    Arrange(v=son[j]);
                    vector<int> pp;
                    for(i=0;i<(int)tree[v].ch.size();++i)
                        pp.pb(tree[v].ch[i]);
                    if((nhf!=1 && j!=hf[0]) || (nhf==1 && nff && hf[0]==ff[nff-1]+1))
                        reverse(pp.begin(),pp.end());
                    for(i=0;i<=(int)pp.size()-1;++i)
                        newson.pb(pp[i]);
                }
            }
            tree[u].ch=newson;
        }
        else
        {
            vector<int> newson;
            for(j=0;j<(int)hf.size();++j)
                Arrange(son[hf[j]]);
            for(j=0;j<(int)son.size();++j)
                if(tree[son[j]].color==0)
                    newson.pb(son[j]);
            int np1=++Ncnt;
            tree[np1].kind=1;
            newson.pb(np1);
            if(nhf)
            {
                int now=son[hf[0]];
                for(j=0;j<(int)tree[now].ch.size();++j)
                    tree[np1].ch.pb(tree[now].ch[j]);
            }
            if(nff)
            {
                int np2=++Ncnt;
                tree[np2].kind=0;
                for(j=0;j<nff;++j)
                    tree[np2].ch.pb(son[ff[j]]);
                clear(np2);
                tree[np1].ch.pb(np2);
            }
            if(nhf==2)
            {
                int now=son[hf[1]];
                for(j=(int)tree[now].ch.size()-1;j>=0;--j)
                    tree[np1].ch.pb(tree[now].ch[j]);
            }
            clear(np1);
            tree[u].ch=newson;
        }
    }
    else
    {
        for(j=0;j<(int)tree[u].ch.size();++j)
            if(tree[tree[u].ch[j]].color==1)Goto(tree[u].ch[j]);
    }
    clear(u);
}

int rec[MAX];

void dfs(int u)
{
    if(tree[u].leaf)
    {
        rec[++rec[0]]=tree[u].leaf;
        return;
    }
    for(int j=0;j<(int)tree[u].ch.size();++j)
        dfs(tree[u].ch[j]);
}

void ShowTree(int u)
{
    printf("%d %d %d\n",u,tree[u].kind,tree[u].color);
    for(int j=0;j<(int)tree[u].ch.size();++j)
        printf("%d ",tree[u].ch[j]);
    printf("\n");
    for(int j=0;j<(int)tree[u].ch.size();++j)
        ShowTree(tree[u].ch[j]);
}

void work()
{
    paint(Root);
    Goto(Root);
    return;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#endif
    int i,j;
    scanf("%d",&n);
    m=n;
    initTree();
    for(i=1;i<=m;++i)
        scanf("%s",g[i]+1);
    for(i=1;i<=m;++i)
    {
        nowTest++;
        memset(hash,0,sizeof hash);
        for(j=1;j<=n;++j)
            if(g[i][j]=='1')
                hash[j]=1;
        work();
    }
    dfs(Root);
    printf("YES\n");
    for(i=1;i<=m;++i,printf("\n"))
        for(j=1;j<=n;++j)
            printf("%c",g[i][rec[j]]);
    return 0;
}

