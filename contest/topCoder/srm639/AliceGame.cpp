// BEGIN CUT HERE

// END CUT HERE
#line 5 "AliceGame.cpp"
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


class AliceGame
{
        public:
	long long findsqr(long long x)
		{
			long long last = 0;
			for (long long i = 1; ; ++i)
			{
				if (i * i > x) break;
				last = i;
			}
			return last;
		}
	long long findMinimumValue(long long x, long long y)
        {
			
			if (x == 2 || y == 2) return -1;
			long long tmp = x + y;
			long long n = findsqr(tmp);
			long long lim = 2LL * n - 1;
			if (n * n == tmp)
			{
				if (x == 0) return 0;
				if (y == 0) return n;
				if (x <= lim)
				{
					if (x & 1) return 1;
					else return 2;
				}
				long long m = findsqr(y);
				long long rst = y - m * m;
				if (rst == 0) return n - m;
				if ((rst & 1) == 0) return n - m;
				if (rst < 2LL * m - 1) return n - (m - 1);
				if (m * m + m * 2LL - 1 + 2 + m * 2LL - 1 + 4 <= tmp)
					return n - (m - 1);
				return -1;
			} else return -1;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 8LL; long long Arg1 = 17LL; long long Arg2 = 2LL; verify_case(0, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 17LL; long long Arg1 = 8LL; long long Arg2 = 3LL; verify_case(1, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 0LL; long long Arg1 = 0LL; long long Arg2 = 0LL; verify_case(2, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 9LL; long long Arg1 = 9LL; long long Arg2 = -1LL; verify_case(3, Arg2, findMinimumValue(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 500000LL; long long Arg1 = 500000LL; long long Arg2 = 294LL; verify_case(4, Arg2, findMinimumValue(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        AliceGame ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
