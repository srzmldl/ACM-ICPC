#include <bits/stdc++.h>

using namespace std;

int nex[20020];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int tail = 1, pre = 0;
	bool fix = false;
	nex[1] = 0;
	nex[0] = -1;
	int i = 0, j = 0, now = 0, cnt = 0;
	for (int rou = 0; rou < m; rou++)
	{
		now++;
		int q = 5;
		char str[5];
		while (q && i < now)
		{
			printf("t %d s %d\n", i + 1, j + 1);
			fflush(stdout);
			q--;
			scanf("%s", str);
			if (str[0] == 'Y')
				i++, j++;
			else
			{
				j = nex[j];
				if (j == -1)
					i++, j++;
			}
			if (j == n)
				cnt++, j = nex[j];
		}
		while (!fix && q && tail < n)
		{
//				printf("%d %d\n", pre, tail);
//				fflush(stdout);
			printf("s %d s %d\n", pre + 1, tail + 1);
			fflush(stdout);
			q--;
			scanf("%s", str);
			if (str[0] == 'Y')
			{
				pre++, tail++;
				nex[tail] = pre;
			}
			else
			{
				pre = nex[pre];
				if (pre == -1)
				{
					pre = 0, tail++;
					nex[tail] = 0;
				}
			}
			if (tail == n)
			{
				fix = true;
				tail = n - 1, pre = nex[tail];
//				for (int i = 0; i <= n; i++)
//					printf("%d%c", nex[i], " \n"[i == n]);
//				fflush(stdout);
			}
		}
//		while (fix && q && tail > 1)
//		{
////				printf("%d %d\n", tail, nex[tail]);
////				fflush(stdout);
//			while (tail > 1 && !nex[tail])
//				tail--;
//			if (tail == 1)
//				break;
//			printf("s %d s %d\n", nex[tail] + 1, tail + 1);
//			fflush(stdout);
//			q--;
//			scanf("%s", str);
//			if (str[0] == 'Y')
//			{
//				nex[tail] = nex[nex[tail]];
//				if (!nex[tail])
//					tail--;
//			}
//			else
//				tail--;
//		}
		printf("$ %d\n", cnt);
		fflush(stdout);
	}
	return 0;
}
