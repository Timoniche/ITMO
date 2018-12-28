import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;
 
public class L {
    final static long INF = 1_000_000;
 
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
    }
 
    public class Node {
        long min;
 
        public Node(long min) {
            this.min = min;
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
 
    public void build(int v, int tl, int tr, Node[] atree, int n) {
        if (tl == tr) {
            if (tl < n) {
                atree[v] = new Node(tl);
            } else {
                atree[v] = new Node(INF);
            }
            return;
        }
        int tm = tl + (tr - tl) / 2;
        build(2 * v, tl, tm, atree, n);
        build(2 * v + 1, tm + 1, tr, atree, n);
        long tmp = Math.min(atree[2 * v].min, atree[2 * v + 1].min);
        atree[v] = new Node(tmp);
    }
 
    public static long enterR(int v, int tl, int tr, int l, int r, Node[] atree) {
        if (l > r)
            return INF;
        if (l == tl && r == tr)
            return atree[v].min;
        int tm = (tl + tr) / 2;
        return Math.min(enterR(2 * v, tl, tm, l, Math.min(r, tm), atree),
                enterR(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, atree));
    }
 
    public void set(int v, int tl, int tr, long pos, long val, Node[] atree) {
        if (tl == tr)
            atree[v].min = val;
        else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                set(2 * v, tl, tm, pos, val, atree);
            else
                set(2 * v + 1, tm + 1, tr, pos, val, atree);
            long tmp = Math.min(atree[2 * v].min, atree[2 * v + 1].min);
            atree[v] = new Node(tmp);
        }
    }
 
    public void run() {
        try {  //0 - occupied, 1 - available
            MyScanner sc = new MyScanner(new File("parking.in"));
            try (PrintWriter pr = new PrintWriter(new File("parking.out"))) {
                int n = Integer.parseInt(sc.next());
                int npow = pow(n);
                Node[] atree = new Node[4 * n];
                int m = Integer.parseInt(sc.next());
                build(1, 0, npow - 1, atree, n);
                for (int i = 0; i < m; i++) {
                    if (sc.next().equals("enter")) {
                        int tmp = Integer.parseInt(sc.next());
                        long ent = enterR(1, 0, npow - 1, tmp - 1, npow - 1, atree);
                        if (ent == INF) {
                            pr.println(atree[1].min + 1);
                            set(1, 0, npow - 1, atree[1].min, INF, atree);
                        } else {
                            pr.println(ent + 1);
                            set(1, 0, npow - 1, ent, INF, atree);
                        }
                    } else { //"exit"
                        int tmp = Integer.parseInt(sc.next());
                        set(1, 0, npow - 1, tmp - 1, tmp - 1, atree);
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("No file " + e.getMessage());
        }
    }
 
    public static void main(String[] args) {
        new L().run();
    }
}
