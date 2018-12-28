import java.io.*;
import java.util.*;
 
public class D {
 
    public int fit (char a, char b) {
        if (a != b) {
            return 1;
        } else {
            return 0;
        }
    }
 
    public void run () throws IOException {
        String fileInName = "input.txt";
        String fileOutName = "output.txt";
 
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        Scanner sc = new Scanner(file);
 
        String s1 = sc.nextLine();
        int n = s1.length();
        String s2 = sc.nextLine();
        int m = s2.length();
 
        //initialization
        int[][] d = new int[n + 1][m + 1];
 
        for (int i = 0; i <= n; i++) {
            d[i][0] = i;
        }
 
        for (int j = 0; j <= m; j++) {
            d[0][j] = j;
        }
 
        //fill
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                d[i][j] = Math.min(d[i - 1][j - 1] + fit(s1.charAt(i - 1), s2.charAt(j - 1)),
                        Math.min(d[i][j - 1] + 1, d[i - 1][j] + 1));
 
            }
        }
 
        /*for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                writer.print(d[i][j] + " ");
            }
            writer.println();
        }*/
 
        writer.print(d[n][m]);
 
        writer.close();
    }
    public static void main(String[] args) throws IOException {
        new D().run();
    }
}
