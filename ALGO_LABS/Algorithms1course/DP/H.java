import java.util.*;
 
public class H {
    final int INF = 100_000;
    Scanner sc = new Scanner(System.in);
    final int n = sc.nextInt();
    int[] vhod = new int[n];
    int[] ans = new int[n];
 
    public ArrayList<Integer> giveArr (int index) {
        ArrayList<Integer> arr = new ArrayList<>();
 
        for (int i = 0; i < n; i++) {
            if (vhod[i] == index + 1) {
                arr.add(i);
            }
        }
 
        return arr;
    }
 
    public ArrayList<Integer> anSearch (int index) {
        ArrayList<Integer> arr = new ArrayList<>();
 
        for (int i = 0; i < n; i++) {
            if (vhod[i] == index + 1) {
                arr.add(i);
            }
        }
 
        if (arr.size() == 0) {
            ans[index] = 1;
            return arr;
        }
 
        for (int i = 0; i < arr.size(); i++) {
            anSearch(arr.get(i));
        }
 
        int temp = 0;
        int temp2 = 0;
        for (int i = 0; i < arr.size(); i++) {
            temp += ans[arr.get(i)];
            ArrayList<Integer> arr2 = giveArr(arr.get(i));
            for (int j = 0; j < arr2.size(); j++) {
                temp2 += ans[arr2.get(j)];
            }
        }
 
        ans[index] = Math.max(1 + temp2, temp);
 
        return arr;
    }
 
    public void run() {
 
        int glava = 0;
        for (int i = 0; i < n; i++) {
            vhod[i] = sc.nextInt();
            if (vhod[i] == 0) {
                glava = i;
            }
        }
 
        anSearch(glava);
        System.out.print(ans[glava]);
 
    }
 
    public static void main(String[] args) {
        new H().run();
    }
}
