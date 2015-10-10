#include <bits/stdc++.h>
#define MAXN 101010
#define LIM 29

using namespace std;

typedef int arrayN[MAXN];

arrayN fir, nxt;
int base, now, num;

struct node
{
    int l, r;
    int val;
} g[MAXN];

struct segment
{
    segment *ch[2];
    int cnt;

    segment *makeNew()
    {
        segment *tmp = new segment;
        tmp->ch[0] = tmp->ch[1] = NULL;
        tmp->cnt = 0;
        return tmp;
    }
    void del(int x)
    {
        int wq = 1 << LIM;
        segment *pt = this;
        for (int i = 0; i <= LIM; ++i)
        {
            int nx = 0;
            if (x & wq) nx = 1;
            if (pt->ch[nx] == NULL) return ;
            pt = pt->ch[nx];
            wq >>= 1;
        }

        
        wq = 1 << LIM;
        pt = this;
        pt->cnt--;
        segment *last = NULL;
        for (int i = 0; i <= LIM; ++i)
        {
            int nx = 0;
            if (x & wq) nx = 1;
            last = pt;
            pt = pt->ch[nx];
            pt->cnt--;
            if (pt->cnt == 0)
            {
                last->ch[nx] = NULL;
                if (i && last->cnt == 0)
                    free(last);
            }
            wq >>= 1;
        }
    }
    
    void add(int x)
    {
        int wq = 1 << LIM;
        segment *pt = this;
        pt->cnt++;
        for (int i = 0; i <= LIM; ++i)
        {
            int nx = 0;
            if (x & wq) nx = 1;
            if (!pt->ch[nx]) pt->ch[nx] = makeNew();
            
            pt = pt->ch[nx];
            pt->cnt++;
            wq >>= 1;
        }
    }
    
    int ask(int x)
    {
        int tmp = 0;
        segment *pt = this;
        int wq = 1 << LIM;
        if (pt->cnt)
        for (int i = 0; i <= LIM; ++i)
        {
            int nx = 0;
            if (x & wq) nx = 1;
            if (pt->ch[1 - nx] && pt->ch[1 - nx]->cnt)
            {
                pt = pt->ch[1 - nx];
                tmp |= wq;
            } else pt = pt->ch[nx];
            wq >>= 1;
        }
        return tmp;
    }
} seg[MAXN * 3];

void getdfs(int x)
{
    g[x].l = ++now;
    for (int p = fir[x]; p; p = nxt[p])
        getdfs(p);
    g[x].r = now;
}

int ask(int u)
{
    int pos = g[u].l + base;
    int ans = 0;
    for (; pos; pos >>= 1)
        ans = max(ans, seg[pos].ask(g[u].val));
    return ans;
}

void change(int u, int v)
{
    int l = g[u].l + base - 1, r = g[u].r + base + 1;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) seg[l + 1].del(g[u].val);
        if (r & 1) seg[r - 1].del(g[u].val);
    }
    l = g[u].l + base - 1, r = g[u].r + base + 1;
    g[u].val = v;
    for (; (l ^ r) != 1; l >>= 1, r >>= 1)
    {
        if (!(l & 1)) seg[l + 1].add(g[u].val);
        if (r & 1) seg[r - 1].add(g[u].val);
    }
}

void link(int u, int v)
{
    nxt[v] = fir[u];
    fir[u] = v;
}


int main()
{
    // freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int T;
    //srand(clock() % time(0));
    for (scanf("%d", &T); T; --T)
    //  for (int T = 1; T <= 3; ++T)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        //   n = 100000;
        //m = 100000;
        num = 0;
        memset(fir, 0, sizeof(fir));
        memset(g, 0, sizeof(g));
        for (int i = 2; i <= n; ++i)
        {
            int fa;
            scanf("%d", &fa);
            // fa = rand() % (i - 1) + 1;
            link(fa, i);
        }
        now = 0;
        getdfs(1);
        for (base = 1; base <= n; base <<= 1);
        for (int i = base + n; i >= 1; --i)
        {
            seg[i].ch[0] = seg[i].ch[1] = NULL;
            seg[i].cnt = 0;
        }
        for (int i = 1; i <= n; ++i)
        {
            int v;
            scanf("%d", &v);
            //v = abs(rand() * rand() * rand()) % 1000000000;
            g[i].val = v;
            int l = g[i].l + base - 1, r = g[i].r + base + 1;
            for (; (l ^ r) != 1; l >>= 1, r >>= 1)
            {
                if (!(l & 1))
                seg[l + 1].add(v);
                if (r & 1) seg[r - 1].add(v);
            }
        }
        int i;
        
        for (int i = 1; i <= m; ++i)
        {
            int k, u, v;
            scanf("%d%d", &k, &u);
            //k = rand() % 2;
            //u = rand() % n + 1;
            //v =  abs(rand() * rand() * rand()) % 1000000000;
            if (k == 0)
            {
                scanf("%d", &v);
                change(u, v);
            } else
            {
                //cout << ask(u) << endl;
                printf("%d\n", ask(u));
            }
        }
    }
    return 0;
}
