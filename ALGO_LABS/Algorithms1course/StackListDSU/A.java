import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
 
public class A {
 
    private void run() throws IOException {
        String fileInName = "decode.in";
        String fileOutName = "decode.out";
 
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        Scanner sc = new Scanner(file);
        String s = sc.nextLine();
 
        char[] code = new char[200000];
        int k = 0; //указатель в массиве
 
        for (int i = 0; i < s.length(); i++) {
            code[k] = s.charAt(i);
            while ((k > 0) && (code[k] == code[k-1])) {
                k -= 2;
            }
            k++;
        }
 
        for (int i = 0; i < k; i++) {
            writer.print(code[i]);
        }
 
        sc.close();
        writer.close();
    }
 
    public static void main(String[] args) throws IOException {
        try {
            new A().run();
        } catch (IOException e) {
            e.printStackTrace();
        }
 
    }
}
