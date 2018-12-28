import java.util.*;
 
public class B {
 
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        int[] d = new int[n];
        int[] otv = new int[n];
        for (int i = 0; i < n; i++) {
            d[i] = 1;
            otv[i] = -1;
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i] && d[j] + 1 > d[i]) {
                    d[i] = d[j] + 1;
                    otv[i] = j;
                }
            }
        }
        int ans = 0;
        int maxd = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] > d[maxd]) {
                maxd = i;
            }
            ans = Math.max(ans, d[i]);
        }
        for (int i = 0; i < n; i++) {
            if (otv[i] != -1) {
 
            }
        }
 
        int[] vihod = new int[n];
        int y = n - 1; //указатель на последний элемент
        System.out.println(ans);
        while (otv[maxd] != -1) {
            vihod[y--] = arr[maxd];
            maxd = otv[maxd];
        }
        vihod[y] = arr[maxd];
        for (int i = y; i < n; i++) {
            System.out.print(vihod[i] + " ");
        }
    }
}
