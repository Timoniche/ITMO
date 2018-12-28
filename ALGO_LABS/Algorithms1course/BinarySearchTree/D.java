import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;
import java.util.StringTokenizer;
 
public class D {
    //5 4
    //3 3 4 1 3
    //Ans: 6
    //4 0 5 2 3 1
 
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
 
    static class Node {
        int value;
        int prior;
        int weight;
        int zeroAmount;
        Node left;
        Node right;
 
        public Node(int value, int prior, int weight, int zeroAmount, Node left, Node right) {
            this.value = value;
            this.prior = prior;
            this.weight = weight;
            this.zeroAmount = zeroAmount;
            this.left = left;
            this.right = right;
        }
 
        public Node(int value, Random prior) {
            this.value = value;
            this.prior = prior.nextInt();
            this.weight = 1;
            if (value == 0) {
                this.zeroAmount = 1;
            } else {
                this.zeroAmount = 0;
            }
            this.left = null;
            this.right = null;
        }
 
        void reCount() {
            weight = weightOf(left) + weightOf(right) + 1;
            if (value == 0) {
                zeroAmount = zerosOf(left) + zerosOf(right) + 1;
            } else {
                zeroAmount = zerosOf(left) + zerosOf(right);
            }
        }
 
    }
 
    static Node root = null;
    static ArrayList<Integer> ans = new ArrayList<>();
    static int maxIndex;
 
    static int weightOf(Node node) {
        if (node == null) {
            return 0;
        }
        return node.weight;
    }
 
    static int zerosOf(Node node) {
        if (node == null) {
            return 0;
        }
        return node.zeroAmount;
    }
 
    static class pairNodes {
        Node first;
        Node second;
 
        public pairNodes(Node first, Node second) {
            this.first = first;
            this.second = second;
        }
    }
 
    static pairNodes split(int x, Node in) {
        if (in == null) {
            return new pairNodes(null, null);
        }
        int pref = weightOf(in.left);
        if (pref >= x) {
            pairNodes tmp = split(x, in.left);
            in.left = tmp.second;
            in.reCount();
            return new pairNodes(tmp.first, in);
        } else {
            pairNodes tmp = split(x - pref - 1, in.right);
            in.right = tmp.first;
            in.reCount();
            return new pairNodes(in, tmp.second);
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
            ans = new Node(n1.value, n1.prior, 1, n1.zeroAmount, n1.left, n1.right);
        } else {
            n2.left = merge(n1, n2.left);
            ans = new Node(n2.value, n2.prior, 1, n2.zeroAmount, n2.left, n2.right);
        }
        ans.reCount();
        return ans;
    }
 
    static void insertInitial(int L) {
        pairNodes tmp = split(L - 1, root);
        root = merge(merge(tmp.first, new Node(0, new Random())), tmp.second);
    }
 
    static void insert(int L, int value) {
        pairNodes tmp = split(L - 1, root);
        pairNodes tmp2 = split(1, tmp.second);
 
        if (tmp2.first.value == 0) {
            if (L > maxIndex) {
                maxIndex = L;
            }
            root = merge(merge(tmp.first, new Node(value, new Random())), tmp2.second);
        } else {
            int zeroPosition = rightZeroIndex(tmp2.second);
            if (L + zeroPosition + 1 > maxIndex) {
                maxIndex = L + zeroPosition + 1;
            }
            pairNodes tmp3 = split(zeroPosition, tmp2.second);
            pairNodes tmp4 = split(1, tmp3.second);
            root = merge(merge(merge(tmp.first, new Node(value, new Random())), tmp2.first), merge(tmp3.first, tmp4.second));
        }
    }
 
    static int rightZeroIndex(Node in) {
        if (in.left != null) {
            if (in.left.zeroAmount == 0) {
                if (in.value == 0) {
                    return weightOf(in.left);
                } else {
                    return weightOf(in.left) + 1 + rightZeroIndex(in.right);
                }
            } else {
                return rightZeroIndex(in.left);
            }
        } else {
            if (in.value == 0) {
                return 0;
            } else {
                //weightOf(in.left) == 0;
                return 1 + rightZeroIndex(in.right);
            }
        }
    }
 
    static void traversal(Node node) {
        if (node != null) {
            traversal(node.left);
            ans.add(node.value);
            traversal(node.right);
        }
    }
 
    public static void main(String[] args) throws Exception {
        try (MyScanner sc = new MyScanner(System.in)) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            maxIndex = n;
            // (n + m) initial elements
            for (int i = 1; i <= n + m + 1; i++) {
                insertInitial(i);
            }
            for (int i = 1; i <= n; i++) {
                int L = sc.nextInt();
                insert(L, i);
            }
            traversal(root);
            System.out.println(maxIndex);
            for (int i = 0; i < maxIndex; i++) {
                System.out.print(ans.get(i) + " ");
            }
 
        }
    }
}
