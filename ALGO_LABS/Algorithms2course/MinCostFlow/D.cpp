//
// Created by Timoniche on 4/20/2019.
//

#include <vector>
#include <limits>
#include <iostream>
#include <set>

const int INF = std::numeric_limits<int>::max() - 15;

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

struct ProblemDestination
{
    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> adj;
    /**
     * rock - 1
     * scissors - 2
     * paper - 3
     */
    //std::vector<int> type;
    std::vector<int> dist1;
    std::vector<int> matching;
    int edge_num = 0;
    int s = 0;
    int t = -1;

    void set_s(int s) {
        this->s = s;
    }

    void set_t(int t) {
        this->t = t;
    }

    explicit ProblemDestination(int n) : n(n) {
        auto sz = static_cast<size_t>(n * 2 + 5);
        dist1.resize(sz);
        matching.resize(sz);
//        type.resize(sz);
        adj.assign(sz, std::vector<int>());
    }

    void dijkstra() {
        std::set<std::pair<int, int>> Q{};
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
                int w = edges[index].cost;
                if (dist1[e.to] > dist1[v] + w) {
                    Q.erase({dist1[e.to], e.to});
                    dist1[e.to] = dist1[v] + w;
                    Q.emplace(dist1[e.to], e.to);
                    matching[e.to] = index;
                }
            }
        }
    }

    int fill_flow(int flow) {
        int result = 0;
        while (true) {
            dijkstra();
            if (dist1[t] == INF)
                return result;
            int push = flow;
            int cur = t;
            while (cur != s) {
                Edge &tmp = edges[matching[cur]];
                int from = tmp.from;
                int can_push = tmp.c - tmp.flow;
                push = std::min(push, can_push);
                cur = from;
            }
            flow -= push;
            cur = t;
            while (cur != s) {
                Edge &tmp = edges[matching[cur]];
                int from = tmp.from;
                int to = tmp.to;
                edges[matching[cur]].flow += push;
                edges[matching[cur] ^ 1].flow -= push;
                result += push * tmp.cost;
                cur = from;
            }
            if (flow == 0)
                break;
        }
        return result;
    }

    void add_edge(int from, int to, int c, int cost) {
        edges.emplace_back(from, to, 0, c, cost);
        adj[from].push_back(edge_num);
        edges.emplace_back(to, from, 0, 0, -cost);
        adj[to].push_back(edge_num + 1);
        edge_num += 2;
    }

};

int main() {
    freopen("rps2.in", "r", stdin);
    freopen("rps2.out", "w", stdout);

    int n = 3;
    int r1, s1, p1;
    //left
    std::cin >> r1 >> s1 >> p1;

    //n = r1 + s1 + p1;
    int r2, s2, p2;

    //right
    std::cin >> r2 >> s2 >> p2;
    ProblemDestination B(n);

    //fill types left
    //________________________________________
//    int index = 1;
//    for (int i = 0; i < r1; ++i) {
//        B.type[index++] = 1;
//    }
//    for (int i = 0; i < s1; ++i) {
//        B.type[index++] = 2;
//
//    }
//    for (int i = 0; i < p1; ++i) {
//        B.type[index++] = 3;
//
//    }
    //_________________________________________
    //fill types right
    //________________________________________
//    index = n + 1;
//    for (int i = 0; i < r2; ++i) {
//        B.type[index++] = 1;
//    }
//    for (int i = 0; i < s2; ++i) {
//        B.type[index++] = 2;
//
//    }
//    for (int i = 0; i < p2; ++i) {
//        B.type[index++] = 3;
//
//    }
    //_________________________________________
    B.set_s(0);
    B.set_t(2 * n + 1);

//    for (int i = 1; i <= n; i++) {
//        //B.add_edge(B.s, i, 1, 0);
//        B.add_edge(B.s, i, 1, 0);
//    }
    B.add_edge(B.s, 1, r1, 0);
    B.add_edge(B.s, 2, s1, 0);
    B.add_edge(B.s, 3, p1, 0);

//    for (int i = n + 1; i <= 2 * n; i++) {
//        B.add_edge(i, B.t, 1, 0);
//    }
    B.add_edge(4, B.t, r2, 0);
    B.add_edge(5, B.t, s2, 0);
    B.add_edge(6, B.t, p2, 0);



    /**
    * rock - 1
    * scissors - 2
    * paper - 3
     * 1 wins 2
     * 2 wins 3
     * 3 wins 1
     */
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) {
            int cost = 0;
//            int typeL = B.type[i];
//            int typeR = B.type[j];
            if ((i == 1 && j == 2 + 3) ||
                (i == 2 && j == 3 + 3) ||
                (i == 3 && j == 1 + 3)) {
                cost = 1;
            }
//            B.add_edge(i, j, 1, cost);
            B.add_edge(i, j, INF, cost);
        }
    }

    std::cout << B.fill_flow(INF) << std::endl;
    return 0;
}