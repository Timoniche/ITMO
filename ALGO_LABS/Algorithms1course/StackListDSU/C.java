import java.io.*;
import java.util.Scanner;
 
public class C {
 
    public static void main(String[] args) {
        try {
            String fileInName = "postfix.in";
            String fileOutName = "postfix.out";
 
            File file = new File(fileInName);
            PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
            Scanner sc = new Scanner(file);
 
            int[] stek = new int[200];
            int k = 0; //указатель на стек
 
            while (sc.hasNext()) {
                String s = sc.next();
                char a = s.charAt(0);
 
                if (Character.isDigit(a)) {
                    stek[k++] = Integer.parseInt(s);
                } else {
                    if (a == '+') {
                        int temp = stek[k-1] + stek[k-2];
                        k -= 2;
                        stek[k++] = temp;
                    }
                    if (a == '-') {
                        int temp = stek[k-2] - stek[k-1];
                        k -= 2;
                        stek[k++] = temp;
                    }
                    if (a == '*') {
                        int temp = stek[k-1] * stek[k-2];
                        k -= 2;
                        stek[k++] = temp;
                    }
                }
            }
            writer.print(stek[k-1]);
 
            sc.close();
            writer.close();
 
        } catch (IOException exc) {
 
        }
    }
}
