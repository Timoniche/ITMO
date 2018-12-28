#include <iostream>
#include <vector>
#include <algorithm>

const unsigned long long MAXN = 50010;
const unsigned long long MAXM = 100010;
struct Edge {
    long long x;
    long long y;
    long long cost;

    Edge(long long x, long long y, long long cost) :
            x(x), y(y), cost(cost) {}
};

typedef std::pair<Edge, long long> pei;

struct Graph {
    long long V;
    long long E;
    long long maxCostDelete;
    std::vector<pei> edges;
    std::vector<std::pair<long long, long long>> adj[MAXN];

    long long tree_id[MAXN]{};
    bool inSpanTree[MAXM]{};

    Graph(long long V, long long E, long long maxCostDelete) :
            V(V), E(E), maxCostDelete(maxCostDelete) {}

    void addEdge(long long x, long long y, long long cost, long long number) {
        adj[x].emplace_back(y, number);
        edges.push_back({{x, y, cost}, number});
    }

    void sortEdges() {
        std::sort(edges.begin(), edges.end(),
                  [](const pei &a, const pei &b) { return a.first.cost > b.first.cost; });
    }

    void tree_id_init() {
        for (long long i = 1; i <= V; ++i) {
            tree_id[i] = i;
        }
    }

    long long update_and_get(long long val) {
        return (val == tree_id[val]) ? val : (tree_id[val] = update_and_get(tree_id[val]));
    }
    void connectDSU(long long x, long long y) {
        x = update_and_get(x);
        y = update_and_get(y);
        if (rand() % 2 == 0) { //NOLINT
            std::swap(x, y);
        }
        if (x != y) {
            tree_id[x] = y;
        }
    }

    void Kruskal() {
        for (auto e : edges) {
            if (update_and_get(e.first.x) != update_and_get(e.first.y)) {
                inSpanTree[e.second] = true;
                connectDSU(e.first.x, e.first.y);
            }
        }
    }

};

int main() {
    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);

    long long n, m, s;
    std::cin >> n >> m >> s;
    Graph G(n, m, s);

    long long number = 1;
    for (int i = 0; i < m; ++i) {
        long long x, y, cost;
        std::cin >> x >> y >> cost;
        G.addEdge(x, y, cost, number++);
    }

    G.sortEdges();
    G.tree_id_init();
    G.Kruskal();

    long long curSum = 0;
    std::vector<long long> ans;
    std::reverse(G.edges.begin(), G.edges.end());
    for (auto u : G.edges) {
        if (!G.inSpanTree[u.second]) {
            curSum += u.first.cost;
            if (curSum > s) {
                curSum -= u.first.cost;
                continue;
            } else {
                ans.push_back(u.second);
            }
        }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << std::endl;
    for (auto u : ans) {
        std::cout << u << " ";
    }
    return 0;
}

