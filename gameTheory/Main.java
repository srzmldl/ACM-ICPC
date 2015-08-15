import java.util.*;
import java.io.*;
import java.awt.*;
import java.text.*;
import java.math.*;

public class Main {

	public static final int MAXN = 6;
	public static int tot = 0;
	public static BigInteger[] ans = new BigInteger[MAXN];
	
	public static void calc(BigInteger A, BigInteger B)
	{
			for (;;)
			{
				if (B.equals(BigInteger.ZERO)) break;
				ans[++tot] = A.divide(B);
				BigInteger C = B;
				B = A.subtract(B.multiply(ans[tot]));
				A = C;
			}
	//	if (B == BigInteger.ZERO) return;
	//	ans[++tot] = A.divide(B);
	//	calc(B, A.mod(B));
	}
	
	public static void main(String[] args) {
		try{
		File srcFile = new File("continued.in");
		File desFile = new File("continued.out");
		Scanner cin = new Scanner(new BufferedInputStream(new FileInputStream(srcFile)));
		PrintWriter cout = new PrintWriter(new OutputStreamWriter(new FileOutputStream(desFile)));
		int N = cin.nextInt();
		int M = cin.nextInt();
	
		BigInteger A = BigInteger.valueOf(10);
		A = A.pow(N);
		//A = power(A, N);
		
		BigInteger B = BigInteger.valueOf(10);
		B = B.pow(M);
		B = B.subtract(BigInteger.ONE);

		calc(A, B);
		
		cout.println(tot - 1);
		cout.print(ans[1]);
		for (int i = 2; i <= tot; ++i)
			cout.print(" " + ans[i]);
		cout.println();
		
		cout.flush();
		cout.close();
		cin.close();
		}
		catch(IOException e)
		{
			
		}
		
	}

}
