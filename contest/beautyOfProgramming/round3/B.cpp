#include <bits/stdc++.h>
#define MAXN 312345
#define oo1 1100000000
#define MST(a, b) memset(a, b, sizeof(a));

using namespace std;

struct node
{
    int value, size, high, plow, nhigh;
    node *ch[2], *pre;
    int lazy;
} tree[MAXN], *queue[MAXN], *stack[MAXN], *null, *root;
int A[MAXN], top, n, m;

node *new_node(int x)
{
    node *p;
    p = &tree[top++];
    p->value = p->plow = x;
    p->nhigh = -oo1;
    p->size = 1, p->pre = p->ch[0] = p->ch[1] = null;
    p->lazy = 0;
    return p;
}

void updata(node *x)
{
     if (x == null) return;
     x->size = 1;
     x->nhigh = -oo1;
     x->plow = oo1;
     if (x->value >= 0) x->plow = x->value;
     else x->nhigh = x->value;
     
     for (int i = 0; i <= 1; ++i)
         if (x->ch[i] != null)
         {
             x->high = max(x->high, x->ch[i]->high);
             x->low = min(x->low, x->ch[i]->low);
             x->size += x->ch[i]->size;
         }
}

node *buildtree(int l, int r, node *f)
{
     if (l > r) return null;
     int mid = l + r >> 1; node *p = new_node(A[mid]);
     p->ch[0] = buildtree(l, mid - 1, p);
     p->ch[1] = buildtree(mid + 1, r, p);
     p->pre = f; updata(p);
     return p;
}

void rotate(node *x, int p)
{
     node *y = x->pre;
     x->pre = y->pre;
     y->ch[!p] = x->ch[p];
     if (x->ch[p] != null) x->ch[p]->pre = y;
     if (x->pre != null)
        x->pre->ch[x->pre->ch[1] == y] = x;
     y->pre = x;  x->ch[p] = y;
     if (y == root) root = x;
     updata(y); 
}

void splay(node *x, node *f)
{
    for (pushdown(x); x->pre != f;)
        if (x->pre->pre == f)
            rotate(x, x->pre->ch[0] == x);
        else
        {
            node *y = x->pre, *z = y->pre;
            if (z->ch[0] == y)
                if (y->ch[0] == x)
                    rotate(y, 1), rotate(x, 1);
                else rotate(x, 0), rotate(x, 1);
            else 
                if (y->ch[1] == x)
                    rotate(y, 0), rotate(x, 0);
                else rotate(x, 1), rotate(x, 0); 
        }
    updata(x);
}

void select(int k, node *f)
{
     node *now;
     for (now = root;;)
     {
         int mid = now->ch[0]->size;
         if (mid + 1 == k) break;
         if (k <= mid) now = now->ch[0]; 
         else now = now->ch[1], k -= mid + 1; 
     }
     splay(now, f);
}

int getin()
{
    char ch;
    int flag = 0, tmp = 0;
    for (ch = getchar(); ch < 48 || ch > 57; ch = getchar())
        if (ch == int('-')) break;
    if (ch == int('-')) flag = 1; else tmp = int(ch) - 48;
    for (ch = getchar(); 48 <= ch && ch <= 57; ch = getchar())
        tmp = tmp * 10 + int(ch) - 48;
    return (flag) ? -tmp : tmp;
}

void findLMax(int k, int &ans)
{
    int tt = -1;
    node tmp = root->ch[1]->ch[0];
    for (;;)
    {
        if (tmp->value <= k) tt = max(tmp->value, tt);
        
    }
}

void findRMin(int k, int &ans)
{
}

int main()
{
    freopen("B.in", "r", stdin);
    int T;
    T = getin();
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n");
        n = getin();
        m = getin();
        top = 0;
        null = new_node(-oo1);
        null->size = 0;
        root = new_node(-oo1);
        root->ch[1] = new_node(oo1);
        root->ch[1]->pre = root;
        updata(root);
        for (int i = 1; i <= tot; ++i)
            A[i] = getin();
        root->ch[1]->ch[0] = buildtree(1, n, root->ch[1]);
        splay(root->ch[1]->ch[0], null);
        for (int t = 1; t <= m; ++t)
        {
            int L, R, K;
            L = getin();
            R = getin();
            K = getin();
            L++, R++;
            select(L - 1, null);
            select(R + 1, root);

            int ans = oo1;
            findLMax(K, ans);
            findRmin(K, ans);
            splay(root->ch[1], null);
            printf("%d\n", ans);
        } 
    }
    return 0;
}
