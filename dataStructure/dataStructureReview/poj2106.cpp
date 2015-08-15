#include <vector>
#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))


using namespace std;

vector<bool> opNum;
vector<char> opcode;
map<char, int> level;


void calc()
{
	if (opcode.back() == '!') 
		opNum.back() = !opNum.back();
	else
	{
		bool u = opNum.back();
		opNum.pop_back();
		bool v = opNum.back();
		opNum.pop_back();
		if (opcode.back() == '&') 
			opNum.push_back(u & v);
		else opNum.push_back(u | v);
	}
	opcode.pop_back();
}

char com(char u, char v)
{
	if (u == '(' && v == ')') return '=';
	if (u == '#' || v == '(') return '<';
	if (v == ')') return '>';
	if (u == v) return '<';
	if (level[u] <= level[v]) return '<';
	return '>';
}

int main()
{
	freopen("in2106.txt", "r", stdin);
	level.clear();
	level['|'] = 1;
	level['&'] = 2;
	level['!'] = 3;
	for (int task = 1;;++task)
	{
		opNum.clear();
		opcode.clear();
		opcode.push_back('#');  //加入#，方便判断，防止溢出
		char ch = getchar();
		if (ch == EOF) break;
		for(;;)
		{
			for (; ch == ' '; ch = getchar());
			if (ch == '\n' || ch == EOF) 
			{
				for (; opcode.back() != '#'; )
					calc();
				break;
			}
			if (ch == 'V' || ch == 'F')
			{ 
				opNum.push_back(ch == 'V' ? true : false);
				ch = getchar();
			}
			else 
			{
				switch(com(opcode.back(), ch))
				{
				case '<':opcode.push_back(ch); ch = getchar(); break;
				case '>':calc(); break;
				case '=':opcode.pop_back(); ch = getchar(); break;
				}
			}
		}
		printf("Expression %d: %c\n", task, opNum.back() ? 'V' : 'F');
		if (ch == EOF) break;
	}
	return 0;
}
