import java.io.*;
import java.util.StringTokenizer;
 
public class J {
    private final static int INF = Integer.MAX_VALUE;
 
    private static int n;
    private static int[] atree;
    private static int curMin = INF;
    private static int curVertix;
    private static int curTl;
    private static int curTr;
    private static int minIndex;
 
    static class MyScanner implements AutoCloseable {
        BufferedReader br;
        StringTokenizer st;
 
        MyScanner(InputStream is) {
            br = new BufferedReader(new InputStreamReader(is));
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
 
        public void close() throws Exception {
            br.close();
        }
    }
 
    public static void main(String[] args) {
        try (MyScanner sc = new MyScanner(System.in)) {
            n = sc.nextInt();
            int m = sc.nextInt();
            int a, b, c, d, e;
            atree = new int[4 * n];
            for (int i = 0; i < m; i++) {
                String s = sc.next();
                switch (s.charAt(0)) {
                    case 'd':
                        a = sc.nextInt();
                        b = sc.nextInt();
                        c = sc.nextInt();
                        set(a, b, c);
                        break;
                    case 'a':
                        d = sc.nextInt();
                        e = sc.nextInt();
                        //reset
                        curVertix = 0;
                        curMin = INF;
                        minIndex = -1;
                        curTl = 0;
                        curTr = 0;
                        //
                        min(d, e);
                        minIndex(curVertix, curTl, curTr);
                        System.out.println(curMin + " " + minIndex);
                        break;
                }
            }
        } catch (Exception e) {
            System.out.println("Очень жаль");
            e.printStackTrace();
        }
    }
 
    public static void set(int l, int r, int set) {
        setThis(1, 0, n - 1, l - 1, r - 1, set);
    }
 
    public static void setThis(int v, int tl, int tr, int l, int r, int set) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            atree[v] = Math.max(set, atree[v]);
            return;
        }
        push(v);
        int tm = tl + (tr - tl) / 2;
        setThis(2 * v, tl, tm, l, Math.min(tm, r), set);
        setThis(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, set);
        atree[v] = Math.max(atree[v], Math.min(atree[2 * v], atree[2 * v + 1]));
    }
 
    public static void min(int l, int r) {
        minThis(1, 0, n - 1, l - 1, r - 1);
    }
 
    public static void minThis(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            if (atree[v] < curMin) {
                curMin = atree[v];
                curVertix = v;
                curTl = tl;
                curTr = tr;
            }
            return;
        }
        push(v);
        int tm = tl + (tr - tl) / 2;
        minThis(2 * v, tl, tm, l, Math.min(r, tm));
        minThis(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r);
    }
 
    public static void minIndex(int v, int l, int r) {
        if (l == r) {
            minIndex = l + 1;
            return;
        }
        push(v);
        int tm = l + (r - l) / 2;
        if (atree[2 * v] == curMin) {
            minIndex(2 * v, l, tm);
            return;
        }
        minIndex(2 * v + 1, tm + 1, r);
    }
 
    public static void push(int v) {
        atree[2 * v] = Math.max(atree[v], atree[2 * v]);
        atree[2 * v + 1] = Math.max(atree[v], atree[2 * v + 1]);
    }
 
 
}
