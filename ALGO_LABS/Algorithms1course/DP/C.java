import java.math.BigInteger;
import java.util.*;
 
public class C {
 
 
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
 
        BigInteger[][] helper = new BigInteger[10][n + 1];
        for (int i = 0; i < 10; i++) {
            helper[i][1] = BigInteger.valueOf(1);
        }
 
        for (int i = 2; i <= n; i++) {
            helper[0][i] = helper[4][i - 1].add(helper[6][i - 1]);
            helper[1][i] = helper[6][i - 1].add(helper[8][i - 1]);
            helper[2][i] = helper[7][i - 1].add(helper[9][i - 1]);
            helper[3][i] = helper[4][i - 1].add(helper[8][i - 1]);
            helper[4][i] = helper[3][i - 1].add(helper[9][i - 1]).add(helper[0][i - 1]);
            //5 missed
            helper[6][i] = helper[1][i - 1].add(helper[7][i - 1]).add(helper[0][i - 1]);
            helper[7][i] = helper[2][i - 1].add(helper[6][i - 1]);
            helper[8][i] = helper[1][i - 1].add(helper[3][i - 1]);
            helper[9][i] = helper[4][i - 1].add(helper[2][i - 1]);
        }
 
        BigInteger ans = BigInteger.valueOf(0);
        if (n == 1) {
            System.out.println(8);
        } else {
            for (int i = 0; i < 10; i++) {
                if (i != 0 && i != 5 && i != 8) {
                    ans = ans.add(helper[i][n]);
                }
            }
            System.out.println(ans.mod(BigInteger.valueOf(1000_000_000)));
        }
    }
}
