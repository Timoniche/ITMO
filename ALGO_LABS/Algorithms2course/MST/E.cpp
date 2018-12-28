#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

struct Graph {
    unsigned int n, m;
    const static unsigned int MAXN = static_cast<int>(2e4 + 3);
    const static unsigned int MAXM = static_cast<int>(2e5 + 3);
    int timer{};
    std::vector<std::pair<int, int>> adj_pair[MAXN]; //second used when edges're numbered
    int timeIn[MAXN]{};
    int f[MAXN]{}; //highest back edge
    bool wasHere[MAXN]{};
    std::set<int> cut_vertexes;
    int colEdges[MAXM]{};
    int componentsCounter = 0;

    Graph(unsigned int n, unsigned int m) : n(n), m(m) {}

    void dfs_cut_vertexes(int v, int lastEdge = -1) {
        wasHere[v] = true;
        f[v] = timeIn[v] = timer++;
        int count_children = 0;
        for (auto u : adj_pair[v]) {
            if (u.second == lastEdge) continue;
            //isReverseEdge?
            if (wasHere[u.first]) {
                f[v] = std::min(f[v], timeIn[u.first]);
            } else {
                dfs_cut_vertexes(u.first, u.second);
                f[v] = std::min(f[v], f[u.first]);
                if (lastEdge != -1 && f[u.first] >= timeIn[v]) {
                    //is_cut_vertex?
                    cut_vertexes.emplace(v + 1);
                }
                count_children++;

            }
        }
        if (lastEdge == -1 && count_children > 1) {
            cut_vertexes.emplace(v + 1);
        }
    }

    void dfs_edges_components(int v, int color) {
        wasHere[v] = true;
        for (auto u : adj_pair[v]) {
            if (wasHere[u.first]) continue;
            if (cut_vertexes.count(u.first) == 0) {
                colEdges[u.second] = color;
                dfs_edges_components(u.first, color);
            } else {
                colEdges[u.second] = color;
                componentsCounter++;
                dfs_edges_components(u.first, componentsCounter);
            }
        }
    }

    void clear() {
        //int timer = 0;
        FOR(i, MAXN) {
            //timeIn[i] = 0;
            //f[i] = 0;
            wasHere[i] = false;
            //marked[i] = 0;
        }
    }

};

int main() {
    unsigned int n, m;
    std::cin >> n >> m;
    Graph g(n, m);
    int k = 0;
    FOR(i, m) {
        int u, v;
        std::cin >> u >> v;
        k++;
        g.adj_pair[u - 1].emplace_back(v - 1, k);
        g.adj_pair[v - 1].emplace_back(u - 1, k);
    }
    FOR(i, n) {
        if (!g.wasHere[i]) g.dfs_cut_vertexes(i);
    }

    g.clear();
    FOR(i, n) {
        if (!g.wasHere[i]) {
            g.componentsCounter++;
            g.dfs_edges_components(i, g.componentsCounter);
        }
    }

    std::cout << g.componentsCounter << std::endl;
    FOR(i, m) {
        std::cout << g.colEdges[i] << " ";
    }

    return 0;
}

/*
5 6
1 2
2 3
3 1
1 4
4 5
5 1
*/

//Post: 2
//1 1 1 2 2 2
