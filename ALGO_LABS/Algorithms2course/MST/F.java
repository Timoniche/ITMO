import java.util.*;

public class F {

    class Pair {
        int first;
        int second;

        public Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }

        @Override
        public boolean equals(Object o) {
            Pair pair = (Pair) o;
            return first == pair.first &&
                    second == pair.second;
        }

        @Override
        public int hashCode() {
            return first * 341 + second * 253;
        }
    }

    HashSet<Pair> set_ans = new HashSet<>();

    final static int MAXN = 20000;
    static int[] colored = new int[MAXN];
    static boolean[] wasHere = new boolean[MAXN];

    class Graph {
        int n, m;
        ArrayList<Integer>[] adj = new ArrayList[MAXN];
        ArrayDeque<Integer> topsort;

        public Graph(int n, int m) {
            this.n = n;
            this.m = m;
            topsort = new ArrayDeque<>(n);
        }

        void dfs(int v) {
            wasHere[v] = true;
            for (int u : adj[v]) {
                if (!wasHere[u]) dfs(u);
            }
            topsort.addFirst(v);
        }

        void dfs_color_components(int v, int color) {
            wasHere[v] = true;
            colored[v] = color;
            for (int u : adj[v]) {
                if (!wasHere[u]) dfs_color_components(u, color);
            }
        }

    };

    void run() {
        int n, m;
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt(); m = sc.nextInt();
        Graph g = new Graph(n, m);
        Graph g_t = new Graph(n, m);
        for (int i = 0; i < n; i++) {
            g.adj[i] = new ArrayList<>();
            g_t.adj[i] = new ArrayList<>();
        }
        for (int i = 0; i < m; i++) {
            int u = sc.nextInt(), v = sc.nextInt();
            g.adj[u - 1].add(v - 1);
            g_t.adj[v - 1].add(u - 1);
        }
        for (int i = 0; i < n; i++) {
            wasHere[i] = false;
        }

        for (int i = 0; i < n; i++) {
            if (!wasHere[i]) g.dfs(i);
        }

        for (int i = 0; i < n; i++) {
            wasHere[i] = false;
        }
        int color = 0;
        for (int i = 0; i < n; i++) {
            colored[i] = -1;
        }
        for (int u : g.topsort) {
            if (!wasHere[u]) {
                g_t.dfs_color_components(u, color++);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int u : g.adj[i]) {
                if (colored[i] != colored[u]) {
                    set_ans.add(new Pair(colored[i], colored[u]));
                }
            }
        }

        System.out.println(set_ans.size());
    }
    public static void main(String[] args) {
        new F().run();
    }

}

/*
4 5
2 1
3 2
2 3
4 3
4 4
 */

//Post: 2