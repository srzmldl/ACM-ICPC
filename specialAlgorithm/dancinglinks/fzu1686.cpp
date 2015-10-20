#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MaxM = 15*15+10;
const int MaxN = 15*15+10;
const int maxnode = MaxN * MaxM;
const int INF = 0x3f3f3f3f;
struct DLX
{
    int n,m,size;
    int
    U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN],S[MaxM];
    int ansd;
    void init(int _n,int _m) {
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++) {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)H[i] = -1;
    }
    void Link(int r,int c) {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    void remove(int c) {
        for(int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c) {
        for(int i = U[c];i != c;i = U[i])
            L[R[i]] = R[L[i]] = i;
    }
    bool v[MaxM];
    int f() {
        int ret = 0;
        for(int c = R[0]; c != 0;c = R[c])v[c] = true;
        for(int c = R[0]; c != 0;c = R[c])
            if(v[c]) {
                ret++;
                v[c] = false;
                for(int i = D[c];i != c;i = D[i])
                    for(int j = R[i];j != i;j = R[j])
                        v[Col[j]] = false;
            }
        return ret;
    }
    void Dance(int d) {
        if(d + f() >= ansd)return;
        if(R[0] == 0) {
            if(d < ansd)ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i]) {
            remove(i);
            for(int j = R[i];j != i;j = R[j])remove(j);
            Dance(d+1);
            for(int j = L[i];j != i;j = L[j])resume(j);
            resume(i);
        }
    }
};
DLX g;
int a[20][20];
int id[20][20];
int main() {
    int n,m;
    while(scanf("%d%d",&n,&m) == 2) {
        int sz = 0;
        memset(id,0,sizeof(id));
        for(int i = 0;i < n;i++)
            for(int j = 0;j < m;j++) {
                scanf("%d",&a[i][j]);
                if(a[i][j] == 1)id[i][j] = (++sz);
            }
        g.init(n*m,sz);
        sz = 1;
        int n1,m1;
        scanf("%d%d",&n1,&m1);
        for(int i = 0;i < n;i++)
            for(int j = 0;j < m;j++) {
                for(int x = 0;x < n1 && i + x < n;x++)
                    for(int y = 0;y < m1 && j + y < m;y++)
                        if(id[i+x][j+y])
                            g.Link(sz,id[i+x][j+y]);
                sz++;
            }
        g.ansd = INF;
        g.Dance(0);
        printf("%d\n",g.ansd);
    }
    return 0;
}