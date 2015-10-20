#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
#define maxn 2000007
#define inf  1000000000
#define ll long long

struct Node{
    Node *fa,*ch[2];
    bool rev,root;
    int val,minv;
};
Node pool[maxn];
Node *nil,*tree[maxn];
int cnt = 0;
void init(){
    cnt = 1;
    nil = tree[0] = pool;
    nil->ch[0] = nil->ch[1] = nil;
    nil->val = inf;
    nil->minv = inf;
}
Node *newnode(int val,Node *f){
    pool[cnt].fa = f;
    pool[cnt].ch[0]=pool[cnt].ch[1]=nil;
    pool[cnt].rev = false;
    pool[cnt].root = true;
    pool[cnt].val = val;
    pool[cnt].minv = val;
    return &pool[cnt++];
}

//左右子树反转******真正把结点变为根
void update_rev(Node *x){
    if(x == nil) return ;
    x->rev = !x->rev;
    swap(x->ch[0],x->ch[1]);
}
//splay向上更新信息******
void update(Node *x){
    if(x == nil) return ;
    x->minv = x->val;
    if(x->ch[0] != nil)
        x->minv = min(x->minv,x->ch[0]->minv);
    if(x->ch[1] != nil)
        x->minv = min(x->minv,x->ch[1]->minv);
}

//splay下推信息******
void pushdown(Node *x){
    if(x->rev != false){
        update_rev(x->ch[0]);
        update_rev(x->ch[1]);
        x->rev = false;
    }
}
//splay在root-->x的路径下推信息******
void push(Node *x){
    if(!x->root) push(x->fa);
    pushdown(x);
}
//将结点x旋转至splay中父亲的位置******
void rotate(Node *x){
    Node *f = x->fa, *ff = f->fa;
    int t = (f->ch[1] == x);
    if(f->root)
        x->root = true, f->root = false;
    else ff->ch[ff->ch[1] == f] = x;
    x->fa = ff;
    f->ch[t] = x->ch[t^1];
    x->ch[t^1]->fa = f;
    x->ch[t^1] = f;
    f->fa = x;
    update(f);
}
//将结点x旋转至x所在splay的根位置******
void splay(Node *x){
    push(x);
    Node *f, *ff;
    while(!x->root){
        f = x->fa,ff = f->fa;
        if(!f->root)
            if((ff->ch[1]==f)&&(f->ch[1] == x)) rotate(f);
            else rotate(x);
        rotate(x);
    }
    update(x);
}
//将x到树根的路径并成一条path******
Node *access(Node *x){
    Node *y = nil,*z;
    while(x != nil){
        splay(x);
        x->ch[1]->root = true;
        (x->ch[1] = y)->root = false;
        update(x);
        y = x;
        x = x->fa;
    }
    return y;
}
//将结点x变成树根******
void be_root(Node *x){
    access(x);
    splay(x);
    update_rev(x);
}
ll ans[maxn];
//将x连接到结点f上******
void link(Node *x, Node *f){
    be_root(x);
    x->fa = f;
    access(x);
}
//将x,y分离******
void cut(Node *x,Node *y){
    be_root(x);
    access(x);
    splay(y);
    y->fa = nil;
}
Node * find_fa(Node *root){
    if(root->ch[0] == nil) return root;
    return find_fa(root->ch[0]);
}
Node * find_min(Node * root,int val){
    if(root->val == val) return root;
    if(root->ch[0]->minv == val)
        return find_min(root->ch[0],val);
    return find_min(root->ch[1],val);
}
//处理u到v是否连边
int work(int u,int v){
    Node *x,*y,*z;
    be_root(tree[u]);
    y = access(tree[v]);
    x = find_fa(y);
    int res = 0;
    if(x == tree[u]){
        if(y->minv >= v) return 0;
        y = find_min(y,y->minv);
        cut(y,tree[u]);
        cut(y,tree[v]);
        res -= y->val;
    }
    y = newnode(v,nil);
    link(tree[u],y);
    link(tree[v],y);
    return res+v;
}
int main(){
    memset(ans,0,sizeof(ans));
    init();
    int u,v;
    for(int i = 1;i <= 100000;i++){
        ans[i] = ans[i-1];
        tree[i] = newnode(inf,nil);
        for(int j = 1;j * j <= i && j < i; j++){
            if(i%j != 0) continue;
            ans[i]+=work(i,j);
            if(i/j != j) ans[i]+=work(i,i/j);
        }
    }
//    freopen("in.txt","r",stdin);
//    freopen("outx.txt","w",stdout);
    int n;
    while(scanf("%d",&n)!=EOF)
        printf("%I64d\n",ans[n]);
    return 0;
}
