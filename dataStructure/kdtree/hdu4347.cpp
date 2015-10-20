#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MAXN = 50010;
const int DIM = 10;
inline double sqr(double x){return x*x;}
namespace KDTree{
	int K;//维数
	struct Point{
		int x[DIM];
		double distance(const Point &b)const{
			double ret = 0;
			for(int i = 0;i < K;i++)
				ret += sqr(x[i]-b.x[i]);
			return ret;
		}
		void input(){
			for(int i = 0;i < K;i++)scanf("%d",&x[i]);
		}
		void output(){
			for(int i = 0;i < K;i++)
				printf("%d%c",x[i],i < K-1?' ':'\n');
		}
	};
	struct qnode{
		Point p;
		double dis;
		qnode(){}
		qnode(Point _p,double _dis){
			p = _p; dis = _dis;
		}
		bool operator <(const qnode &b)const{
			return dis < b.dis;
		}
	};
	priority_queue<qnode>q;
	struct cmpx{
		int div;
		cmpx(const int &_div){div = _div;}
		bool operator()(const Point &a,const Point &b){
			for(int i = 0;i < K;i++)
				if(a.x[(div+i)%K] != b.x[(div+i)%K])
					return a.x[(div+i)%K] < b.x[(div+i)%K];
			return true;
		}
	};
	bool cmp(const Point &a,const Point &b,int div){
		cmpx cp = cmpx(div);
		return cp(a,b);
	}
	struct Node{
		Point e;
		Node *lc,*rc;
		int div;
	}pool[MAXN],*tail,*root;
	void init(){
		tail = pool;
	}
	Node* build(Point *a,int l,int r,int div){
		if(l >= r)return NULL;
		Node *p = tail++;
		p->div = div;
		int mid = (l+r)/2;
		nth_element(a+l,a+mid,a+r,cmpx(div));
		p->e = a[mid];
		p->lc = build(a,l,mid,(div+1)%K);
		p->rc = build(a,mid+1,r,(div+1)%K);
		return p;
	}
	void search(Point p,Node *x,int div,int m){
		if(!x)return;
		if(cmp(p,x->e,div)){
			search(p,x->lc,(div+1)%K,m);
			if(q.size() < m){
				q.push(qnode(x->e,p.distance(x->e)));
				search(p,x->rc,(div+1)%K,m);
			}
			else {
				if(p.distance(x->e) < q.top().dis){
					q.pop(); 
					q.push(qnode(x->e,p.distance(x->e)));
				}
				if(sqr(x->e.x[div]-p.x[div]) < q.top().dis)
					search(p,x->rc,(div+1)%K,m);
			}
		}
		else {
			search(p,x->rc,(div+1)%K,m);
			if(q.size() < m){
				q.push(qnode(x->e,p.distance(x->e)));
				search(p,x->lc,(div+1)%K,m);
			}
			else {
				if(p.distance(x->e) < q.top().dis){
					q.pop();
					q.push(qnode(x->e,p.distance(x->e)));
				}
				if(sqr(x->e.x[div]-p.x[div]) < q.top().dis)
					search(p,x->lc,(div+1)%K,m);
			}
		}
	}
	void search(Point p,int m){
		while(!q.empty())q.pop();
		search(p,root,0,m);
	}
};
KDTree::Point p[MAXN];
int main()
{
	int n,k;
	while(scanf("%d%d",&n,&k) == 2){
		KDTree::K = k;
		for(int i = 0;i < n;i++)p[i].input();
		KDTree::init();
		KDTree::root = KDTree::build(p,0,n,0);
		int Q;
		scanf("%d",&Q);
		KDTree::Point o;
		while(Q--){
			o.input();
			int m;
			scanf("%d",&m);
			KDTree::search(o,m);
			printf("the closest %d points are:\n",m);
			int cnt = 0;
			while(!KDTree::q.empty()){
				p[cnt++] = KDTree::q.top().p;
				KDTree::q.pop();
			}
			for(int i = 0;i < m;i++)p[m-1-i].output();
		}
	}
	return 0;
}