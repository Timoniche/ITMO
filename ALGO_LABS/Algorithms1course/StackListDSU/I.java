import java.io.*;
public class I {
 
    public static void main(String[] args) {
        try {
            String fileInName = "hemoglobin.in";
            String fileOutName = "hemoglobin.out";
 
            PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
            BufferedReader buf = new BufferedReader(new FileReader(fileInName));
 
            int[] stek = new int[50000];
            int y = 0;//указатель на стек
 
            String s = buf.readLine();
            int n = Integer.parseInt(s);
 
            for (int i = 0; i < n; i++) {
                s = buf.readLine();
                if (s.charAt(0) == '+') {
                    stek[y++] = Integer.parseInt(s.substring(1));
                }
                if (s.charAt(0) == '?') {
                    int k = Integer.parseInt(s.substring(1));
                    int sum = 0;
                    for (int j = y-1; j > y-1-k; j--) {
                        sum += stek[j];
                    }
                    writer.print(sum);
                    writer.println();
                }
                if (s.charAt(0) == '-') {
                    writer.print(stek[y-1]);
                    writer.println();
                    y--;
                }
            }
 
            buf.close();
            writer.close();
 
        } catch (IOException exc) {
 
        }
    }
}
