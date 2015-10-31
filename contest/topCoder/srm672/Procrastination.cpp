// BEGIN CUT HERE

// END CUT HERE
#line 5 "Procrastination.cpp"
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
#define ll long long

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long LL;
typedef pair<int,int> PII;

const long long oo = 112345678910LL;

class Procrastination
{
    ll getTn(ll n, ll lim) {
        ll tn = -1;
        if (n == 1 || lim <= 1) return tn;
        for (ll j = 2; j * j <= n && j <= lim; ++j) {
            if (n % j == 0) {
                tn = max(j, tn);
                ll tmp = n / j;
                if (tmp <= lim) {
                    tn = tmp;
                    break;
                }
            }
        }
        return tn;
    }
    
    long long solve(ll n, ll lim) {
        ll tn = getTn(n, lim);
        ll tnm1 = getTn(n - 1, lim);
        if (tn == -1 && tnm1 == -1)
            return n;
        if (tn >= tnm1) {
            return solve(n + 1, tn - 1);
        } else {
            return solve(n - 1, tnm1 - 1);
        }
    }
public:
    long long findFinalAssignee(long long n)
        {
            return solve(n, oo);
        }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 3LL; long long Arg1 = 3LL; verify_case(0, Arg1, findFinalAssignee(Arg0)); }
	void test_case_1() { long long Arg0 = 8LL; long long Arg1 = 11LL; verify_case(1, Arg1, findFinalAssignee(Arg0)); }
	void test_case_2() { long long Arg0 = 20LL; long long Arg1 = 20LL; verify_case(2, Arg1, findFinalAssignee(Arg0)); }
	void test_case_3() { long long Arg0 = 196248LL; long long Arg1 = 196259LL; verify_case(3, Arg1, findFinalAssignee(Arg0)); }
	void test_case_4() { long long Arg0 = 10000000000LL; long long Arg1 = 10000000000LL; verify_case(4, Arg1, findFinalAssignee(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Procrastination ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
