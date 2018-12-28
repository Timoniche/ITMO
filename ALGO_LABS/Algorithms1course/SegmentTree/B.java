import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;
 
public class B {
 
    static class MyScanner {
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
 
        String nextLine() throws IOException {
            String s = br.readLine();
            return s;
        }
 
        Boolean hasNextLine() throws IOException {
            return br.ready();
        }
 
        int nextInt() {
            int radix = Integer.parseInt(next());
            return radix;
        }
    }
 
    public static int spaceIndex(String s) {
        int begin = 4;
        while (s.charAt(begin) != ' ') {
            begin++;
        }
        return begin;
    }
 
    public static int pow(int n) {
        int tmp = n;
        if (n == 0) return 0;
        if (n == 1) return 2;
        int k = 0;
        boolean flag = true;
        while (n != 1) {
            if (n % 2 == 1) flag = false;
            n /= 2;
            k++;
        }
        if (flag) return tmp;
        return 1 << k + 1;
    }
 
    public static void build(long[] a, int v, int tl, int tr, long[] atree) {
        if (tl == tr) {
            atree[v] = a[tl];
            return;
        }
        int tm = tl + (tr - tl) / 2;
        build(a, 2 * v, tl, tm, atree);
        build(a, 2 * v + 1, tm + 1, tr, atree);
        atree[v] = atree[2 * v] + atree[2 * v + 1];
    }
 
    public static long sum(int v, int tl, int tr, int l, int r, long[] atree) {
        if (l > r) return 0;
        if (l == tl && r == tr) return atree[v];
        int tm = tl + (tr - tl) / 2;
        return sum(2 * v, tl, tm, l, Math.min(r, tm), atree) + sum(2 * v + 1, tm + 1, tr, Math.max(tm + 1, l), r, atree);
    }
 
    public static void set(int v, int tl, int tr, int pos, int newval, long[] atree) {
        if (tl == tr) {
            atree[v] = newval;
            return;
        }
        int tm = tl + (tr - tl) / 2;
        if (pos <= tm) set(2 * v, tl, tm, pos, newval, atree);
        else set(2 * v + 1, tm + 1, tr, pos, newval, atree);
        atree[v] = atree[2 * v] + atree[2 * v + 1];
    }
 
    public static void main(String[] args) throws IOException {
        try {
            MyScanner sc = new MyScanner(new File("rsq.in"));
            try (PrintWriter pr = new PrintWriter(new File("rsq.out"))) {
                int n = Integer.parseInt(sc.nextLine());
                int npow = pow(n);
                long[] a = new long[npow];
                long[] atree = new long[4 * n];
                String s = sc.nextLine();
                Scanner sc2 = new Scanner(s);
                for (int i = 0; i < n; i++) a[i] = sc2.nextInt();
                build(a, 1, 0, npow - 1, atree);
                while (sc.hasNextLine()) {
                    s = sc.nextLine();
                    int tmp = spaceIndex(s);
                    int a1 = Integer.parseInt(s.substring(4, tmp));
                    int a2 = Integer.parseInt(s.substring(tmp + 1));
                    if (s.substring(0, 3).equals("sum")) pr.println(sum(1, 0, npow - 1, a1 - 1, a2 - 1, atree));
                    else set(1, 0, npow - 1, a1 - 1, a2, atree);
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("No file " + e.getMessage());
        }
    }
}
