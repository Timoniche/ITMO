#include <limits>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

const long long MAX = std::numeric_limits<long long>::max();

struct edge {
    int x;
    int y;
    int w;

    edge(int x, int y, int w) : x(x), y(y), w(w) {}
};
struct Graph {
    int n;
    std::vector<edge> edges{};
    std::vector<long long> d;
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

    //Строим расстояния от нулевой вершины
    void bellman() {
        d.assign(n, MAX);
        d[0] = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (auto e : edges) {
                if (d[e.x] < MAX) {
                    d[e.y] = std::min(d[e.y], d[e.x] + e.w);
                }
            }
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int in;
            std::cin >> in;
            if (in != 100'000) {
                g.addEdge(i, j, in);
            }
        }
    }


    if (g.isNegativeCycle()) {
        std::cout << "YES" << std::endl;
        std::cout << g.negativeCycle.size() << std::endl;
        for (auto u : g.negativeCycle) {
            std::cout << u + 1 << " ";
        }
    } else {
        std::cout << "NO";
    }

    return 0;
}

/* Pre:
2
0 -1
-1 0
 */

/* Post:
YES
2
2 1
 */