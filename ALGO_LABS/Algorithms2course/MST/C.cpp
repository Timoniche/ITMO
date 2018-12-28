#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

struct Graph {
    unsigned int n, m;
    const static unsigned int MAXN = static_cast<int>(2e4);
    int timer{};
    std::vector<int> adj[MAXN];
    std::vector<std::pair<int, int>> adj_pair[MAXN]; //second used when edges're numbered
    int timeIn[MAXN]{};
    int f[MAXN]{}; //highest back edge
    bool wasHere[MAXN]{};
    int marked[MAXN]{}; // 2 - black, 1 - grey, 0 - white
    std::vector<int> topsort;
    bool hasCycle{};
    //std::vector<int> cut_vertexes;
    std::set<int> cut_vertexes;
    int countBridges{};
    std::vector<int> bridges;

    Graph(unsigned int n, unsigned int m) : n(n), m(m) {}

    void dfs_topsort(int v) {
        if (marked[v] == 1) {
            std::cout << -1;
            //exit(0);
            hasCycle = true;
        }
        if (marked[v] == 2) return;
        marked[v] = 1;
        for (auto u : adj[v]) {
            dfs_topsort(u);
        }
        marked[v] = 2;
        topsort.push_back(v);
    }

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
                    //cut_vertexes.push_back(v + 1);
                    cut_vertexes.emplace(v + 1);
                }
                count_children++;

            }
        }
        if (lastEdge == -1 && count_children > 1) {
            //cut_vertexes.push_back(v + 1);
            cut_vertexes.emplace(v + 1);
        }
    }

    void dfs_bridges(int v, int from = -1) {
        wasHere[v] = true;
        f[v] = timeIn[v] = timer++;
        for (auto u : adj_pair[v]) {
            int tmp = u.second;
            if (u.first == from) continue;
            //isReverseEdge?
            if (wasHere[u.first]) {
                f[v] = std::min(f[v], timeIn[u.first]);
            } else {
                dfs_bridges(u.first, v);
                f[v] = std::min(f[v], f[u.first]);
                if (f[u.first] > timeIn[v]) {
                    //uv - bridge
                    countBridges++;
                    bridges.push_back(tmp);
                }
            }
        }
    }

    void clear() {
        int timer = 0;
        FOR(i, MAXN) {
            timeIn[i] = 0;
            f[i] = 0;
            wasHere[i] = false;
            marked[i] = 0;
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
    //std::sort(g.cut_vertexes.begin(), g.cut_vertexes.end());
    std::cout << g.cut_vertexes.size() << std::endl;
    for (auto u : g.cut_vertexes) {
        std::cout << u << " ";
    }

    return 0;
}

//6 7
//1 2
//2 3
//2 4
//2 5
//4 5
//1 3
//3 6

//2
//2 3