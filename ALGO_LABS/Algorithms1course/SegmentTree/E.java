import java.io.*;
import java.util.StringTokenizer;
 
class Node {
    long a;
    long b;
    long c;
    long d;
 
    public Node(long a, long b, long c, long d) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
    }
}
 
public class E {
    static Node[] atree;
    static int r;
    static Node E = new Node(1, 0, 0, 1);
 
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
 
        long nextLong() {
            long radix = Long.parseLong(next());
            return radix;
        }
 
        public void close() throws Exception {
            br.close();
        }
    }
 
 
    static Node mul(Node m1, Node m2) {
        long a, b, c, d;
        a = (m1.a * m2.a + m1.b * m2.c) % r;
        b = (m1.a * m2.b + m1.b * m2.d) % r;
        c = (m1.c * m2.a + m1.d * m2.c) % r;
        d = (m1.c * m2.b + m1.d * m2.d) % r;
        return new Node(a, b, c, d);
    }
 
    static Node get(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return E;
        if (l == tl && r == tr) {
            return atree[v];
        }
        int tm = (tl + tr) / 2;
        return mul(get(2 * v, tl, tm, l, Math.min(tm, r)),
                get(2 * v + 1, tm + 1, tr, Math.max(tm + 1, l), r));
    }
 
    static void build(Node[] a, int v, int tl, int tr) {
        if (tl == tr) {
            atree[v] = a[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(a, 2 * v, tl, tm);
        build(a, 2 * v + 1, tm + 1, tr);
        atree[v] = mul(atree[2 * v], atree[2 * v + 1]);
    }
 
    public static void main(String[] args) {
        try (MyScanner sc = new MyScanner(new FileInputStream(new File("crypto.in")))) {
            try (PrintWriter pr = new PrintWriter(new File("crypto.out"))) {
                r = sc.nextInt();
                int n = sc.nextInt(), m = sc.nextInt();
                final Node a[] = new Node[n];
                atree = new Node[4 * n];
                for (int i = 0; i < n; i++) {
                    long atmp = sc.nextLong(), btmp = sc.nextLong(), ctmp = sc.nextLong(), dtmp = sc.nextLong();
                    a[i] = new Node(atmp, btmp, ctmp, dtmp);
                }
                build(a, 1, 0, n - 1);
                for (int i = 0; i < m; i++) {
                    int x1 = sc.nextInt(), x2 = sc.nextInt();
                    Node tmp = get(1, 0, n - 1, x1 - 1, x2 - 1);
                    pr.println(tmp.a + " " + tmp.b);
                    pr.println(tmp.c + " " + tmp.d);
                    pr.println();
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("No file " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Очень жаль: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
