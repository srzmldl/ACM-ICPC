import java.math.*;
import java.util.*;
import java.text.*;
import java.io.*;
import java.awt.*;


public class check {

	/**
	 * @param args
	 */
	public static int getBits(int x)
	{
		int tmp = 0;
		for (; x > 0; x >>= 1)
			if ((x & 1) == 1) tmp++;
		return tmp;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
				StdOut.println(2);
				Scanner cin = new Scanner(new BufferedInputStream(System.in));
				PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
				int n = cin.nextInt();
				int k = cin.nextInt();
				BigInteger ans = BigInteger.ZERO;
				for (int i = 0; i < (1 << 25); ++i)
					if (getBits(i) == k)
					{
						BigInteger lcm = BigInteger.ONE;
						for (int j = 0; j < 25; ++j)
								if (((1 << j) & i) > 0)
								{
									 BigInteger gcd = lcm.gcd(BigInteger.valueOf(n - j));
									 lcm = lcm.multiply(BigInteger.valueOf(n - j));
									 lcm = lcm.divide(gcd);
								}
						if (lcm.compareTo(ans) > 0) ans = lcm;
					}
				out.println(ans);
				out.flush();
	}
}

