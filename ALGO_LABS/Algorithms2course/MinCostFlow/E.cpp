//
// Created by Timoniche on 5/4/2019.
//

#include <vector>
#include <limits>
#include <iostream>
#include <set>

const long long INF = std::numeric_limits<int>::max();

struct Edge
{
    int from;
    int to;
    int flow;
    int c;
    int cost;

    Edge() = default;

    Edge(int from, int to, int flow, int c, int cost) : from(from), to(to), flow(flow), c(c),
                                                        cost(cost) {}
};

std::vector<Edge> edges;
std::vector<int> self_cost;
std::vector<std::vector<int>> adj;
std::set<std::pair<long long, int>> Q{};
std::vector<long long> dist1;
std::vector<bool> used;
std::vector<int> matching;
int edge_num = 0;
int s = 0;
int t = -1;

void dijkstra() {
    Q.clear();
    for (int i = s; i <= t; i++) {
        dist1[i] = INF;
    }
    dist1[s] = 0;
    Q.emplace(0, s);
    while (!Q.empty()) {
        int v = (*Q.begin()).second;
        Q.erase(Q.begin());
        for (auto index : adj[v]) {
            auto &e = edges[index];
            if (e.flow == e.c) {
                continue;
            }
            long long w = edges[index].cost;
            if (dist1[e.to] > dist1[v] + w) {
                Q.erase({dist1[e.to], e.to});
                dist1[e.to] = dist1[v] + w;
                Q.emplace(dist1[e.to], e.to);
                matching[e.to] = index;
            }
        }
    }
}

long long fill_flow() {
    long long result = 0;
    while (true) {
        dijkstra();
        if (dist1[t] == INF) {
            return result;
        }
        long long push = INF;
        int cur = t;
        while (cur != s) {
            Edge tmp = edges[matching[cur]];
            int from = tmp.from;
            long long can_push = tmp.c - tmp.flow;
            push = std::min(push, can_push);
            cur = from;
        }
        cur = t;
        while (cur != s) {
            Edge &tmp = edges[matching[cur]];
            int from = tmp.from;
            tmp.flow += push;
            edges[matching[cur] ^ 1].flow -= push;
            result += push * tmp.cost;
            cur = from;
        }
    }
}

inline void add_edge(int from, int to, int c, int cost) {
    edges.emplace_back(from, to, 0, c, cost);
    adj[from].push_back(edge_num);
    edges.emplace_back(to, from, c, c, -cost);
    adj[to].push_back(edge_num + 1);
    edge_num += 2;
}

/**
 * 0 -- s
 * 2 * n + 1 -- t
 * i --> n + i opposite
 */
int main() {
    int n, m;
    std::cin >> n >> m;
    auto sz = static_cast<unsigned int>(2 * n + 5);
    self_cost.resize(sz);
    used.assign(sz, false);
    dist1.resize(sz);
    matching.resize(sz);
    adj.assign(sz, std::vector<int>());
    t = 2 * n + 1;
    for (int i = 1; i <= n; ++i) {
        std::cin >> self_cost[i];
        add_edge(n + i, i, INF, self_cost[i]);
        add_edge(i, n + i, INF, 0);
        add_edge(0, n + i, 1, 0);
        add_edge(i, 2 * n + 1, 1, 0);
    }
//    int m;
//    std::ios_base::sync_with_stdio(0);
//    std::cin.tie(0);
//    std::cin >> n >> m;
    //___________________________________________

    //___________________________________________
    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        std::cin >> from >> to >> cost;
        //add_edge(from, to, c, cost);
        add_edge(n + from, to, INF, cost);
    }

//    s = 1;
//    t = n;
    std::cout << fill_flow() << std::endl;
    return 0;
}

