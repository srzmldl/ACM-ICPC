#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)

using namespace std;


char st[500];
int vis[500];
char g[10] = "fjxmlhx";
char g1[15] = "marshtomp";


char change(char x)
{
	if (x >= 'A' && x <= 'Z')
		return x - 'A' + 'a';
	return x;
}

int main()
{
//	int i 
	freopen("in.txt", "r", stdin);
	for (; cin.getline(st, sizeof(st));)
	{
		int len = strlen(st);
		memset(vis, 0, sizeof(vis));
		REP(i, len)
		{
			vis[i] = 1;
			if (i + 8 < len)
			{
				REP(j, 9)
					if (change(g1[j]) != change(st[i + j]))
					{
						vis[i] = 0;
						break;
					}
			} else vis[i] = 0;
		}
		
		for (int i = 0; i < len; ++i)
		{
			if (!vis[i]) cout << st[i];
			else 
			{
				cout << g;
				i += 8;
			}
		}	
		cout <<  endl;
	}
	return 0;
}
