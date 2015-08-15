// BEGIN CUT HERE

// END CUT HERE
#line 5 "BoardFolding.cpp"
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




class BoardFolding
{
        public:
	int tonumber(char x)
		{
			if (x >= '0' && x <= '9') return x - '0';
			if (x >= 'a' && x <= 'z') return x - 'a' + 10;
			if (x >= 'A' && x <= 'Z') return x - 'A' + 36;
			if (x == '#') return 62;
			if (x == '@') return 63;
		}
	int pap[300][300];

	int checkRow(int x, int y, int N, int M)
		{
			if (x >= N || y >= N || x < 0 || y < 0) return 0;
			for (int i = 0; i < M; ++i)
				if (pap[x][i] != pap[y][i]) return 0;
			return 1;
		}


	int checkCol(int x, int y, int N, int M)
		{
			if (x >= M || y >= M || x < 0 || y < 0) return 0;
			for (int i = 0; i < N; ++i)
				if (pap[i][x] != pap[i][y]) return 0;
			return 1;
		}
	
	int howMany(int N, int M, vector <string> compressedPaper)
        {
			for (int i = 0; i <= N - 1; ++i)
				for (int j = 0; j <= M - 1; ++j)
					pap[i][j] = (tonumber(compressedPaper[i][j / 6]) >> (j % 6)) % 2;
			vector<int> L, R, U, D;
			int last = 0;
			for (int i = 0; i <= N - 1; ++i)
			{
				int flag = 1;
				for (int j = 1; j <= i && flag && i - j >= last; ++j)
					if (!checkRow(i - j, i + j - 1, N, M))
						flag = 0;
				if (flag)
				{ 
					L.push_back(i);
					last = i;
				}
			}
			
			last = N - 1;
			for (int i = N - 1; i >= 0; --i)
				{
					int flag = 1;
					for (int j = 1; j <= N - 1 - i && flag && i + j <= last; ++j)
						if (!checkRow(i + j, i - j + 1, N, M))
							flag = 0;
					if (flag)
					{
						R.push_back(i);
						last = i;
					}
				}
			
			
			last = 0;
			for (int i = 0; i <= M - 1; ++i)
			{
				int flag = 1;
				for (int j = 1; j <= i && flag && i - j >= last; ++j)
					if (!checkCol(i - j, i + j - 1, N, M))
						flag = 0;
				if (flag)
				{ 
					U.push_back(i);
					last = i;
				}
			}
			
			last = M - 1;
			for (int i = M - 1; i >= 0; --i)
			{
				int flag = 1;
				for (int j = 1; j <= M - 1 - i && flag && i + j <= last; ++j)
					if (!checkCol(i + j, i - j + 1, N, M))
						flag = 0;
				if (flag) 
				{
					D.push_back(i);
					last = i;
				}
			}
			

			

			long long t1 = 0, t2 = 0;
			for (int i = 0; i < L.size(); ++i)
				for (int j = 0; j < R.size(); ++j)
					if (L[i] <= R[j]) t1++;
			for (int i = 0; i < U.size(); ++i)
				for (int j = 0; j < D.size(); ++j)
					if (U[i] <= D[j]) t2++;
			return t1 * t2;

        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; string Arr2[] = {"1", "3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 7; string Arr2[] = {"@@", "@@"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 84; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 4; string Arr2[] = {"6", "9", "9", "6"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 9; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; string Arr2[] = {"0", "2", "6", "@", "4", "A"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 3; string Arr2[] = {"0", "2", "0"}
; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        BoardFolding ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
