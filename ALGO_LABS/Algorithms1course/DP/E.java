import java.util.*;
 
public class E {
    Scanner sc = new Scanner(System.in);
    final int n = sc.nextInt();
    int[] value = new int[n];
    int k1 = 0, k2 = 0;
    int minsum = 300_000;
    int[] ans = new int[n];
    int y = n - 1; //указатель на ans
    int[][] dp = new int[n][n + 2];
 
    /**
     * деньги за i дней с j купонами
     */
 
    public boolean search (int row, int what, int index) {
        if (dp[row][index + 1] == what) {
            return true;
        }
 
        return false;
    }
 
    public void run() {
        if (n != 0) {
            for (int i = 0; i < n; i++) {
                value[i] = sc.nextInt();
            }
 
            //fill 1st day
            for (int j = 0; j < n + 2; j++) {
                dp[0][j] = 300_000;
            }
 
            if (value[0] <= 100) {
                dp[0][0] = value[0];
            } else {
                dp[0][1] = value[0];
            }
            //
 
            for (int i = 0; i < n; i++) {
                dp[i][n + 1] = 300_000;
            }
 
            for (int i = 1; i < n; i++) {
 
                for (int j = 1; j < n + 1; j++) {
                    if (value[i] <= 100) {
                        dp[i][j] = Math.min(dp[i - 1][j] + value[i], dp[i - 1][j + 1]);
                    } else {
                        dp[i][j] = Math.min(dp[i - 1][j - 1] + value[i], dp[i - 1][j + 1]);
                    }
                }
 
                if (value[i] <= 100) {
                    dp[i][0] = Math.min(dp[i - 1][0] + value[i], dp[i - 1][1]);
                } else {
                    if (dp[i - 1][1] != 300_000) {
                        dp[i][0] = dp[i - 1][1];
                    } else {
                        dp[i][0] = 300_000;
                    }
                }
 
            }
 
 
        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n + 2; j++) {
                System.out.printf("%7d", dp[i][j]);
            }
            System.out.println();
        }*/
 
            //search sum & k1
            minsum = dp[n - 1][0];
            k1 = 0;
            for (int j = 1; j < n + 1; j++) {
                if (minsum >= dp[n - 1][j]) {
                    minsum = dp[n - 1][j];
                    k1 = j;
                }
            }
 
            int t = n - 1;
            int otv = minsum;
            int index = k1;
            while (t != 0) {
                if (search(t - 1, otv, index)) {
                    index++;
                    ans[y--] = t + 1;
                } else {
                    otv -= value[t];
                    if (dp[t - 1][index] != otv) {
                        index -= 1;
                    }
                }
 
                t--;
            }
 
            System.out.println(minsum);
            System.out.println(k1 + " " + (n - y - 1));
 
            for (int i = y + 1; i < n; i++) {
                System.out.println(ans[i] + " ");
            }
 
 
        } else {
            System.out.println(0);
            System.out.println(0 + " " + 0);
        }
    }
 
    public static void main(String[] args) {
        new E().run();
    }
}
