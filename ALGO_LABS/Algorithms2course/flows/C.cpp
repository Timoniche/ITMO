//
// Created by Timoniche on 3/18/2019.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <memory>
#include <set>
#include <algorithm>

const int MAXN = 100005;
const int INF = std::numeric_limits<int>::max();

struct Edge
{
    int to;
    int f;
    int c;
    int r_index;

    Edge(int to, int f, int c, int r_index) : to(to), f(f), c(c), r_index(r_index) {}
};

struct Network
{
private:
    int N;
    int s;
    int t;
    int level[MAXN]{};
    std::vector<std::pair<int, int>> path_one;
    std::vector<std::pair<int, int>> path_two;
    std::vector<Edge> adj[MAXN];
    std::vector<int> start_from{};
    std::vector<std::pair<int, int>> from_and_index{};
public:
    std::vector<bool> used{};
    //________________________
public:
    explicit Network(int N, int s, int t) : N(N), s(s), t(t) {}

    void add_edge(int from, int to, int c) {
        int from_size = adj[from].size();
        int to_size = adj[to].size();
        adj[from].emplace_back(to, 0, c, to_size);
        from_and_index.emplace_back(from, from_size);
        adj[to].emplace_back(from, 0, 0, from_size);
    }

    int dfs_ford(int u, int c_min) {
        if (u == t) {
            return c_min;
        }
        used[u] = true;
        for (auto &p : adj[u]) {
            if (!used[p.to] && p.c > p.f) {
                int delta = dfs_ford(p.to, std::min(c_min, p.c - p.f));
                if (delta > 0) {
                    p.f += delta;
                    adj[p.to][p.r_index].f -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }

    bool dfs_path(int u, std::vector<std::pair<int, int>> &p) {
        used[u] = true;
        if (u == t) {
            return true;
        }
        int index = 0;
        for (auto &e : adj[u]) {
            if (!used[e.to] && e.f == 1) {
                bool res = dfs_path(e.to, p);
                e.f -= 1;
                adj[e.to][e.r_index].f = 0;
                if (res) p.emplace_back(u, index);
                return res;
            }
            index++;
        }
        return false;
    }

    void find_two_paths() {
        used.assign((unsigned int) N + 1, false);
        dfs_path(s, path_one);
        used.assign((unsigned int) N + 1, false);
        dfs_path(s, path_two);
        std::reverse(path_one.begin(), path_one.end());
        std::reverse(path_two.begin(), path_two.end());
    }

    int add_flow(int u, int f, int t) {
        if (u == t) {
            return f;
        }
        for (; start_from[u] < adj[u].size(); start_from[u]++) {
            Edge &edge = adj[u][start_from[u]];
            if (level[edge.to] == level[u] + 1 && edge.f < edge.c) {
                int min_f = std::min(f, edge.c - edge.f);
                int tmp_f = add_flow(edge.to, min_f, t);
                if (tmp_f > 0) {
                    edge.f += tmp_f;
                    adj[edge.to][edge.r_index].f -= tmp_f;
                    return tmp_f;
                }
            }
        }
        return 0;
    }


    void cout_paths() {
        std::cout << s + 1 << " ";
        for (auto &i : path_one) { std::cout << adj[i.first][i.second].to + 1 << " "; }
        std::cout << std::endl;
        std::cout << s + 1 << " ";
        for (auto &i : path_two) { std::cout << adj[i.first][i.second].to + 1 << " "; }
        std::cout << std::endl;
    }
};

int main() {
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    Network network(n, s - 1, t - 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        network.add_edge(a - 1, b - 1, 1);
    }

    int bridges = 0;
    for (;;) {
        network.used.assign((unsigned int) n + 1, false);
        int add_flow = network.dfs_ford(s - 1, INF);
        bridges += add_flow;
        if (add_flow == 0) { break; }
    }

    if (bridges < 2) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES" << std::endl;
    network.find_two_paths();
    network.cout_paths();
    return 0;
}
