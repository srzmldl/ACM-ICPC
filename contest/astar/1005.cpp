#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100005;
const int inf = 0x3fffffff;

int A[maxn],lis[maxn],pos[maxn],top;

int main()
{
    int N;  scanf("%d",&N);
    for(int i = 1;i <= N;i ++)  scanf("%d",A + i);
    lis[0] = -inf;
    for(int i = 1;i <= N;i ++)
    {
        if(A[i] > lis[top] && A[i] - lis[top] >= i - pos[top])
            lis[++ top] = A[i],pos[top] = i;
        else
        {
            int l = 0,r = top,k = -1;
            while(l <= r)
            {
                int mid = l + r >> 1;
                if(A[i] - lis[mid] >= i - pos[mid])
                    l = mid + 1,k = mid;
                else
                    r = mid - 1;
            }
            if(~k)  lis[k + 1] = A[i],pos[k + 1] = i;
        }
    }
    printf("%d\n",N - top);
    return 0;
}
