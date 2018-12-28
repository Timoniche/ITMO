import java.io.*;
import java.util.StringTokenizer;
 
public class D {
    //W - false (0), B - true (1)
    final static int INF = Integer.MAX_VALUE;
    final static int MINF = Integer.MIN_VALUE;
 
    static int[] sumN; //сумма черных отрезков
    static boolean[] isColN; //был ли сет
    static int[] countN; //количество отрезков
 
    static boolean[] LColor;
    static boolean[] RColor;
 
    static int xMin = INF;
    static int xMax = MINF;
    static int len;
 
    static class MyScanner implements AutoCloseable {
        static BufferedReader br;
        static StringTokenizer st;
 
        MyScanner(File inName) {
            try {
                br = new BufferedReader(new FileReader(inName));
            } catch (FileNotFoundException e) {
            }
        }
 
        String next() throws Exception {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }
 
        int nextInt() throws Exception {
            return Integer.parseInt(next());
        }
 
        public void close() throws Exception {
            br.close();
        }
    }
 
    public static void main(String[] args) throws Exception {
        MyScanner sc = new MyScanner(new File("painter.in"));
        PrintWriter pr = new PrintWriter(new File("painter.out"));
        final int n = sc.nextInt();
        boolean[] color = new boolean[n];
        int[] xArr = new int[n];
        int[] lArr = new int[n];
 
        int x, l;
        for (int i = 0; i < n; i++) {
            String sin = sc.next();
            x = sc.nextInt();
            l = sc.nextInt();
            lArr[i] = l;
            xArr[i] = x;
            if (x < xMin) {
                xMin = x;
            }
            if (x + l > xMax) {
                xMax = x + l;
            }
            switch (sin) {
                case "W":
                    color[i] = false;
                    break;
                case "B":
                    color[i] = true;
                    break;
            }
        }
        int delta = 1 - xMin;
        len = xMax - xMin;
 
        sumN = new int[4 * len];
        isColN = new boolean[4 * len];
        countN = new int[4 * len];
        LColor = new boolean[4 * len];
        RColor = new boolean[4 * len];
 
        for (int i = 0; i < n; i++) {
            int tmpX = xArr[i] + delta;
            if (color[i]) {
                //Black
                set(tmpX, tmpX + lArr[i] - 1, 1);
                pr.println(countN[1] + " " + sumN[1]);
            } else {
                //White
                set(tmpX, tmpX + lArr[i] - 1, 0);
                pr.println(countN[1] + " " + sumN[1]);
            }
        }
        pr.close();
        sc.close();
    }
 
    public static void set(int l, int r, int set) {
        setThis(1, 0, len - 1, l - 1, r - 1, set);
    }
 
    public static void setThis(int v, int tl, int tr, int l, int r, int set) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            sumN[v] = set * (tr - tl + 1);
            isColN[v] = true;
            countN[v] = set;
            LColor[v] = (set == 1);
            RColor[v] = (set == 1);
            return;
 
        }
        push(v, tl, tr);
        int tm = tl + (tr - tl) / 2;
        setThis(2 * v, tl, tm, l, Math.min(tm, r), set);
        setThis(2 * v + 1, tm + 1, tr, Math.max(l, tm + 1), r, set);
        sumN[v] = sumN[2 * v] + sumN[2 * v + 1];
        LColor[v] = LColor[2 * v];
        RColor[v] = RColor[2 * v + 1];
        //if (checkL(2 * v, tl, tm) && checkR(2 * v + 1, tm + 1, tr)) {
        if (RColor[2 * v] && LColor[2 * v + 1]) {
            countN[v] = countN[2 * v] + countN[2 * v + 1] - 1;
        } else {
            countN[v] = countN[2 * v] + countN[2 * v + 1];
        }
    }
 
//    private static boolean checkL(int v, int l, int r) {
//        if (l == r) {
//            return countN[v] != 0;
//        }
//        push(v, l, r);
//        int tm = l + (r - l) / 2;
//        return checkL(2 * v + 1, tm + 1, r);
//    }
//
//    private static boolean checkR(int v, int l, int r) {
//        if (l == r) {
//            return countN[v] != 0;
//        }
//        push(v, l, r);
//        int tm = l + (r - l) / 2;
//        return checkR(2 * v, l, tm);
//    }
 
    private static void push(int v, int tl, int tr) {
        if (isColN[v]) {
            int tm = tl + (tr - tl) / 2;
            isColN[v] = false;
            isColN[2 * v] = true;
            isColN[2 * v + 1] = true;
            if (countN[v] != 0) {
                countN[2 * v] = 1;
                countN[2 * v + 1] = 1;
                sumN[2 * v] = (tm - tl + 1);
                sumN[2 * v + 1] = tr - (tm + 1) + 1;
                LColor[2 * v] = true;
                RColor[2 * v] = true;
                LColor[2 * v + 1] = true;
                RColor[2 * v + 1] = true;
            } else {
                countN[2 * v] = 0;
                countN[2 * v + 1] = 0;
                sumN[2 * v] = 0;
                sumN[2 * v + 1] = 0;
                LColor[2 * v] = false;
                RColor[2 * v] = false;
                LColor[2 * v + 1] = false;
                RColor[2 * v + 1] = false;
            }
        }
    }
}
