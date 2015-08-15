#include <bits/stdc++.h>
#define MAXN 312345
#define oo1 1100000000
#define MST(a, b) memset(a, b, sizeof(a));
#define MAXNODE 1000000

using namespace std;

struct node
{
	node *l, *r;
	int low, up;
	int num;
} tree[MAXNODE], *root[MAXN];

vector <int> vec;

int A[MAXN], tot;

node *build(int l, int r)
{
	node *tmp = &tree[tot++];
	tmp->low = l, tmp->up = r;
	tmp->num = 0;
	if (l == r) return tmp;
	int mid = l + r >> 1;
	tmp->l = build(l, mid);
	tmp->r = build(mid + 1, r);
	return tmp;
}

node *change(node *pt, int pos, int value)
{
	node *tmp = &tree[tot++];
	tmp->num = pt->num + 1;
	tmp->l = pt->l, tmp->r = pt->r;
	tmp->low = pt->low, tmp->up = pt->up;
	if (tmp->low == tmp->up) return tmp;
	int mid = tmp->low + tmp->up >> 1;
	if (pos <= mid) tmp->l = change(pt->l, pos, value);
	else tmp->r = change(pt->r, pos, value);
	return tmp;
}

int ask(int l, int r, int k)
{
	node *ptl = root[l - 1], *ptr = root[r];
	for (;ptl->low < ptl->up;)
	{
		if (ptr->l->num - ptl->l->num >= k)
		{
			ptr = ptr->l, ptl = ptl->l;
		} else 
		{
			k -= (ptr->l->num - ptl->l->num);
			ptr = ptr->r, ptl = ptl->r;
		}
	}
	return ptl->low;
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

int main()
{
    //  freopen("tmp.in", "r", stdin);
    int T;
    T = getin();
    for (int t = 1; t <= T; ++t)
    {
        printf("Case #%d:\n", t);
        int n, m;
        tot = 0;
        n = getin();
        m = getin();
        vec.clear();
        for (int i = 1; i <= n; ++i)
        {
            A[i] = getin();
            vec.push_back(A[i]);
        }
        sort(vec.begin(), vec.end());
        vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
        root[0] = build(0, vec.size() - 1);
        for (int i = 1; i <= n; ++i)
        {
            int x = lower_bound(vec.begin(), vec.end(), A[i]) - vec.begin();
            root[i] = change(root[i - 1], x, 1);
        }
        for (int i = 1;  i<= m; ++i)
        {
            int L, R, K;
            L = getin();
            R = getin();
            K = getin();
            int l = 1, r = R - L + 1;
            int tmp = vec[ask(L, R, 1)];
            if (tmp >= K)
            {
                printf("%d\n", tmp - K);
                continue;
            }
            for (; l < r; )
            {
                int mid = l + r + 1 >> 1;
                int tmp = vec[ask(L, R, mid)];
                if (tmp > K) r = mid - 1;
                else l = mid;
            }
            int t1 = vec[ask(L, R, l)];
            int ans = abs(t1 - K);
            if (l < R - L + 1)
            {
                t1 = vec[ask(L, R, l + 1)];
                ans = min(ans, abs(t1 - K));
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
