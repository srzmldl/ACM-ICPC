#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<stack>
 
#define LL long long
 
using namespace std;
const int N=100;
const long long MOD = 1000000007;
int a[N];
long long dp[N][N];
long long c[N][N];
long long d[N];
 
int main()
{
    freopen("A.in","r",stdin);
    for(int i=0;i<N;++i)
        for(int j=0;j<=i;++j)
        {
            if(j==0||i==j) c[i][j]=1;
            else c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
        }
    d[0]=1;
    for(int i=1;i<N;++i)
        d[i]=(d[i-1]*i)%MOD;
    int T;
    cin>>T;
    for(int w=1;w<=T;++w)
    {
        int n = 13;
        int nn;
        cin>>nn;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= nn; ++i)
        {
            string st;
            cin >> st;
            if (st[0] >= '2' && st[0] <= '9')
                a[st[0] - '0']++;
            else if (st[0] == 'T')
                a[1]++;
            else if (st[0] == 'J')
                a[10]++;
            else if (st[0] == 'Q')
                a[11]++;
            else if (st[0] == 'K')
                a[12]++;
            else a[0]++;
        }
        sort(a + 0, a + 13);
        memset(dp,0,sizeof(dp));
        dp[0][a[0]-1]=d[a[0]];
        int sum=a[0];
        for(int i=0;i<n-1;++i)
        {
            for(int j=0;j<sum;++j)
                {
                    if(dp[i][j]>0)
                    {
                        for(int l=0;l<=j&&l<=a[i+1];++l)
                        {
                            for(int r=0;r<=(sum+1-j)&&l+r<=a[i+1];++r)
                            {
                                if(l+r==0) continue;
                                int J=(j-l)+(a[i+1]-l-r);
                                //dp[i+1][J]=(dp[i+1][J]+(dp[i][j]*(c[j][l]*(c[sum+1-j][r]*(d[a[i+1]]*c[a[i+1]-1][l+r-1])%MOD)%MOD)%MOD)%MOD)%MOD;
                                dp[i+1][J]=(((((c[a[i+1]-1][l+r-1]*d[a[i+1]])%MOD*c[sum+1-j][r])%MOD*c[j][l])%MOD*dp[i][j])%MOD+dp[i+1][J])%MOD;
                            }
                        }
                    }
                }
                sum+=a[i+1];
            }
            printf("Case %d: ",w);
            cout<<dp[n-1][0]<<endl;
        }
    return 0;
}
