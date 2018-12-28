import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.Random;
import java.util.StringTokenizer;
 
public class E {
 
    final static long MOD = 1000000000;
 
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
 
    static class Node {
        long key;
        int prior;
        long sum;
        Node left;
        Node right;
 
        public Node(long key, Random prior, long sum, Node left, Node right) {
            this.key = key;
            this.prior = prior.nextInt();
            this.sum = sum;
            this.left = left;
            this.right = right;
        }
 
        public Node(long key, int prior, long sum, Node left, Node right) {
            this.key = key;
            this.prior = prior;
            this.sum = sum;
            this.left = left;
            this.right = right;
        }
 
        public Node(long key, Random prior, long sum) {
            this.key = key;
            this.prior = prior.nextInt();
            this.sum = sum;
        }
 
        void countSum() {
            sum = key + sumOf(left) + sumOf(right);
        }
 
    }
 
    ;
 
    static Node root = null;
    static boolean wasEqualX = false;
 
    static long sumOf(Node node) {
        if (node == null) {
            return 0;
        }
        return node.sum;
    }
 
 
    static class Pair {
        Node first;
        Node second;
 
        public Pair(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }
 
    static Pair split(long x, Node in) {
        Pair tmp;
        if (in == null) {
            return new Pair(null, null);
        }
        if (x > in.key) {
            tmp = split(x, in.right);
            in.right = tmp.first;
            tmp.first = in;
            tmp.first.countSum();
            return tmp;
        } else {
            if (x == in.key) {
                wasEqualX = true;
            }
            tmp = split(x, in.left);
            in.left = tmp.second;
            tmp.second = in;
            tmp.second.countSum();
            return tmp;
        }
    }
 
    static Node merge(Node n1, Node n2) {
        Node ans;
        if (n1 == null) {
            return n2;
        }
        if (n2 == null) {
            return n1;
        }
        if (n1.prior > n2.prior) {
            n1.right = merge(n1.right, n2);
            ans = new Node(n1.key, n1.prior, 1, n1.left, n1.right);
        } else {
            n2.left = merge(n1, n2.left);
            ans = new Node(n2.key, n2.prior, 1, n2.left, n2.right);
        }
        ans.countSum();
        return ans;
    }
 
    static Node insert(long x) {
        Pair tmp = split(x, root);
        if (wasEqualX) {
            return root = merge(tmp.first, tmp.second);
        }
        return root = merge(merge(tmp.first, new Node(x, new Random(), x)), tmp.second);
    }
 
    static long sum(long l, long r) {
        Pair tmp = split(l, root);
        Pair tmp2 = split(r + 1, tmp.second);
        root = merge(merge(tmp.first, tmp2.first), tmp2.second);
        return sumOf(tmp2.first);
    }
 
    public static void main(String[] args) throws Exception {
        try (MyScanner sc = new MyScanner(System.in)) {
            int n = sc.nextInt();
            String s;
            long in;
            long l, r;
            long lastAns = 0;
            boolean lastWasAsk = false;
            for (int i = 0; i < n; i++) {
                s = sc.next();
                switch (s.charAt(0)) {
                    case '+':
                        in = sc.nextLong();
                        wasEqualX = false;
                        if (!lastWasAsk) {
                            insert(in);
                        } else {
                            insert((in + lastAns) % MOD);
                        }
                        lastWasAsk = false;
                        break;
                    case '?':
                        l = sc.nextLong();
                        r = sc.nextLong();
                        lastAns = sum(l, r);
                        System.out.println(lastAns);
                        lastWasAsk = true;
                    default:
                        break;
                }
            }
        }
    }
}
