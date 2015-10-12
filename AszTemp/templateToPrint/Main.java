import java.io.*;
import java.math.*;
import java.util.*;
import java.text.*;


class point
{
    int A, B;
    double C;
    public point(int a, int b)
    {
        this.A = a; this.B = b; 
        if (b == 0) this.C = 1e20;
        else this.C = 1.0 * a / b;
    }
};

public class Main
{
    public static int N, V;
    public static int[] A = new int[44];
    public static int[] B = new int[44];
    public static double[] C = new double[44];
    public static final int MAXN = 44;
    public static point[] g = new point[MAXN];

    public static void main(String[] args)
    {

        Comparator<point> comparator = new Comparator<point>(){
               public int compare(point s1, point s2) {
                   return (s1.C < s2.C) ? -1 : 1;
               }
        };
        
        Scanner cin = new Scanner(new BufferedInputStream(System.in));
	PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int task = cin.nextInt();
        for (; task > 0; --task)
        {
            N = cin.nextInt();
            V = cin.nextInt();
            for (int i = 0; i < N; ++i)
                A[i] = cin.nextInt();
            int flag = 1;
            for (int i = 0; i < N; ++i)
            {
                B[i] = cin.nextInt();
                if (B[i] != 0 && A[i] >= V)
                    flag = 0;
            }
            if (flag == 0) 
            {
                out.println(-1);
                continue;
            }
            for (int i = 0; i < N; ++i)    
                g[i] = new point(A[i], B[i]);
            Arrays.sort(g, 0, N, comparator);
            BigDecimal ans = BigDecimal.ZERO;
            for (int i = N - 1; i >= 0; --i)
            {
                if (g[i].B == 0) continue;
                BigDecimal tmp = ans.multiply(BigDecimal.valueOf(1.0 * g[i].A));
                tmp = tmp.add(BigDecimal.valueOf(1.0 * g[i].B));
                //System.out.println(tmp + " " + (1.0 * V - g[i].A));
                tmp = tmp.divide(BigDecimal.valueOf(1.0 * V - g[i].A), 1000, BigDecimal.ROUND_HALF_UP);
                ans = ans.add(tmp);
            }
            out.println(ans.setScale(0, BigDecimal.ROUND_HALF_UP)); //保留0位小数
        //    Arrays.sort
        }	
    	out.flush();    
    }    
}
