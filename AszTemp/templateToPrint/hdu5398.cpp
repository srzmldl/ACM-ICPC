#include <bits/stdc++.h>
//依次加入数字作为点,向其约数连gcd大小的边,维护最大生成树
//这里把边变成点,这样查询点更好做.
const int MAXNODE = 11234567;
const int INF = 11234567;
const int MAXN = 112345;

using namespace std;

long long ANS = 0, ans[MAXN];

struct node {
	bool rev;
	int minVal, val;
	node *f, *son[2], *minPos;
} g[MAXNODE], *null, *tree[MAXN];

int cnt = 0;

node* newNode(int x) {
	node *tmp = &g[cnt++];
	tmp->f = tmp->son[0] = tmp->son[1] = null;
	tmp->minVal = tmp->val = x;
	tmp->minPos = tmp;
	return tmp;
}

void origin() {
    null = &g[cnt++];
    null->f = null->son[0] = null->son[1] = null;
    null->val = null->minVal = INF;
    null->minPos = null;
    null->rev = false;
}

void makeRev(node *x) {
    if (x == null) return ;
    swap(x->son[0], x->son[1]);
    x->rev = !x->rev;
}

void update(node *x) {
	if (x == null) return ;
	x->minVal = x->val;
	x->minPos = x;
	for (int k = 0; k <= 1; ++k)
		if (x->son[k]->minVal < x->minVal) {
			x->minVal = x->son[k]->minVal;
			x->minPos = x->son[k]->minPos;
	}
}

void pushDown(node *x) {
	if (x == null) return ;
	if (x->rev) {
		makeRev(x->son[0]);
		makeRev(x->son[1]);
		x->rev = false;
	}
}

bool ifRoot(node *x) {
	if (x->f == null) return true;
	return (x->f->son[0] != x) && (x->f->son[1] != x);
}

void rotate(node *x, node *y, int p) {
	node *z = y->f;
	x->f = z;
	if (!ifRoot(y)) z->son[z->son[1] == y] = x;
	y->son[p] = x->son[1 - p];
	x->son[1 - p] = y;
	if (y->son[p] != null)
		y->son[p]->f = y;
	if (x->son[1-p] != null)
		x->son[1 - p]->f = x;
	update(y);
	//update(x);
	//update(z);
}

void pushDownAll(node *x) {
    if (!ifRoot(x)) pushDownAll(x->f);
    pushDown(x);
}

void splay(node *x) {
	if (x == null) return ;
	pushDownAll(x);
	for (;!ifRoot(x);) {
		node *y = x->f, *z = y->f;
		int p = (y->son[1] == x);
		int q = (z->son[1] == y);
		if (ifRoot(y)) rotate(x, y, p);
		else if (p == q) rotate(y, z, p), rotate(x, y, p);
		else rotate(x, y, p), rotate(x, z, q);
	}
    update(x);
}

node *access(node *u) {
	node *v = null;
	for (;u != null; u = u->f) {
		splay(u);
		u->son[1] = v;
		v = u;
		update(u);
	}
	return v;
}

void evert(node *x) { //换根
	node *tmp = access(x);
	makeRev(tmp);
	splay(x);
}

node *getRoot(node *x) {
	access(x);
	splay(x);
	node *tmp = x;
	for (; tmp->son[0] != null; tmp = tmp->son[0])
		pushDown(tmp);
	return tmp;
}

void link(node *const x, node *const y) {
	if (getRoot(x) == getRoot(y)) return ;
	evert(x);
	x->f = y;
	access(x);
}

void cut(node *x, node *y) { //切断x到y的路径,从y相连的第一个点断开
	if ((x == y) || (getRoot(x) != getRoot(y))) return ;
	evert(x);
	access(y);
	splay(y);
	y->son[0]->f = null;
	y->son[0] = null;
	update(y);
}

void addEdge(int u, int v, int val) {
    node *x = tree[u];
    node *y = tree[v];
    node *rx = getRoot(x);
    node *ry = getRoot(y);
    if (rx == ry) {
		evert(x);
        node *tmp = access(y);
        
        node *delNode = tmp->minPos;
        if (delNode->val >= val) return ;
		ANS -= 1LL * delNode->minVal;
        cut(x, delNode);
        cut(y, delNode);
    }
	node *mid = newNode(val);
	ANS += 1LL * val;
	link(x, mid);
	link(mid, y);
}

int main() {
	origin();
    for (int i = 1; i <= 100000; ++i) {
        tree[i] = newNode(INF);
		if (i == 1) continue;
		for (int j = 1; 1LL * j * j <= i; ++j)
        if (i % j == 0) {
            addEdge(i, j, j);
            if (j * j < i) addEdge(i, i/j, i/j);
        }
        ans[i] = ANS;
    }
	int n;
    for (; scanf("%d", &n) != EOF; ) {
		cout << ans[n] << endl;
    }
	return 0;
}
