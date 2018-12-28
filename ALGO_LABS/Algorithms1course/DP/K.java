import java.io.*;
import java.util.*;
 
public class K {
 
    public boolean can(int i, int j, int n) {
        int predi = 0, predj = 1;
        while (n > 0) {
            int tempi = i % 2;
            int tempj = j % 2;
            if (tempi == tempj && predi == predj && predi == tempi) {
                return false;
            } else {
                predi = tempi;
                predj = tempj;
            }
            i /= 2;
            j /= 2;
            n--;
        }
        return true;
    }
 
    public void run () throws IOException {
        String fileInName = "nice.in";
        String fileOutName = "nice.out";
 
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        Scanner sc = new Scanner(file);
 
        int m = sc.nextInt();
        int n = sc.nextInt();
        if (m < n) {
            int temp = n;
            n = m;
            m = temp;
        }
 
        //можно ли перейти с маски на маску
        boolean[][] pos = new boolean[1 << n][1 << n];
        for (int i = 0; i < 1 << n; i++) {
            for (int j = 0; j < 1 << n; j++) {
                if (can(i, j, n)) {
                    pos[i][j] = true;
                }
            }
        }
 
        //можно взять любую маску
        long[][] ans = new long[m][1 << n];
        for (int i = 0; i < 1 << n; i++) {
            ans[0][i] = 1;
        }
 
        for (int mi = 1; mi < m; mi++) {
            for (int i = 0; i < 1 << n; i++) {
                for (int j = 0; j < 1 << n; j++) {
                    if (pos[j][i]) {
                        ans[mi][i] += ans[mi - 1][j];
                    }
                }
            }
        }
 
        long otv = 0;
        for (int i = 0; i < 1 << n; i++) {
            otv += ans[m - 1][i];
        }
 
        writer.print(otv);
 
        writer.close();
    }
    public static void main(String[] args) throws IOException {
        new K().run();
    }
}
