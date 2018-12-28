import java.io.*;
 
public class E {
    class Node {
        int lead;
        int min;
        int max;
        int rank;
 
        public Node(int lead, int min, int max, int rank) {
            this.lead = lead;
            this.min = min;
            this.max = max;
            this.rank = rank;
        }
    }
 
    public int find (int v, Node[] trees) {
        if (v == trees[v].lead)
            return v;
        return trees[v].lead = find(trees[v].lead, trees);
    }
 
    public void union(int a, int b, Node[] trees) {
        int temp1 = find(a, trees);
        int temp2 = find(b, trees);
        if (temp1 != temp2) {
            if (trees[temp1].rank < trees[temp2].rank) {
                int temp = temp2;
                temp2 = temp1;
                temp1 = temp;
            }
            if (trees[temp1].max < trees[temp2].max) {
                trees[temp1].max = trees[temp2].max;
            }
            if (trees[temp1].min > trees[temp2].min) {
                trees[temp1].min = trees[temp2].min;
            }
             
            trees[temp1].rank += trees[temp2].rank;
            trees[temp2].lead = temp1; 
        }
    }
 
    private void run() throws  IOException {
 
        String fileInName = "dsu.in";
        String fileOutName = "dsu.out";
 
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        BufferedReader buf = new BufferedReader(new FileReader(fileInName));
 
        String s = buf.readLine();
        int n = Integer.parseInt(s);
 
        Node[] trees = new Node[n];
        for (int i = 0; i < n; i++) {
            trees[i] = new Node(i, i+1, i+1, 1);
        }
 
        while (buf.ready()) {
            s = buf.readLine();
            if (s.charAt(0)=='u') {
                String temp = s.substring(6);
                int k = 0;
                for (int i = 0; i < temp.length(); i++) {
                    if (temp.charAt(i) == ' ') {
                        k = i;
                        break;
                    }
                }
                int a = Integer.parseInt(temp.substring(0, k));
                a--;
                int b = Integer.parseInt(temp.substring(k+1));
                b--;
 
                union(a, b, trees);
            } else {
                int a = Integer.parseInt(s.substring(4));
                a--;
                int temp = find(a, trees);
                writer.print(trees[temp].min + " " + trees[temp].max + " " + trees[temp].rank);
                writer.println();
            }
        }
 
 
 
        buf.close();
        writer.close();
    }
 
    public static void main(String[] args) throws IOException {
        new E().run();
    }
}
