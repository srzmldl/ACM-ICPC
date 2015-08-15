#include <bits/stdc++.h>

#define L (x << 1)
#define R (x << 1 | 1)
#define MID ((l + r) >> 1)
#define LC L, l, MID
#define RC R, MID + 1, r

#define REP(i, a) for (int i = 0; i < (int) (a); i ++)
#define REPP(i, a, b) for (int i = (int) (a); i <= (int) (b); i ++)
#define MST(a, b) memset(a, b, sizeof(a))

using namespace std;

const int N = 200005;
const int INF = 2e9;

int mi[N << 2], mx[N << 2], val[N << 2], a[N], add[N << 2];
int ql, qr, qd;
bool fl[N << 2];

void maintain(int x, int l, int r) {
	mi[x] = min(mi[L], mi[R]);
	mx[x] = max(mx[L], mx[R]);
	fl[x] = (fl[L] && fl[R] && val[L] == val[R]);
	val[x] = fl[x] ? val[L] : 0;
}

void build(int x, int l, int r) {
	if (l == r) {
		mi[x] = mx[x] = a[l];
		fl[x] = 1, add[x] = 0;
		val[x] = a[l];
	}
	else {
		build(LC), build(RC);
		maintain(x, l, r);
	}
}

void push(int x, int l, int r) {
	fl[L] = fl[R] = fl[x];
	mi[L] = mx[L] = val[x];
	mi[R] = mx[R] = val[x];
	val[L] = val[R] = val[x];
	add[L] = add[R] = 0;
	fl[x] = val[x] = add[x] = 0;
}

void pushadd(int x, int l, int r) {
	add[L] += add[x], add[R] += add[x];
	mi[L] += add[x], mx[L] += add[x];
	mi[R] += add[x], mx[R] += add[x];
	if (fl[L]) val[L] += add[x];
	if (fl[R]) val[R] += add[x];
	add[x] = 0;
}

void update1(int x, int l, int r) {
	if (ql <= l && qr >= r) {
		if (fl[x]) {
			mi[x] = mx[x] = min(mi[x], qd);
			fl[x] = 1;
			val[x] = mi[x];
			add[x] = 0;
		}
		else {
			if (fl[x]) push(x, l, r);
			else if (add[x]) pushadd(x, l, r);
			update1(LC), update1(RC);
			maintain(x, l, r);
		}
	}
	else {
		if (fl[x]) push(x, l, r);
		else if (add[x]) pushadd(x, l, r);
		if (ql <= MID) {
			update1(LC);
		}
		if (qr > MID) {
			update1(RC);
		}
		maintain(x, l, r);
	}
}

void update2(int x, int l, int r) {
	if (ql <= l && qr >= r) {
		if (fl[x]) {
			mi[x] = mx[x] = max(mi[x], qd);
			val[x] = mx[x];
			fl[x] = 1;
			add[x] = 0;
		}
		else {
			if (fl[x]) push(x, l, r);
			else if (add[x]) pushadd(x, l, r);
			update2(LC), update2(RC);
			maintain(x, l, r);
		}
	}
	else {
		if (fl[x]) push(x, l, r);
		else if (add[x]) pushadd(x, l, r);
		if (ql <= MID) {
			update2(LC);
		}
		if (qr > MID) {
			update2(RC);
		}
		maintain(x, l, r);
	}
}

int ansp, ansq;

void query(int x, int l, int r) {
	if (ql <= l && qr >= r) {
		ansp = min(ansp, mi[x]);
		ansq = max(ansq, mx[x]);
	}
	else {
		if (fl[x]) push(x, l, r);
		else if (add[x]) pushadd(x, l, r);
		if (ql <= MID) query(LC);
		if (qr > MID) query(RC);
	}
}

void modify(int x, int l, int r) {
	if (ql <= l && qr >= r) {
		add[x] += qd;
		mi[x] += qd, mx[x] += qd;
		if (fl[x]) val[x] += qd;
	}
	else {
		if (fl[x]) push(x, l, r);
		else if (add[x]) pushadd(x, l, r);
		if (ql <= MID) modify(LC);
		if (qr > MID) modify(RC);
		maintain(x, l, r);
	}
}

int get() {
	char c;
	while (c = getchar(), (c < '0' || c > '9') && (c != '-'));
	bool flag = (c == '-');
	if (flag) c = getchar();
	int x = 0;
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - 48;
		c = getchar();
	}
	return flag ? -x : x;
}

int bit[10];

void output(int x) {
	if (x < 0) putchar('-'), x = -x;
	int len = 0;
	while (x) {
		bit[len++] = x % 10; 
		x /= 10;
	}
	if (!len) bit[len++] = 0;
	while (len--) putchar(bit[len] + 48);
}

int main() {
	int n, m, ty;
	//freopen("tmp.in", "r", stdin);
	n = get(), m = get();
	REPP(i, 1, n) {
		a[i] = get();
	}
	build(1, 1, n);
	while (m--) {
		ty = get();
		ql = get(), qr = get();
		if (ty == 1) {
			qd = get();
			modify(1, 1, n);
		}
		else if (ty == 2) {
			qd = get();
			update1(1, 1, n);
		}
		else if (ty == 3) {
			qd = get();
			update2(1, 1, n);
		}
		else {
			ansp = INF, ansq = -INF;
			query(1, 1, n);
			output(ansp), putchar(' '), output(ansq);
			putchar('\n');
		}
	}

	return 0;
}
