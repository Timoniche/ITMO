//package com.company;
 
import java.io.*;
import java.util.PriorityQueue;
import java.util.Scanner;
 
public class D {
 
    public static void main(String[] args) {
        try {
            String fileInName = "stack-min.in";
            String fileOutName = "stack-min.out";
 
            File file = new File(fileInName);
            PrintWriter writer = new PrintWriter(new FileWriter(fileOutName));
            BufferedReader buf = new BufferedReader(new FileReader(fileInName));
            int[] stek = new int[1000000];
            int[] min = new int[1000000];
 
            int k = 0;
            int n = Integer.parseInt(buf.readLine());
            for (int i = 0; i < n; i++) {
                String s = buf.readLine();
                int a = Integer.parseInt(s.substring(0, 1));
                if (a == 1) {
                    int b = Integer.parseInt(s.substring(2));
                    if (k == 0) min[k] = b;
                    else {
                        if (b < min[k - 1]) min[k] = b;
                        else min[k] = min[k - 1];
                    }
                    stek[k++] = b;
                }
                if (a == 2) {
                    k--;
                }
                if (a == 3) {
                   writer.println(min[k-1]);
                }
            }
 
            buf.close();
            writer.close();
 
        } catch (IOException exc) {
 
        }
    }
}
