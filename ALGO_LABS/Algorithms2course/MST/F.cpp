#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

std::set<std::pair<int, int>> set_ans;

struct Graph {

    unsigned int n, m;
    const static unsigned int MAXN = static_cast<int>(2e4 + 5);
    std::vector<int> adj[MAXN];
    bool wasHere[MAXN]{};
    int colored[MAXN]{};
    std::vector<int> topsort;

    Graph(unsigned int n, unsigned int m) : n(n), m(m) {}

    void dfs(int v) {
        wasHere[v] = true;
        for (auto u : adj[v]) {
            if (!wasHere[u]) dfs(u);
        }
        topsort.push_back(v);
    }

    void dfs_color_components(int v, int color) {
        wasHere[v] = true;
        colored[v] = color;
        for (auto u : adj[v]) {
            if (!wasHere[u]) dfs_color_components(u, color);
        }
    }


};

int main() {
    unsigned int n, m;
    std::cin >> n >> m;
    Graph g(n, m);
    Graph g_t(n, m);
    FOR(i, m) {
        int u, v;
        std::cin >> u >> v;
        g.adj[u - 1].push_back(v - 1);
        g_t.adj[v - 1].push_back(u - 1);
    }
    FOR(i, n) {
        if (!g.wasHere[i]) g.dfs(i);
    }
    std::reverse(g.topsort.begin(), g.topsort.end());

    int color = 1;
    FOR(i, n) {
        if (!g_t.wasHere[i]) {
            g_t.dfs_color_components(g.topsort[i], color++);
        }
    }

    FOR(i, n) {
        for (auto u : g.adj[i]) {
            if (g_t.colored[i] != g_t.colored[u]) {
                set_ans.emplace(g_t.colored[i], g_t.colored[u]);
            }
        }
    }

    std::cout << set_ans.size();
    return 0;
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