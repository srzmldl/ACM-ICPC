import java.util.*;
import java.io.*;
import java.math.*;

public class A {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner cin = new Scanner(new BufferedInputStream(System.in));
		PrintWriter cout = new PrintWriter(new BufferedOutputStream(System.out));
		BigInteger n;
		n = cin.nextBigInteger();
		BigInteger BigTwo = BigInteger.valueOf(2);
		BigInteger ans = BigInteger.ZERO;
		for (;n.compareTo(BigInteger.ZERO) == 1;)
		{
			BigInteger tmp = n.subtract(BigTwo);
			tmp = tmp.divide(BigTwo);
			BigInteger x = tmp.add(BigInteger.ONE);
			ans = ans.add(n.subtract(x));
			ans = ans.add(BigInteger.ONE);
			n = (x.subtract(BigTwo)).divide(BigTwo);
			//cout.println(n);
			if (x.and(BigInteger.ONE).equals(BigInteger.ZERO))
			{
				n = n.subtract(BigInteger.ONE);
			}
			
		}
		cout.println(ans);
		cout.flush();
		cin.close();
		cout.close();
	}

}
