import java.io.*;
import java.util.StringTokenizer;
 
public class F {
    long[] a;
    long[][] ast;
 
    static class MyScanner implements AutoCloseable {
        BufferedReader br;
        StringTokenizer st;
 
        MyScanner(File inName) {
            try {
                br = new BufferedReader(new FileReader(inName));
            } catch (FileNotFoundException e) {
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            int radix = Integer.parseInt(next());
            return radix;
        }
 
        long nextLong() {
            long radix = Long.parseLong(next());
            return radix;
        }
 
        public void close() throws Exception {
            br.close();
        }
    }
 
    public long flog(long size) {
        if (size == 1) {
            return 0;
        }
        return flog(size / 2) + 1;
    }
 
    public long min(long l, long r) {
        long j = flog(r - l + 1);
        return Math.min(ast[(int) l][(int) j], ast[(int) (r - (1 << j) + 1)][(int) j]);
    }
 
    public void run() {
        try (MyScanner sc = new MyScanner(new File("sparse.in"))) {
            try (PrintWriter pr = new PrintWriter(new File("sparse.out"))) {
                int n = sc.nextInt();
                long m = sc.nextLong(), a1 = sc.nextLong();
                long u1 = sc.nextLong(), v1 = sc.nextLong();
                a = new long[n + 1];
                int maxj = (int) (Math.log(n) / Math.log(2)) + 1;
                ast = new long[n + 1][maxj];
                a[1] = a1;
                for (int i = 2; i <= n; i++) {
                    a[i] = (23 * a[i - 1] + 21563) % 16714589;
                }
                for (int i = 1; i <= n; i++) {
                    ast[i][0] = a[i];
                }
                for (int j = 1; j < maxj; j++) {
                    for (int i = 1; i <= n; i++) {
                        int tmp = i + (1 << (j - 1));
                        if (tmp <= n) {
                            ast[i][j] = Math.min(ast[i][j - 1], ast[tmp][j - 1]);
                        }
                    }
                }
                long ansi;
                if (u1 > v1) {
                    ansi = min(v1, u1);
                } else {
                    ansi = min(u1, v1);
                }
                for (int i = 1; i < m; i++) {
                    u1 = ((17 * u1 + 751 + ansi + 2 * i) % n) + 1;
                    v1 = ((13 * v1 + 593 + ansi + 5 * i) % n) + 1;
                    if (u1 > v1) {
                        ansi = min(v1, u1);
                    } else {
                        ansi = min(u1, v1);
                    }
                }
                pr.print(u1 + " " + v1 + " " + ansi);
 
            }
        } catch (FileNotFoundException e) {
            System.out.println("No file " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Очень жаль: " + e.getMessage());
            e.printStackTrace();
        }
    }
 
    public static void main(String[] args) {
        new F().run();
    }
}
