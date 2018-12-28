import java.util.ArrayList;
import java.util.Scanner;

public class C {
    private static Scanner sc = new Scanner(System.in);
    private static ArrayList<Integer> out = new ArrayList<>();

    private static int binSearch(int i) {
        int l = -1;
        int r = out.size();
        int m;
        while (r > l + 1) {
            System.out.flush();
            m = l + (r - l) / 2;
            System.out.println("1" + " " + out.get(m)
                    + " " + i);
            String sIn = sc.next();
            if (sIn.equals("YES")) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    }

    public static void main(String[] args) {

        int n = sc.nextInt();
        out.add(1);
        for (int i = 2; i <= n; i++) {
            int insertI = binSearch(i);
            out.add(insertI, i);
        }
        System.out.flush();
        System.out.print("0 ");
        for (int i = 0; i < n; i++) {
            System.out.print(out.get(i) + " ");
        }
    }
}
