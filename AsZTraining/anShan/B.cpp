#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#include 
#define REP(i, n) for (int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int)(b); ++i)
#define LL long long
#define MAXN 6000

using namespace std;
struct node
{
    int u, w;
    node(int u = 0, int w = 0) :u(u), w(w) {};
}g[MAXN];
int cnt, top;
string st;

void origin()
{
    cnt = 0;
    top = -1;
}

int Find(int u)
{
    int p = -1;
    REPP(i, 1, cnt)
        if (g[i].u == u)
        {
            p = i;
            break;
        }
    return p;
}

void Add(int lab)  
{
    int u;
    scanf("%d", &u);
    int p = Find(u);
    printf("Operation #%d: ", lab);
    if (p != -1)
    {
        printf("same priority.\n");
    } else
    {
        ++cnt;
        g[cnt] = node(u, 0);
        printf("success.\n");
    }
}

void Close(int lab)
{
    int u;
    scanf("%d", &u);
    int p = Find(u);
    printf("Operation #%d: ", lab);
    if (p == -1)
    {
        printf("invalid priority.\n");
    } else
    {
        printf("close %d with %d.\n", g[p].u, g[p].w);
        if (u == top) top = -1;
        REPP(i, p, cnt - 1) g[i] = g[i +1];
        cnt--;
    }
}

void Chat(int lab)
{
    int w;
    scanf("%d", &w);
    printf("Operation #%d: ", lab);
    if (cnt == 0)
    {
        printf("empty.\n");
    } else
    {
        int p;
        if (top > 0) p = Find(top);
        else p = 1;
        g[p].w += w;
        printf("success.\n");
    }
}

void Rotate(int lab)
{
    int x;
    scanf("%d", &x);
    printf("Operation #%d: ", lab);
    if (x > cnt)
    {
        printf("out of range.\n");
    } else
    {
        node tmp = g[x];
        for (int i = x; i >= 2; --i)
            g[i] = g[i - 1];
        g[1] = tmp;
        printf("success.\n");
    }
}

int findMax()
{
    int p = 1;
    REPP(i, 2, cnt)
        if (g[i].u >g[p].u)
            p = i;
    return p;
}

void Prior(int lab)
{
    printf("Operation #%d: ", lab);
    if (cnt == 0)
    {
        printf("empty.\n");
    } else
    {
        int p = findMax();
        node tmp = g[p];
        for (int i = p; i >= 2; --i)
            g[i] = g[i - 1];
        g[1] = tmp;
        printf("success.\n");
    }
}

void Choose(int lab)
{
    int u;
    scanf("%d", &u);
    int p = Find(u);
    printf("Operation #%d: ", lab);
    if (p == -1)
    {
        printf("invalid priority.\n");
    } else
    {
        node tmp = g[p];
        for (int i = p; i >= 2; --i)
            g[i] = g[i - 1];
        g[1] = tmp;
        printf("success.\n");
    }
}

void Top(int lab)
{
    int u;
    scanf("%d", &u);
    int p = Find(u);
    printf("Operation #%d: ", lab);
    if (p == -1)
    {
        printf("invalid priority.\n");
    } else
    {
        printf("success.\n");
        top = u;
    }
}

void Untop(int lab)
{
    printf("Operation #%d: ", lab);
    if (top == -1)
    {
        printf("no such person.\n");
    } else
    {
        top = -1;
        printf("success.\n");
    }
}

int main() {
    //freopen("B.txt", "r", stdin);
    int task;
    for (scanf("%d", &task); task; --task)
    {
        int n;
        scanf("%d", &n);
        origin();
        REPP(i, 1, n)
        {
            cin >> st;
            //scanf("%s", st);
            if (st == "Add") Add(i);
            else if (st == "Close") Close(i);
            else if (st == "Chat") Chat(i);
            else if (st == "Rotate") Rotate(i);
            else if (st == "Prior") Prior(i);
            else if (st == "Choose") Choose(i);
            else if (st == "Top") Top(i);
            else Untop(i);
        }

        if (top >= 0)
        {
            int p = Find(top);
            if (g[p].w > 0)
                printf("Bye %d: %d\n", g[p].u, g[p].w);
            REPP(i, p, cnt) g[i] = g[i + 1];
            --cnt;
        }

        REPP(i, 1, cnt)
            if (g[i].w > 0)
            {
                printf("Bye %d: %d\n", g[i].u, g[i].w);
            }
    }
    return 0;
}

