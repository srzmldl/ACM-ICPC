#include <bits/stdc++.h>

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

#define SI 1000100

using namespace std;

int a[SI], f[2][SI];
int a1[SI * 6], a2[SI * 6], p1[SI * 6], p2[SI * 6];

struct Node
{
	int l, r, k;
	Node(int l = 0, int r = 0, int k = 0) : l(l), r(r), k(k) {}
};

void build(int l, int r, int now)
{
	if (l == r)
	{
		a1[now] = a2[now] = a[l];
		p1[now] = p2[now] = l;
		return;
	}
	int mid = (l + r) / 2;
	int g = now * 2, h = g + 1;
	if (l <= mid)
		build(l, mid, g);
	if (mid < r)
		build(mid + 1, r, h);
	if (a1[g] <= a1[h])
	{
		a1[now] = a1[g];
		p1[now] = p1[g];
	} else
	{
		a1[now] = a1[h];
		p1[now] = p1[h];
    }
    if (a2[g] > a2[h])
    {
		a2[now] = a2[g];
		p2[now] = p2[g];
    } else
    {
		a2[now] = a2[h];
		p2[now] = p2[h];
    }
}

int ask(int l, int r, int now, int s, int t, int k)
{
	if (s <= l && r <= t)
		return k ? p2[now] : p1[now];
	int mid = (l + r) / 2;
	int g = -1, h = -1;
	if (s <= mid)
		g = ask(l, mid, now * 2, s, t, k);
	if (mid < t)
		h = ask(mid + 1, r, now * 2 + 1, s, t, k);
	if (g == -1)
		return h;
	if (h == -1)
		return g;
	if (k == 0)
	{
		if (a[g] == a[h])
			return g;
		return a[g] < a[h] ? g : h;
	} else
	{
		if (a[g] == a[h])
			return h;
		return a[g] > a[h] ? g : h;
	}
}

int main() {
	ios :: sync_with_stdio(0);

	int ttt;
	scanf("%d", &ttt);
	while (ttt--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, n, 1);
//		for (int i = 1; i < 20; i++)
//			printf("%d%c", a1[i], " \n"[i == 19]);
//		for (int i = 1; i < 20; i++)
//			printf("%d%c", p1[i], " \n"[i == 19]);
		queue<Node> q;
		q.push(Node(1, n, 0));
		while (q.size())
		{
			Node now = q.front();
			q.pop();
			int l = now.l, r = now.r, k = now.k;
//			printf("%d %d\n", l, r);
			int pos = ask(1, n, 1, l, r, 0);
//			printf("%d %d %d\n", l, r, pos);
			f[0][pos] = k;
			if (l < pos)
				q.push(Node(l, pos - 1, k));
			if (pos < r)
				q.push(Node(pos + 1, r, k + 1));
		}
		q.push(Node(1, n, 0));
		while (q.size())
		{
			Node now = q.front();
			q.pop();
			int l = now.l, r = now.r, k = now.k;
			int pos = ask(1, n, 1, l, r, 1);
//			printf("%d %d %d\n", l, r, pos);
			f[1][pos] = k;
			if (l < pos)
				q.push(Node(l, pos - 1, k + 1));
			if (pos < r)
				q.push(Node(pos + 1, r, k));
		}
		int ans = n;
		for (int i = 1; i <= n; i++)
			ans = min(ans, f[0][i] + 1 + f[1][i]);
		cout << ans << endl;
	}

	return 0;
}
