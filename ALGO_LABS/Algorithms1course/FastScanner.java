import java.util.*;
import java.io.*;

public class FastScanner implements AutoCloseable {
    BufferedReader br;
    StringTokenizer st;

    FastScanner(InputStream is) {
        br = new BufferedReader(new InputStreamReader(is));
    }

    FastScanner(File inName) {
        try {
            br = new BufferedReader(new FileReader(inName));
        } catch (FileNotFoundException e) {
        }
    }

    String next() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
            }
        }
        return st.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(next());
    }

    long nextLong() {
        return Long.parseLong(next());
    }

    double nextDouble() {
        return Double.parseDouble(next());
    }

    public void close() throws Exception {
        br.close();
    }
}
