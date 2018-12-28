import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
 
public class B {
 
    private void run() throws IOException {
        String fileInName = "brackets.in";
        String fileOutName = "brackets.out";
 
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        Scanner sc = new Scanner(file);
        String s = sc.nextLine();
 
        boolean flag = false;
        char[] stek = new char[10000];
        int k = 0; //счетчик стека
 
        for (int i = 0; i < s.length(); i++) {
            char temp = s.charAt(i);
 
            if (temp == '(' || temp == '[' || temp == '{') {
                stek[k++] = temp;
            } else if (k == 0){
                flag = true;
                break;
            } else {
                if (temp == ')') {
                    if (stek[k-1] != '(') {
                        flag = true;
                        break;
                    } else k--;
 
                }
                if (temp == ']') {
                    if (stek[k-1] != '[') {
                        flag = true;
                        break;
                    } else k--;
                }
                if (temp == '}') {
                    if (stek[k-1] != '{') {
                        flag = true;
                        break;
                    } else k--;
                }
            }
        }
 
        if (flag || k != 0) writer.print("NO");
        else writer.print("YES");
 
        sc.close();
        writer.close();
    }
 
    public static void main(String[] args) throws IOException {
        try {
            new B().run();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
