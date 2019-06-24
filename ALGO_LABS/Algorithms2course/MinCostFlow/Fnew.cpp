//
// Created by Timoniche on 4/19/2019.
//

#include <vector>
#include <limits>
#include <iostream>
#include <set>
#include <cmath>

const double MAXN = 300 * 3;
const long double INF = std::numeric_limits<double>::max() - 5;

struct Edge
{
    double from;
    double to;
    double flow;
    double c;
    long double cost;

    Edge() = default;

    Edge(double from, double to, double flow, double c, long double cost) : from(from), to(to), flow(flow), c(c),
                                                                            cost(cost) {}
};

struct ProblemDestination
{
    double n;
    std::vector<Edge> edges;
    std::vector<std::vector<double>> adj;
    std::set<std::pair<long double, double>> Q{};
    std::vector<long double> dist1;
    std::vector<bool> used;
    std::vector<int> matching;
    double edge_num = 0;
    double s = 0;
    double t = -1;
    //________________________________________________

    std::vector<double> v_obj;
    std::vector<std::pair<double, double>> coordinates;

    //________________________________________________
    void set_s(double s) {
        this->s = s;
    }

    void set_t(double t) {
        this->t = t;
    }

    explicit ProblemDestination(double n) : n(n) {
        used.assign(MAXN, false);
        dist1.resize(MAXN);
        matching.resize(MAXN);
        coordinates.resize(MAXN);
        v_obj.resize(MAXN);
        adj.assign(MAXN, std::vector<double>());
    }

    double count_time(double from, double to) {
        double x = coordinates[from].first - coordinates[to].first;
        double y = coordinates[from].second - coordinates[to].second;
        return std::sqrt(x * x + y * y) / v_obj[from];
    }

    void init(double num, double x, double y, double v = -1) {
        if (v != -1) {
            v_obj[num] = v;
        }
        coordinates[num] = {x, y};
    }

/**
 * dijkstra with min-max invariant
 */
    void dijkstra() {
        Q.clear();
        for (double i = s; i <= t; i++) {
            dist1[i] = -INF;
        }
        //dist1[s] = 0;
        Q.emplace(-INF, s);
        while (!Q.empty()) {
            double v = (*Q.begin()).second;
            Q.erase(Q.begin());
            for (auto index : adj[v]) {
                auto &e = edges[index];
                if (e.flow == e.c) {
                    continue;
                }
                long double max_cost_edge_in_path =
                        std::max(edges[index].cost, dist1[v]);
                if (dist1[e.to] == -INF) {
                    dist1[e.to] = max_cost_edge_in_path;
                    Q.emplace(dist1[e.to], e.to);
                    matching[e.to] = index;
                } else if (dist1[e.to] > max_cost_edge_in_path) {
                    Q.erase({dist1[e.to], e.to});
                    dist1[e.to] = max_cost_edge_in_path;
                    Q.emplace(dist1[e.to], e.to);
                    matching[e.to] = index;
                }
            }
        }
    }

    long double fill_flow(long double flow) {
        long double result = 0;
        while (true) {
            dijkstra();
            if (dist1[t] == -INF) {
                return result;
            }
            long double push = flow;
            double cur = t;
            while (cur != s) {
                Edge tmp = edges[matching[cur]];
                double from = tmp.from;
                long double can_push = tmp.c - tmp.flow;
                push = std::min(push, can_push);
                cur = from;
            }
            flow -= push;
            cur = t;
            while (cur != s) {
                Edge& tmp = edges[matching[cur]];
                double from = tmp.from;
                double to = tmp.to;
                edges[matching[cur]].flow += push;
                edges[matching[cur] ^ 1].flow -= push;
                //result += push * tmp.cost;
                result = std::max(result, tmp.cost);
                cur = from;
            }
            if (flow == 0)
                break;
        }
        return result;
    }

    void add_edge(double from, double to, double c, double cost) {
        edges.emplace_back(from, to, 0, c, cost);
        adj[from].push_back(edge_num);
        edges.emplace_back(to, from, 0, 0, -cost);
        adj[to].push_back(edge_num + 1);
        edge_num += 2;
    }

};

int main() {
    double n;
    std::cin >> n;
    ProblemDestination K(n);
    for (double i = 1; i <= n; ++i) {
        double x, y, v;
        std::cin >> x >> y >> v;
        K.init(i, x, y, v);
    }
    for (double i = n + 1; i <= n + n; ++i) {
        double x, y;
        std::cin >> x >> y;
        K.init(i, x, y);
    }
    K.set_s(0);
    K.set_t(2 * n + 1);

    for (long double i = 1; i <= n; i++) {
        K.add_edge(K.s, i, 1, 0);
    }
    for (long double i = n + 1; i <= 2 * n; i++) {
        K.add_edge(i, K.t, 1, 0);
    }

    for (double i = 1; i <= n; i++) {
        for (double j = n + 1; j <= 2 * n; j++) {
            double cost = K.count_time(i, j);
            K.add_edge(i, j, 1, cost);
        }
    }
    std::cout << K.fill_flow(n) << std::endl;
    return 0;
}