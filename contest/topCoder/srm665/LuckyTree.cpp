// BEGIN CUT HERE

// END CUT HERE
#line 5 "LuckyTree.cpp"
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


class LuckyTree
{
        public:
        vector <int> construct(int favorite)
        {
             
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 1; int Arr1[] = {3, 0, 1, 4, 1, 2, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, construct(Arg0)); }
	void test_case_1() { int Arg0 = 64; int Arr1[] = {17, 0, 1, 4, 0, 2, 4, 0, 3, 4, 0, 4, 4, 0, 5, 4, 0, 6, 4, 0, 7, 4, 0, 8, 4, 0, 9, 7, 0, 10, 7, 0, 11, 7, 0, 12, 7, 0, 13, 7, 0, 14, 7, 0, 15, 7, 0, 16, 7 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, construct(Arg0)); }
	void test_case_2() { int Arg0 = 47; int Arr1[] = {15, 1, 12, 4, 1, 11, 4, 0, 1, 7, 0, 2, 7, 2, 10, 4, 2, 9, 4, 0, 4, 4, 0, 3, 4, 3, 7, 7, 3, 8, 7, 4, 5, 7, 4, 6, 7, 12, 13, 7, 13, 14, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, construct(Arg0)); }
	void test_case_3() { int Arg0 = 1275; int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, construct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        LuckyTree ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
