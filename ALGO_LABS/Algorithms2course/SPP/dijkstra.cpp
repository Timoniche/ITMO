#include <utility>

#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <cmath>
#include <queue>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

const int MAXN = 30'005;
const int INF = std::numeric_limits<int>::max();;

int mark[MAXN];

typedef std::pair<int, int> pii; //ключ-значение

struct Graph {
    unsigned int n, m;
    std::vector<pii> adj[MAXN];
    std::priority_queue<pii> Q; //без компаратора, но пушу ключ с минусом

    Graph(unsigned int n, unsigned int m) : n(n), m(m) {}

    void findMST() {
        Q.push({0, 0});
        while (!Q.empty()) {
            int v = Q.top().second;
            Q.pop();
            for (auto u : adj[v]) {
                if (mark[u.first] > mark[v] + u.second) {
                    mark[u.first] = mark[v] + u.second;
                    Q.push({-mark[u.first], u.first});
                }
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int n, m;
    std::cin >> n >> m;
    FOR(i, n) {
        mark[i] = INF;
    }
    mark[0] = 0;
    Graph g(n, m);
    FOR(i, m) {
        int u, v, w;
        std::cin >> u >> v >> w;
        g.adj[u - 1].emplace_back(v - 1, w);
        g.adj[v - 1].emplace_back(u - 1, w);
    }
    g.findMST();

    for (int i = 0; i < n; ++i) {
        std::cout << mark[i] << " ";
    }
    return 0;
};

/*
4 5
1 2 1
1 3 5
2 4 8
3 4 1
2 3 3
*/

//Post: 0 1 4 5
