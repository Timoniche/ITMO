import java.util.*;

public class C {
    static Node nodes[]; //root is in nodes[0]

    //for ordinary lca
    static ArrayList<Integer>[] children;
    static int[][] parents;
    static int[] inTime;
    static int[] outTime;
    static int n, log, t;

    //counting with lca
    static int[] treeSize;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        n = in.nextInt();
        log = 1;
        while ((1 << log) <= n) {
            ++log;
        }
        children = new ArrayList[n];
        parents = new int[n][log + 1];
        inTime = new int[n];
        outTime = new int[n];

        treeSize = new int[n];

        for (int i = 0; i < n; i++) {
            children[i] = new ArrayList<>();
        }
        ArrayList<Integer>[] edges = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            edges[i] = new ArrayList<>();
        }
        for (int i = 1; i < n; i++) {
            int v = in.nextInt() - 1;
            int u = in.nextInt() - 1;
            edges[v].add(u);
            edges[u].add(v);
            //children[in.nextInt() - 1].add(i);
        }

        // hanging up a tree using bfs
        Queue<Integer> q = new ArrayDeque<>();
        boolean[] used = new boolean[n];
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i] = new Node();
            nodes[i].index = i;
        }
        q.add(0);
        used[0] = true;
        nodes[0].parent = nodes[0];
        while (!q.isEmpty()) {
            int v = q.poll();
            for (int u : edges[v]) {
                if (!used[u]) {
                    nodes[u].parent = nodes[v];
                    children[v].add(u);
                    used[u] = true;
                    q.add(u);
                }
            }
        }

        t = 0;
        dfs(0, 0);

        buildHeavyLight(0, null);

//        soutEverything();
        int m = in.nextInt();
        for (int j = 0; j < m; j++) {
            if (in.next().equals("?")) {
                int v = in.nextInt() - 1;
                System.out.println(nodes[v].segmentTree.getValue(nodes[v].segmentTreeIndex));
            } else {
                plusValue(in.nextInt() - 1, in.nextInt() - 1, in.nextInt());
            }
//            soutEverything();
        }
    }

    static void soutEverything() {
        for (Node node : nodes) {
            System.out.println(node.toString());
        }
        System.out.println();
    }

    static void buildHeavyLight(int v, SegmentTree segmentTree) {
        boolean wasNull = segmentTree == null;
        if (wasNull) {
            segmentTree = new SegmentTree();
            segmentTree.firstNode = nodes[v];
        }
        nodes[v].segmentTree = segmentTree;
        nodes[v].segmentTreeIndex = segmentTree.plannedSize;
        segmentTree.plannedSize++;
        int maxSize = 0;
        int maxChild = -1;
        for (int i = 0; i < children[v].size(); i++) {
            int child = children[v].get(i);
            if (treeSize[child] > maxSize) {
                maxSize = treeSize[child];
                maxChild = child;
            }
        }
        for (int i = 0; i < children[v].size(); i++) {
            int child = children[v].get(i);
            if (child == maxChild) {
                buildHeavyLight(child, segmentTree);
            } else {
                buildHeavyLight(child, null);
            }
        }
        if (wasNull) {
            segmentTree.build();
        }
    }

/*  just a mistake in reading of the task

    //between two vertexes
    static int findSum(int v, int u) {
        int lca = findLCA(v, u);
        return findSum(v) + findSum(u) - 2 * findSum(lca);
    }

    //between vertex and root
    static int findSum(int vIndex) {
        Node v = nodes[vIndex];
        int ans = 0;
        for (; ; ) {
            ans += v.segmentTree.findSum(0, v.segmentTreeIndex);
            v = v.segmentTree.getNode(0);
            if (v != nodes[0]) {
                ans += v.parentEdgeWeight;
                v = v.parent;
            } else {
                break;
            }
        }
        return ans;
    }
*/

    //between two vertexes
    static void plusValue(int v, int u, int value) {
        int lca = findLCA(v, u);
        plusValue(v, value);
//        soutEverything();
        plusValue(u, value);
//        soutEverything();
        plusValue(lca, -value);
        if (nodes[lca] != nodes[lca].parent) {
            plusValue(nodes[lca].parent.index, -value);
        }
//        soutEverything();
    }

    //between vertex and root
    static void plusValue(int vIndex, int value) {
        Node v = nodes[vIndex];
        for (; ; ) {
            v.segmentTree.plusValue(0, v.segmentTreeIndex, value);
            v = v.segmentTree.firstNode;
            if (v != nodes[0]) {
//                v.parentEdgeWeight += value;
                v = v.parent;
            } else {
                break;
            }
        }
    }


    //ordinary lca
    static int findLCA(int v, int u) {
        if (isAncestor(v, u)) {
            return v;
        } else if (isAncestor(u, v)) {
            return u;
        } else {
            for (int i = log; i >= 0; --i) {
                if (!isAncestor(parents[v][i], u)) {
                    v = parents[v][i];
                }
            }
            return parents[v][0];
        }
    }

    static void dfs(int v, int p) {
        treeSize[v] = 1;
        inTime[v] = ++t;
        parents[v][0] = p;
        for (int i = 1; i <= log; ++i) {
            parents[v][i] = parents[parents[v][i - 1]][i - 1];
        }
        for (int i = 0; i < children[v].size(); i++) {
            int u = children[v].get(i);
            if (u != p) {
                dfs(u, v);
            }
            treeSize[v] += treeSize[u];
        }
        outTime[v] = ++t;
    }

    static boolean isAncestor(int v, int u) {
        return inTime[v] <= inTime[u] && outTime[v] >= outTime[u];
    }

    static class Node {
        int index;
        SegmentTree segmentTree;
        int segmentTreeIndex;

        Node parent;
//        int parentEdgeWeight;

        @Override
        public String toString() {
            return index + " " + segmentTree + " " + segmentTreeIndex + " " + parent.index;
        }
    }
}

class SegmentTree {
    int plannedSize = 0;
    C.Node firstNode;
    long[] a;
    long[] plus;

    public void build() {
        a = new long[plannedSize * 4];
        plus = new long[plannedSize * 4];
    }

    public void plusValue(int l, int r, int value) {
        set(1, 0, plannedSize - 1, l, r, value);
    }

    private void set(int v, int l, int r, int ql, int qr, long x) {
        if (ql > qr) {
            return;
        }
        if (ql == l && qr == r) {
            plus[v]+= x;
        } else {
            propagate(v);
            set(2 * v, l, (l + r) / 2, ql, Math.min(qr, (l + r) / 2), x);
            set(2 * v + 1, (l + r) / 2 + 1, r, Math.max(ql, (l + r) / 2 + 1), qr, x);
        }
    }

    public long getValue(int i) {
        return getValue(1, 0, plannedSize - 1, i, i);
    }

    private long getValue(int v, int l, int r, int ql, int qr) {
        if (ql > qr) {
            return 0;
        }
        if (ql == l && qr == r) {
            return a[v] + plus[v];
        }
        propagate(v);
        return getValue(2 * v, l, (l + r) / 2, ql, Math.min(qr, (l + r) / 2)) +
                getValue(2 * v + 1, (l + r) / 2 + 1, r, Math.max(ql, (l + r) / 2 + 1), qr);
    }

    private void propagate(int v) {
        plus[2 * v] += plus[v];
        plus[2 * v + 1] += plus[v];
        plus[v] = 0;
    }

    @Override
    public String toString() {
        return Arrays.toString(a);
    }
}
