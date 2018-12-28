import java.io.*;
import java.util.*;
 
public class A {
 
    public void run () throws IOException {
        String fileInName = "input.txt";
        String fileOutName = "output.txt";
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        Scanner sc = new Scanner(file);
        int n = sc.nextInt();
        int k = sc.nextInt();
        int[] arr = new int[n];
        arr[0] = 0;
        arr[n - 1] = 0;
        for (int i = 1; i < n - 1; i++) {
            arr[i] = sc.nextInt();
        }
        int[] d = new int[n];
        int[] helper = new int[n];
        d[0] = 0;
        helper[0] = -1;
 
        for (int i = 1; i < n; i++) {
            if (k <= i) {
                int max = i - k;
                for (int j = 1; j < k; j++) {
                    if (d[i - j] > d[max]) {
                        max = i - j;
                    }
                }
                d[i] = d[max] + arr[i];
                helper[i] = max;
            } else {
                int max = 0;
                for (int j = 1; j < i; j++) {
                    if (d[i - j] > d[max]) {
                        max = i - j;
                    }
                }
                d[i] = d[max] + arr[i];
                helper[i] = max;
            }
        }
        int[] ans = new int[n];
        int start = n - 1;
        int y = n - 1; //указатель на последний элемент
        while (helper[start] != -1) {
            ans[y--] = start + 1;
            start = helper[start];
        }
        ans[y] = 1;
 
        writer.println(d[n - 1]);
        writer.println(n - y - 1);
     
        for (int i = y; i < n; i++) {
            writer.print(ans[i] + " ");
        }
        writer.println();
        writer.close();
    }
    public static void main(String[] args) throws IOException {
        new A().run();
    }
}
