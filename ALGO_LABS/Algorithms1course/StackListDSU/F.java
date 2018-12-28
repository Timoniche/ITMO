//package com.company;
import java.io.*;
 
public class F {
 
    class Node {
        int data;
        Node next;
        Node pred;
 
        public Node(int data, Node next, Node pred) {
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
 
 
    }
 
    public void run() throws IOException {
 
        String fileInName = "formation.in";
        String fileOutName = "formation.out";
 
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        BufferedReader buf = new BufferedReader(new FileReader(fileInName));
 
 
        String s = buf.readLine();
        int temp = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == ' ') {
                temp = i;
                break;
            }
        }
 
        int n = Integer.parseInt(s.substring(0, temp));
        int m = Integer.parseInt(s.substring(temp + 1));
        Node[] nodes = new Node[n];
        Node glava = new Node(0, null, null);
        nodes[0] = new Node(1, glava, glava);
        glava.setNext(nodes[0]);
        glava.setPred(nodes[0]);
 
        for (int i = 0; i < m; i++) {
            s = buf.readLine();
            if (s.charAt(2) == 'f') { //left
                String str = s.substring(5);
                for (int j = 0; j < str.length(); j++) {
                    if (str.charAt(j) == ' ') {
                        temp = j;
                        break;
                    }
                }
                int I = Integer.parseInt(str.substring(0, temp));
                int J = Integer.parseInt(str.substring(temp + 1));
                nodes[I - 1] = new Node(I, nodes[J - 1], nodes[J - 1].pred);
                nodes[J - 1].pred.setNext(nodes[I - 1]);
                nodes[J - 1].setPred(nodes[I - 1]);
            }
            else if (s.charAt(0) == 'r') { //right
                String str = s.substring(6);
                for (int j = 0; j < str.length(); j++) {
                    if (str.charAt(j) == ' ') {
                        temp = j;
                        break;
                    }
                }
                int I = Integer.parseInt(str.substring(0, temp));
                int J = Integer.parseInt(str.substring(temp + 1));
                nodes[I - 1] = new Node(I, nodes[J - 1].next, nodes[J - 1]);
                nodes[J - 1].next.setPred(nodes[I - 1]);
                nodes[J - 1].setNext(nodes[I - 1]);
 
            }
            else if (s.charAt(3) == 'v') { //leave
                String str = s.substring(6);
                int I = Integer.parseInt(str);
                nodes[I - 1].pred.setNext(nodes[I - 1].next);
                nodes[I - 1].next.setPred(nodes[I - 1].pred);
            }
            else { //name
                String str = s.substring(5);
                int I = Integer.parseInt(str);
                writer.print(nodes[I - 1].pred.data + " " + nodes[I - 1].next.data);
                writer.println();
            }
        }
 
        buf.close();
        writer.close();
    }
    public static void main(String[] args) throws IOException {
        new F().run();
    }
}
