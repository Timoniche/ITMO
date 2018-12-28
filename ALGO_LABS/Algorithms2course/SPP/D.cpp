#include <limits>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

const long long MAX = std::numeric_limits<long long>::max();
const int INF = std::numeric_limits<int>::max();
const int MAXN = 10'000;

int k;
int s;

struct edge {
    int x;
    int y;
    int w;

    edge(int x, int y, int w) : x(x), y(y), w(w) {}
};
struct Graph {
    int n;
    std::vector<std::pair<int, int>> adj[MAXN];
    std::vector<edge> edges{};
    std::vector<long long> d;
    std::vector<int> k_d[101];
    std::vector<int> p;
    std::vector<int> negativeCycle;

    Graph(int n) : n(n) {}

    void addEdge(int x, int y, int w) {
        edges.emplace_back(x, y, w);
    }

    bool isNegativeCycle() {
        bool ret = false;

        d.assign((size_t) n, 0);
        p.assign(n, -1);

        for (int i = 1; i < n; ++i) {
            for (edge e : edges) {
                if (d[e.x] != MAX && d[e.y] > d[e.x] + e.w) {
                    d[e.y] = std::max(-MAX, d[e.x] + e.w);
                    p[e.y] = e.x;
                }
            }
        }

        int lastV = 0;
        for (edge e : edges) {
            if (d[e.x] != MAX && d[e.y] > d[e.x] + e.w) {
                d[e.y] = std::max(-MAX, d[e.x] + e.w);
                ret = true;
                lastV = e.y;
                p[e.y] = e.x;
                break;
            }
        }

        if (!ret) return false;

        for (int i = 0; i < n; ++i) {
            lastV = p[lastV];
        }

        for (int curV = lastV;; curV = p[curV]) {
            if (curV == lastV && negativeCycle.size() > 1) break;
            negativeCycle.push_back(curV);
        }

        std::reverse(negativeCycle.begin(), negativeCycle.end());
        return true;

    }

    void k_d_init() {
        for (auto &t : k_d) {
            t.resize((size_t) n);
        }
        for (int i = 0; i < 101; ++i) {
            for (int j = 0; j < n; ++j) {
                k_d[i][j] = INF;
            }
        }
        k_d[0][s - 1] = 0;
    }

    void k_path() {
        k_d_init();
        for (int kt = 0; kt < k; ++kt) {
            for (auto e : edges) {
                if (k_d[kt][e.x] < INF) {
                    k_d[kt + 1][e.y] = std::min(k_d[kt + 1][e.y], k_d[kt][e.x] + e.w);
                }
            }

        }
    }

    //Строим расстояния от нулевой вершины
    void bellman() {
        d.assign(n, MAX);
        d[0] = 0;
        for (int i = 0; i < n; ++i) {
            for (auto e : edges) {
                if (d[e.x] < MAX) {
                    d[e.y] = std::min(d[e.y], d[e.x] + e.w);
                }
            }
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m >> k >> s;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        std::cin >> a >> b >> w;
        g.addEdge(a - 1, b - 1, w);
       // g.adj[a - 1].emplace_back(b - 1, w);
    }
    g.k_path();
    for (int i = 0; i < n; ++i) {
        if (g.k_d[k][i] == INF) std::cout << -1 << std::endl;
        else std::cout << g.k_d[k][i] << std::endl;
    }
    return 0;
}

/*
3 3 1 1
1 2 100
2 3 300
1 3 2
Post:
-1
100
2
 */
