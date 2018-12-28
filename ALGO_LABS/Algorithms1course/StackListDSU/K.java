//package com.company;
 
import java.io.*;
 
public class K {
 
    class Lead extends Node {
        Node mid;
 
        public Lead(int index, int data, Node next, Node pred, Node mid) {
            super(index, data, next, pred);
            this.mid = mid;
        }
 
        public void setMid(Node n) {
            mid = n;
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
        String fileInName = "kenobi.in";
        String fileOutName = "kenobi.out";
 
        PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
        BufferedReader buf = new BufferedReader(new FileReader(fileInName));
 
        String s = buf.readLine();
        int n = Integer.parseInt(s);
 
        Node[] nodes = new Node[n];
        Lead glava = new Lead(-1,0, null, null, null);
 
        for (int i = 0; i < n; i++) {
            s = buf.readLine();
 
            if (s.charAt(0) == 'a') { //add
                int temp = Integer.parseInt(s.substring(4));
                if (glava.data == 0) {
                    glava.setData(1);
                    nodes[i] = new Node(i, temp, glava, glava);
                    glava.setNext(nodes[i]);
                    glava.setPred(nodes[i]);
                    glava.setMid(nodes[i]);
                } else {
                    glava.setData(glava.data + 1);
                    nodes[i] = new Node(i, temp, glava, glava.pred);
                    glava.pred.setNext(nodes[i]);
                    glava.setPred(nodes[i]);
                    if (glava.data % 2 == 1) glava.setMid(glava.mid.next);
                }
            } else if (s.charAt(0) == 't') { //take
                if (glava.data > 0) {
                    glava.setData(glava.data - 1);
                    glava.pred.pred.setNext(glava);
                    glava.setPred(glava.pred.pred);
                    if (glava.data % 2 == 0) {
                        glava.setMid(glava.mid.pred);
                    }
                }
            } else { //mum!
                if (glava.data > 1) {
                    if (glava.data % 2 == 0) {
                        int med = glava.pred.index;
 
                        glava.pred.setNext(glava.next);
                        glava.next.setPred(glava.pred);
                        glava.setNext(glava.mid.next);
                        glava.mid.next.setPred(glava);
                        glava.mid.setNext(glava);
                        glava.setPred(glava.mid);
                        glava.setMid(nodes[med]);
 
                    } else {
                        glava.setMid(glava.mid.pred);
 
                        int med = glava.pred.index;
 
                        glava.pred.setNext(glava.next);
                        glava.next.setPred(glava.pred);
                        glava.setNext(glava.mid.next);
                        glava.mid.next.setPred(glava);
                        glava.mid.setNext(glava);
                        glava.setPred(glava.mid);
                        glava.setMid(nodes[med]);
                    }
                }
            }
        }
 
        writer.println(glava.data);
        if (glava.data != 0) {
            Node prob = glava.next;
            while (prob != glava) {
                writer.print(prob.data + " ");
                prob = prob.next;
            }
        }
 
        buf.close();
        writer.close();
    }
 
    public static void main(String[] args) throws IOException {
        new K().run();
    }
}
