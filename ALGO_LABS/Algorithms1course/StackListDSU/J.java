//package com.company;
 
import java.io.*;
import java.util.*;
 
public class J {
 
    class FastScanner {
        BufferedReader br;
        StringTokenizer st;
 
        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
 
        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
 
    class Node {
        int index;
        int data;
        Node next;
        Node pred;
 
        public Node(int index, int data, Node next, Node pred) {
            this.index = index;
            this.data = data;
            this.next = next;
            this.pred = pred;
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
 
    public void run() throws IOException {
        String fileInName = "bureaucracy.in";
        String fileOutName = "bureaucracy.out";
 
        File file = new File(fileInName);
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        FastScanner sc = new FastScanner(file);
 
        int n = sc.nextInt();
        int m = sc.nextInt();
 
        Node[] nodes = new Node[n];
        Node glava = new Node(-1, 0, null, null);
 
        glava.setData(n);
        for (int i = 0; i < n; i++) {
            int temp = sc.nextInt();
            if (i == 0) {
                nodes[i] = new Node(i, temp, glava, glava);
                glava.setNext(nodes[i]);
                glava.setPred(nodes[i]);
            } else {
                nodes[i] = new Node(i, temp, glava, glava.pred);
                glava.pred.setNext(nodes[i]);
                glava.setPred(nodes[i]);
            }
        }
 
        int e = m/n;
 
        Node prob;
        while (e >= 1) {
            m -= e * glava.data;
            prob = glava.next;
            while (prob != glava) {
                if (prob.data > e) {
                    prob.setData(prob.data - e);
                } else {
                    m += e - prob.data;
                    prob.pred.setNext(prob.next);
                    prob.next.setPred(prob.pred);
                    glava.setData(glava.data - 1);
                }
                prob = prob.next;
            }
            if (glava.data == 0) break;
            e = m/glava.data;
        }
 
        if (glava.data != 0) {
 
            prob = glava.next;
            while (prob != glava && m != 0 && glava.data != 0) {
                m--;
                prob.setData(prob.data - 1);
                if (prob.data == 0) {
                    prob.pred.setNext(prob.next);
                    prob.next.setPred(prob.pred);
                    prob = prob.next;
                    glava.setData(glava.data - 1);
                } else if (glava.data > 1){
                    prob.pred.setNext(prob.next);
                    prob.next.setPred(prob.pred);
                    int g = prob.next.index;
 
                    prob.setPred(glava.pred);
                    prob.setNext(glava);
                    glava.pred.setNext(prob);
                    glava.setPred(prob);
                    prob = nodes[g];
                } else {
                    int temp = prob.data - m;
                    if (temp > 0) {
                        prob.setData(temp);
                        m = 0;
                    }
                    else glava.setData(0);
                }
 
            }
        }
 
 
        if (glava.data != 0) {
            writer.println(glava.data);
            prob = glava.next;
            while (prob != glava) {
                writer.print(prob.data + " ");
                prob = prob.next;
            }
        } else {
            writer.print(-1);
        }
 
        writer.close();
    }
 
    public static void main(String[] args) throws IOException {
        new J().run();
    }
}
