import java.io.*;
import java.util.StringTokenizer;
 
public class C {
    final static long INF = Long.MAX_VALUE;
    Node[] atree;
 
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
 
        long nextLong() {
            long radix = Long.parseLong(next());
            return radix;
        }
 
        public void close() throws Exception {
            br.close();
        }
    }
 
    public class Node {
        long min;
        long add;
        long set;
        boolean isSet;
        boolean isAdd;
 
        public Node(long min, long add, long set, boolean isSet, boolean isAdd) {
            this.min = min;
            this.add = add;
            this.set = set;
            this.isSet = isSet;
            this.isAdd = isAdd;
        }
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
 
    public void build(long[] a, int v, int tl, int tr, int n) {
        if (tl == tr) {
            if (tl < n) {
                atree[v] = new Node(a[tl], 0, -1, false, false);
            } else {
                atree[v] = new Node(INF, 0, -1, false, false);
            }
            return;
        }
        int tm = tl + (tr - tl) / 2;
        build(a, 2 * v, tl, tm, n);
        build(a, 2 * v + 1, tm + 1, tr, n);
        long tmp = Math.min(atree[2 * v].min, atree[2 * v + 1].min);
        atree[v] = new Node(tmp, 0, -1, false, false);
    }
 
    public long min(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return INF;
        if (l == tl && r == tr) {
            return atree[v].min;
        }
        propagate(v);
        int tm = (tl + tr) / 2;
        return Math.min(min(2 * v, tl, tm, l, Math.min(r, tm)),
                min(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r));
    }
 
    public void add(int v, int tl, int tr, int l, int r, long add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            if (atree[v].isSet) {
                atree[v].set += add;
                atree[v].min += add;
            } else {
                atree[v].min += add;
                atree[v].add += add;
                atree[v].isAdd = true;
            }
            return;
        }
        propagate(v);
        int tm = (tl + tr) / 2;
        add(2 * v, tl, tm, l, Math.min(r, tm), add);
        add(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, add);
        atree[v].min = Math.min(atree[2 * v].min, atree[2 * v + 1].min);
    }
 
    public void set(int v, int tl, int tr, int l, int r, long set) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            atree[v].set = set;
            atree[v].min = set;
            atree[v].add = 0;
            atree[v].isSet = true;
            atree[v].isAdd = false;
            return;
        }
        propagate(v);
        int tm = (tl + tr) / 2;
        set(2 * v, tl, tm, l, Math.min(tm, r), set);
        set(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, set);
        atree[v].min = Math.min(atree[2 * v].min, atree[2 * v + 1].min);
    }
 
    public void propagate(int v) {
        if (atree[v].isAdd) {
            atree[v].isAdd = false;
            if (atree[2 * v].isSet) {
                atree[2 * v].min += atree[v].add;
                atree[2 * v].set += atree[v].add;
            } else {
                atree[2 * v].add += atree[v].add;
                atree[2 * v].min += atree[v].add;
                atree[2 * v].isAdd = true;
            }
            if (atree[2 * v + 1].isSet) {
                atree[2 * v + 1].min += atree[v].add;
                atree[2 * v + 1].set += atree[v].add;
            } else {
                atree[2 * v + 1].add += atree[v].add;
                atree[2 * v + 1].min += atree[v].add;
                atree[2 * v + 1].isAdd = true;
            }
            atree[v].add = 0;
        }
        if (atree[v].isSet) {
            //isSet
            atree[v].isSet = false;
            atree[2 * v].isSet = true;
            atree[2 * v + 1].isSet = true;
            //Set
            atree[2 * v].set = atree[v].set;
            atree[2 * v + 1].set = atree[v].set;
            atree[v].set = -1;
            //reset
            atree[2 * v].add = 0;
            atree[2 * v].isAdd = false;
            atree[2 * v + 1].add = 0;
            atree[2 * v + 1].isAdd = false;
            atree[2 * v].min = atree[v].min;
            atree[2 * v + 1].min = atree[v].min;
        }
    }
 
    public void run() {
        try (MyScanner sc = new MyScanner(new File("rmq2.in"))) {
            try (PrintWriter pr = new PrintWriter(new File("rmq2.out"))) {
                int n = Integer.parseInt(sc.nextLine());
                int npow = pow(n);
                long[] a = new long[npow];
                atree = new Node[4 * n];
                for (int i = 0; i < n; i++) {
                    a[i] = sc.nextLong();
                }
                build(a, 1, 0, npow - 1, n);
                while (sc.hasNextLine()) {
                    int i, j;
                    long k;
                    String sin = sc.next();
                    i = sc.nextInt();
                    switch (sin) {
                        case "set":
                            j = sc.nextInt();
                            k = sc.nextLong();
                            set(1, 0, npow - 1, i - 1, j - 1, k);
                            break;
                        case "add":
                            j = sc.nextInt();
                            k = sc.nextLong();
                            add(1, 0, npow - 1, i - 1, j - 1, k);
                            break;
                        case "min":
                            j = sc.nextInt();
                            pr.println(min(1, 0, npow - 1, i - 1, j - 1));
                            break;
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("No file " + e.getMessage());
        } catch (Exception e) {
            System.out.println("Очень жаль: " + e.getMessage());
        }
    }
 
    public static void main(String[] args) {
        new C().run();
    }
}
