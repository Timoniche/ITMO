import java.io.*;
public class G {
    class Lead extends Node {
        Node mid;
  
        public Lead(int data, Node next, Node pred, Node mid) {
            super(data, next, pred);
            this.mid = mid;
        }
  
        public void setMid(Node n) {
            mid = n;
        }
    }
  
    class Node {
        int data;
        Node next;
        Node pred;
  
        public Node(int data, Node next, Node pred) {
            this.data = data;
            this.next = next;
            this.pred = pred;
        }
  
        public int getData() {
            return data;
        }
  
        public void setNext(Node n) {
            next = n;
        }
  
        public void setPred(Node n) {
            pred = n;
        }
  
        public void setData(int e) {
            data = e;
        }
  
    }
  
    private  void run() throws IOException {
        String fileInName = "hospital.in";
        String fileOutName = "hospital.out";
  
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        BufferedReader buf = new BufferedReader(new FileReader(fileInName));
  
        String s = buf.readLine();
        int n = Integer.parseInt(s);
  
        Lead glava = new Lead(0, null, null, null); //data - size
        Node[] nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            s = buf.readLine();
             
            if (s.charAt(0) == '+') {
                int temp = Integer.parseInt(s.substring(2));
                if (glava.data == 0) {
                    glava.setData(1);
                    nodes[i] = new Node(temp, glava, glava);
                    glava.setNext(nodes[i]);
                    glava.setPred(nodes[i]);
                    glava.setMid(nodes[i]);
                } else {
                    glava.setData(glava.data + 1);
                    nodes[i] = new Node(temp, glava, glava.pred);
                    glava.pred.setNext(nodes[i]);
                    glava.setPred(nodes[i]);
                    if (glava.data % 2 == 1) glava.setMid(glava.mid.next);
                }
            }
             
            if (s.charAt(0) == '*') {
                int temp = Integer.parseInt(s.substring(2));
                if (glava.data == 0) {
                    glava.setData(1);
                    nodes[i] = new Node(temp, glava, glava);
                    glava.setNext(nodes[i]);
                    glava.setPred(nodes[i]);
                    glava.setMid(nodes[i]);
                } else {
                    glava.setData(glava.data + 1);
                    nodes[i] = new Node(temp, glava.mid.next, glava.mid);
                    glava.mid.next.setPred(nodes[i]);
                    glava.mid.setNext(nodes[i]);
                    if (glava.data % 2 == 1) {
                        glava.setMid(nodes[i]);
                    }
                }
            }
             
            if (s.charAt(0) == '-') {
                glava.setData(glava.data - 1);
                writer.print(glava.next.getData());
                writer.println();
                glava.next.next.setPred(glava);
                glava.setNext(glava.next.next);
                if (glava.data % 2 == 1) {
                    glava.setMid(glava.mid.next);
                }
            }
        }
        buf.close();
        writer.close();
    }
  
    public static void main(String[] args) throws IOException {
       new G().run();
    }
}
