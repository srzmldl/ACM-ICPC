#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#define REP(i, n) for(int i = 0; i < (int) (n); ++i)
#define REPP(i, a, b) for(int i = (int) (a); i <= (int) (b); ++i)
#define MST(a, b) memset((a), (b), sizeof(a))
#define MAXN 444

using namespace std;
typedef int arrayN[MAXN];
arrayN vote, voteFinal, f, g;
int N, M, V, voteLeft, se[111], vo[111];

int checkMax(int pos, int seat)
{
	long long seatOther = 0;
	REPP(i, 0, pos - 1)
		if (vote[i] * 20 >= V)
			seatOther += 1LL * (vote[i] * (seat)) / vote[pos];
	REPP(i, pos + 1, N - 1)
		if (vote[i] * 20 >= V)
		{
			int tmp = vote[i] * (seat) / vote[pos];
			if (vote[i] * (seat) % vote[pos] == 0)
				seatOther += 1LL * max(tmp - 1, 0);
			else seatOther += 1LL * tmp;
		}
	if (seatOther + seat <= 1LL * M) return 1;
	return 0;
}

void solveMax()
{
	if (N == 1)
	{
		printf("%d\n", M);
		return ;
	}

	REP(i, N)
	{
		vote[i] += voteLeft;
		{
			int l = 0, r = M;
			if (vote[i] * 20 < V) r = 0;
			for (; l < r;)
			{
				int mid = (l + r + 1) >> 1;
				if (checkMax(i, mid)) l = mid;
				else r = mid - 1;
			}
			printf("%d%c", l, " \n"[i == N - 1]);
		}

		vote[i] -= voteLeft;
	}
}

int checkMin(int pos, int seat)
{
	long long seatTot = seat, seatLeft;
	MST(se, 0);

	REP(i, pos)
		if (vote[i] * 20 >= V)
		{
			se[i] = vote[i] * (seat + 1) / vote[pos];
			seatTot += 1LL * se[i];
		}

	REPP(i, pos + 1, N - 1)
		if (vote[i] * 20 >= V)
		{
			int tmp = vote[i] * (seat + 1) / vote[pos];
			if (vote[i] * (seat + 1) % vote[pos] == 0)
				se[i] += max(tmp - 1, 0);
			else se[i] += tmp;
			seatTot += 1LL * se[i];
		}

	if (seatTot >= 1LL * M) return 1;
	seatLeft = M - seatTot;

	MST(f, 0x3f);
	f[0] = 0;
	REP(i, N)
		if (i != pos)
		{
			REPP(k, 0, seatLeft) g[k] = f[k];
			f[0] = f[0];
			REPP(j, 1, seatLeft)
			{
				int k = se[i] + j;
				int tmp = vote[pos] * k / (seat + 1);
				int x;
				if (i < pos)
				{
					if (vote[pos] * k % (seat + 1) == 0)
						x = tmp - vote[i];
					else x = tmp + 1 - vote[i];
				} else
				{
					x = tmp + 1 - vote[i];
				}
				x = max(x, V / 20 - vote[i]);

				REPP(h, 0, seatLeft)
				{
					if (x + g[h] <= voteLeft)
					{
						if (h + j >= seatLeft) return 1;
						f[h + j] = min(f[h + j], g[h] + x);
					}
				}

			}
		}
	if (f[seatLeft] <= voteLeft) return 1;
	return 0;
}

void solveMin()
{
	if (N == 1)
	{
		printf("%d\n", M);
		return ;
	}
	REP(i, N)
	{
		int l = 0, r = M;
		if (vote[i] * 20 < V)
			r = 0;
		for (; l < r; )
		{
			int mid = (l + r) >> 1;
			if (checkMin(i, mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d%c", l, " \n"[i == N - 1]);
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	for (;scanf("%d%d%d", &V, &N, &M) != EOF;)
	{
		int sumVote = 0;
		REP(i, N)
		{
			scanf("%d", vote + i);
			sumVote += vote[i];
		}
		voteLeft = V - sumVote;
		solveMax();
		solveMin();
	}
	return 0;
}
