import java.io.*;
import java.util.*;
 
public class G {
    private final static int INF = Integer.MAX_VALUE;
    private final static int MINF = Integer.MIN_VALUE;
 
    static int yMin = INF;
    static int yMax = MINF;
    static int len;
    private static Node[] atree;
    static int xAns, yAns, cAns = MINF;
 
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
        int max;
        int add;
        boolean isAdd;
 
        public Node(int max, int add, boolean isAdd) {
            this.max = max;
            this.add = add;
            this.isAdd = isAdd;
        }
    }
 
    static class SquareX {
        int key; //1 - open -1 - close
        int x;
        int yUp;
        int yDown;
 
        public SquareX(int key, int x, int yUp, int yDown) {
            this.key = key;
            this.x = x;
            this.yUp = yUp;
            this.yDown = yDown;
        }
 
 
    }
 
    public static void main(String[] args) {
        try (MyScanner sc = new MyScanner(System.in)) {
            int n = sc.nextInt();
            SquareX[] squares = new SquareX[2 * n];
 
            int x1, y1, x2, y2;
            int k = 0; //счетчик squares
            for (int i = 0; i < n; i++) {
                x1 = sc.nextInt();
                y1 = sc.nextInt();
                updateM(y1);//
                x2 = sc.nextInt();
                y2 = sc.nextInt();
                updateM(y2);//
                squares[k++] = new SquareX(1, x1, y1, y2);
                squares[k++] = new SquareX(-1, x2, y1, y2);
            }
            int delta = 1 - yMin;
            len = yMax - yMin + 1;
            atree = new Node[4 * len];
            build(1, 0, len - 1);
            //O(N * logN)
            Arrays.sort(squares, (o1, o2) -> {
                        int tmp = o1.x - o2.x;
                        if (tmp != 0) {
                            return tmp;
                        } else {
                            return o2.key - o1.key;
                        }
                    }
            );
 
            for (int i = 0; i < 2 * n; i++) {
                SquareX sq = squares[i];
                add(1, 0, len - 1, sq.yUp - 1 + delta, sq.yDown - 1 + delta, sq.key);
                if (atree[1].max > cAns) {
                    cAns = atree[1].max;
                    xAns = sq.x;
                    yAns = searchY(1, 0, len - 1);
                }
 
            }
            System.out.println(cAns);
            System.out.println(xAns + " " + (yAns + 1 - delta));
 
        } catch (Exception e) {
            System.out.println("What a pity, you loose");
            e.printStackTrace();
        }
    }
 
    private static int searchY(int v, int l, int r) {
        if (l == r) {
            return l;
        }
        push(v);
        int tm = (l + r) / 2;
 
        if (atree[2 * v].max == atree[v].max) {
            return searchY(2 * v, l, tm);
        } else {
            return searchY(2 * v + 1, tm + 1, r);
        }
    }
 
    private static void updateM(int y) {
        if (y > yMax) {
            yMax = y;
        }
        if (y < yMin) {
            yMin = y;
        }
    }
 
    static void build(int v, int tl, int tr) {
        if (tl == tr) {
            atree[v] = new Node(0, 0, false); //изначально оно все белое
            return;
        }
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        atree[v] = new Node(0, 0, false);
    }
 
    static void add(int v, int tl, int tr, int l, int r, int add) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            atree[v].isAdd = true;
            atree[v].add += add;
            atree[v].max += add;
            return;
        }
        push(v);
        int tm = (tl + tr) / 2;
        add(2 * v, tl, tm, l, Math.min(r, tm), add);
        add(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, add);
        atree[v].max = Math.max(atree[2 * v].max, atree[2 * v + 1].max);
    }
 
    static void push(int v) {
        if (atree[v].isAdd) {
            atree[v].isAdd = false;
            atree[2 * v].isAdd = true;
            atree[2 * v + 1].isAdd = true;
 
            atree[2 * v].max += atree[v].add;
            atree[2 * v + 1].max += atree[v].add;
 
            atree[2 * v].add += atree[v].add;
            atree[2 * v + 1].add += atree[v].add;
 
            atree[v].add = 0;
        }
    }
}
