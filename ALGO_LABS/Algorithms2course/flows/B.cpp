//
// Created by Timoniche on 3/18/2019.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <memory>
#include <set>

const int MAXN = 110;
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
    int level[MAXN]{};
    std::vector<Edge> adj[MAXN];
    std::vector<int> start_from{};
    std::vector<std::pair<int, int>> from_and_index{};
    std::vector<bool> used{};
    std::set<int> attainable;
    //________________________
public:
    explicit Network(int N) : N(N) {}

    void add_edge(int from, int to, int c) {
        int from_size = adj[from].size();
        int to_size = adj[to].size();
        adj[from].emplace_back(to, 0, c, to_size);
        from_and_index.emplace_back(from, from_size);
        adj[to].emplace_back(from, 0, c, from_size);
    }

    bool bfs_and_flow_check(int s, int t) {
        for (int i = 0; i < N; ++i) {
            level[i] = -1;
        }
        level[s] = 0;
        std::priority_queue<int> Q;
        Q.push(s);
        while (!Q.empty()) {
            int u = Q.top();
            Q.pop();
            for (auto &edge : adj[u]) {
                if (level[edge.to] < 0 && edge.f < edge.c) {
                    level[edge.to] = level[u] + 1;
                    Q.push(edge.to);
                }
            }
        }
        return level[t] >= 0;
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

    int dinic(int s, int t) {
        int total = 0;
        while (bfs_and_flow_check(s, t)) {
            start_from.assign(N + 1, 0);
            while (int flow = add_flow(s, INF, t)) {
                total += flow;
            }
        }
        return total;
    }

    void dfs_attainable(int s) {
        used[s] = true;
        attainable.emplace(s);
        for (auto& p : adj[s]) {
            if (p.c - std::abs(p.f) > 0) {
                if (!used[p.to]) {
                    dfs_attainable(p.to);
                }
            }
        }
    }

    void mark_attainable(int s) {
        used.assign((unsigned int) N + 1, false);
        dfs_attainable(s);
    }

    void cout_min_cut(int max_f) {
        int index = 0;
        int count = 0;
        std::vector<int> ans;
        for (auto &p : from_and_index) {
            index++;
            auto& e = adj[p.first][p.second];
            bool is_a = true, is_b = true;
            if (attainable.find(p.first) == attainable.end()) {
                is_a = false;
            }
            if (attainable.find(e.to) == attainable.end()) {
                is_b = false;
            }
            if ((is_a && !is_b) || (!is_a && is_b)) {
                count++;
                ans.push_back(index);
            }
        }
        std::cout << count << " ";
        std::cout << max_f << std::endl;
        for (int& val : ans) {
            std::cout << val << " ";
        }
    }

    void cout_flows() {
        for (auto &p : from_and_index) {
            std::cout << adj[p.first][p.second].f << std::endl;
        }
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    Network network(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        network.add_edge(a - 1, b - 1, c);
    }
    int max_f = network.dinic(0, n - 1);
    network.mark_attainable(0);
    network.cout_min_cut(max_f);
    return 0;
}

