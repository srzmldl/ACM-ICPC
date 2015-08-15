import java.io.*;
import java.util.*;


public class la3989 {

	/**
	 * @param args
	 */
	static Scanner cin = new Scanner(new BufferedInputStream(System.in));
	static PrintWriter cout = new PrintWriter(new BufferedOutputStream(System.out));
	final static int MAXN = 1123;
	
	static people[] girl = new people[MAXN];
	static people[] boy = new people[MAXN];
	
	private static class people{
	
		people()
		{
			futureMate = -1;
			pt = 0;
			mate = new int[MAXN];
			rank = new int[MAXN];
		}
		int[] mate;
		int[] rank;
		
		void readMate(int n)
		{
			for (int i = 0; i < n; ++i)
				mate[i] = cin.nextInt() - 1;
		}
		
		void getRank(int n)
		{
			for (int i = 0; i < n; ++i)
				rank[mate[i]] = i;
		}
		
		
		int futureMate, pt;
	}
	

	static void marry(int man, int woman)
	{
		boy[man].futureMate = woman;
		girl[woman].futureMate = man;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int task = cin.nextInt();
		for (int T = 1; T <= task; ++T)
		{
			//if (T > 1) cout.println();
			int n = cin.nextInt();
			for (int i = 0; i < n; ++i)
			{
				girl[i] = new people();
				girl[i].readMate(n);
			}
			
			for (int i = 0; i < n; ++i)
			{
				boy[i] = new people();
				boy[i].readMate(n);
				boy[i].getRank(n);
			}
			Queue<Integer> sole = new LinkedList<Integer>();
			sole.clear();
			for (int i = 0; i < n; ++i)
				sole.add(i);
			
			for (; !sole.isEmpty(); )
			{
				int woman = sole.poll(); 
				if (girl[woman].pt >= n) continue;
				int man = girl[woman].mate[girl[woman].pt++];
				if (boy[man].futureMate == -1)
					marry(man, woman);
				else if  (boy[man].rank[boy[man].futureMate] > boy[man].rank[woman])
				{
					sole.add(boy[man].futureMate);
					marry(man, woman);
				} else sole.add(woman);
			}
			
			for (int i = 0; i < n; ++i)
			{
				cout.println(girl[i].futureMate + 1);
				cout.flush();
			}
			
		}
		
		
		cin.close();
		cout.close();
	}

}
