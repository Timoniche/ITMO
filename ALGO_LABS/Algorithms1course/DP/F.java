import java.util.*;
 
public class F {
    Scanner sc = new Scanner(System.in);
    String s = sc.nextLine();
    int n = s.length();
    int[][] dp = new int[n][n]; //d[l][r] sub-clusters
 
    public int f(int l, int r) {
        //base
        if (r == l) {
            dp[r][r] = 1;
            return 1;
        }
 
        //base
        if (l + 1 == r) {
            if (s.charAt(l) == '(' && s.charAt(r) == ')') {
                dp[l][r] = 0;
                return 0;
            }
            else if (s.charAt(l) == '[' && s.charAt(r) == ']') {
                dp[l][r] = 0;
                return 0;
            }
            else if (s.charAt(l) == '{' && s.charAt(r) == '}') {
                dp[l][r] = 0;
                return 0;
            } else {
                dp[l][r] = 2;
                return 2;
            }
        }
 
        //l < r && l + 1 < r
        if (s.charAt(l) == '(' && s.charAt(r) == ')' ||
                s.charAt(l) == '[' && s.charAt(r) == ']' ||
                s.charAt(l) == '{' && s.charAt(r) == '}') {
            if (dp[l + 1][r - 1] == 1000_000) {
                dp[l + 1][r - 1] = f(l + 1, r - 1);
            }
            dp[l][r] = dp[l + 1][r - 1];
        }
 
 
        if (dp[l + 1][r] == 1000_000) {
            dp[l + 1][r] = f(l + 1, r);
        }
        if (dp[l][r - 1] == 1000_000) {
            dp[l][r - 1] = f(l, r - 1);
        }
 
        dp[l][r] = Math.min(dp[l][r], dp[l + 1][r] + 1);
        dp[l][r] = Math.min(dp[l][r], dp[l][r - 1] + 1);
 
        for (int k = l; k < r; k++) {
            if (dp[l][k] == 1000_000) {
                dp[l][k] = f(l, k);
            }
            if (dp[k + 1][r] == 1000_000) {
                dp[k + 1][r] = f(k + 1, r);
            }
            dp[l][r] = Math.min(dp[l][r], dp[l][k] + dp[k + 1][r]);
        }
 
        return dp[l][r];
 
    }
 
    public void run() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = 1000_000;
            }
        }
 
        System.out.println(n - f(0, n - 1));
 
        /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(dp[i][j] + "     ");
            }
            System.out.println();
        }*/
 
    }
 
    public static void main(String[] args) {
        new F().run();
 
    }
}
