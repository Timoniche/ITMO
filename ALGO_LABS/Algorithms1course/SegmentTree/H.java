import java.io.*;
import java.util.StringTokenizer;
 
public class H {
    private final static int INF = Integer.MAX_VALUE;
    private final static int MINF = Integer.MIN_VALUE;
 
    private static int n;
    private static int[] atree;
    private static int[] minTree;
    private static int[] ans;
    private static int[] storage;
    private static boolean flag = true;
 
    static class MyScanner implements AutoCloseable {
        BufferedReader br;
        StringTokenizer st;
 
 
        MyScanner(File is) {
            try {
                br = new BufferedReader(new FileReader(is));
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
 
        public void close() throws Exception {
            br.close();
        }
    }
 
    public static void main(String[] args) {
        try (MyScanner sc = new MyScanner(new File("rmq.in"))) {
            try (PrintWriter pr = new PrintWriter(new File("rmq.out"))) {
                n = sc.nextInt();
                atree = new int[4 * n];
                for (int i = 0; i < 4 * n; i++) {
                    atree[i] = MINF;
                }
                int m = sc.nextInt();
                storage = new int[3 * m];
                int counter = 0;
                for (int t = 0; t < m; t++) {
                    set(storage[counter++] = sc.nextInt(),
                            storage[counter++] = sc.nextInt(),
                            storage[counter++] = sc.nextInt());
                }
                ans = new int[n];
                minTree = new int[4 * n];
                build(1, 0, n - 1);
                buildMin(1, 0, n - 1);
                counter = 0;
                for (int t = 0; t < m; t++) {
                    int tmp = min(storage[counter++], storage[counter++]);
                    if (tmp != storage[counter++]) {
                        pr.println("inconsistent");
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    pr.println("consistent");
                    for (int i = 0; i < n; i++) {
                        pr.print(ans[i] + " ");
                    }
                }
            }
        } catch (Exception e) {
            System.out.println("Очень жаль");
            e.printStackTrace();
        }
    }
 
    public static void build(int v, int tl, int tr) {
        if (tl > tr) {
            return;
        }
        if (tl == tr) {
            ans[tl] = atree[v];
            return;
        }
        push(v);
        int tm = tl + (tr - tl) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
    }
 
    public static void buildMin(int v, int tl, int tr) {
        if (tl > tr) {
            return;
        }
        if (tl == tr) {
            if (tl < n) {
                minTree[v] = ans[tl];
            } else {
                minTree[v] = INF;
            }
            return;
        }
        int tm = tl + (tr - tl) / 2;
        buildMin(2 * v, tl, tm);
        buildMin(2 * v + 1, tm + 1, tr);
        minTree[v] = Math.min(minTree[2 * v], minTree[2 * v + 1]);
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
        //atree[v] = Math.min(atree[2 * v], atree[2 * v + 1]);
        atree[v] = Math.max(atree[v], Math.min(atree[2 * v], atree[2 * v + 1]));
    }
 
    public static int min(int l, int r) {
        return minThis(1, 0, n - 1, l - 1, r - 1);
    }
 
    public static int minThis(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return INF;
        }
        if (l == tl && r == tr) {
            return minTree[v];
        }
        int tm = tl + (tr - tl) / 2;
        return Math.min(minThis(2 * v, tl, tm, l, Math.min(r, tm)),
                minThis(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r));
    }
 
 
    public static void push(int v) {
        if (atree[v] != MINF) {
            atree[2 * v] = Math.max(atree[v], atree[2 * v]);
            atree[2 * v + 1] = Math.max(atree[v], atree[2 * v + 1]);
        }
    }
 
}
