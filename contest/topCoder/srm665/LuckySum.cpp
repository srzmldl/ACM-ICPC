// BEGIN CUT HERE

// END CUT HERE
#line 5 "LuckySum.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;

#define PB push_back
#define MP make_pair

#define REP(i,n) for(i=0;i<(n);++i)
#define FOR(i,l,h) for(i=(l);i<=(h);++i)
#define FORD(i,h,l) for(i=(h);i>=(l);--i)

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;


int a[20], vis[20], n;
long long pw[16];

const long long oo = (long long) 1e17;
long long ans = oo;


void dfs(int lelen, int rilen, int ps, int jw, long long tmp) // lelen long, rilen short
{
    if (tmp >= ans) return ;
    if (ps == n) 
    {
        if (jw) return ;
        ans = tmp;
        return ;
    }
    if (lelen == 0)
    {
        if (!jw) return ;
        if (a[ps] == 1 || a[ps] == -1)
            dfs(lelen, rilen, ps + 1, 0, tmp + pw[ps]);
        return ;
    } else
    {
        if (rilen == 0)
        {
            int x = 4 + jw;
            if (a[ps] == x || a[ps] == -1)
                dfs(lelen - 1, rilen, ps + 1, 0, tmp + 1LL * x * pw[ps]);
            x = 7 + jw;
            if (a[ps] == x || a[ps] == -1)
                dfs(lelen - 1, rilen, ps + 1, 0, tmp + 1LL * x * pw[ps]);
            return ;
        } else
        {
            if (a[ps] == -1 || a[ps] == 8 + jw)
                dfs(lelen - 1, rilen - 1, ps + 1, 0, tmp + (8LL + jw) * pw[ps]);
            if (a[ps] == -1 || a[ps] == 1 + jw)
                dfs(lelen - 1, rilen - 1, ps + 1, 1, tmp + (1LL + jw) * pw[ps]);
            if (a[ps] == -1 || a[ps] == 4 + jw)
                dfs(lelen - 1, rilen - 1, ps + 1, 1, tmp + (4LL + jw) * pw[ps]);
        }
    }
}

class LuckySum
{
        public:
        long long construct(string note)
        {
            ans = oo;
            pw[0] = 1;
            for (int i = 1; i <= 15; ++i)
                pw[i] = pw[i - 1] * 10LL;
            n = note.length();
            for (int i = 0; i < n; ++i)
                if (note[n - 1 - i] == '?') a[i] = -1;
                else a[i] = note[n - 1 - i] - '0';
            
            dfs(n - 1, n - 1, 0, 0, 0);
            for (int i = 1; i <= n; ++i)
                dfs(n, i, 0, 0, 0);
            if (ans == oo) return -1;
            return ans;
        }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "??"; long long Arg1 = 8LL; verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { string Arg0 = "?1"; long long Arg1 = 11LL; verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { string Arg0 = "4?8"; long long Arg1 = 448LL; verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { string Arg0 = "2??"; long long Arg1 = -1LL; verify_case(3, Arg1, construct(Arg0)); }
	void test_case_4() { string Arg0 = "??????????????"; long long Arg1 = 11888888888888LL; verify_case(4, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        LuckySum ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
