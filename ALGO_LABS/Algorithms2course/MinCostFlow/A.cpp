#include <vector>
#include <limits>
#include <iostream>
#include <set>

const int MAXN = 300 * 3;
const long long INF = std::numeric_limits<long long>::max() - 5;
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
    std::set<std::pair<long long, int>> Q{};
    std::vector<long long> potential;
    std::vector<long long> dist1;
    std::vector<bool> used;
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
        used.assign(MAXN, false);
        dist1.resize(MAXN);
        matching.resize(MAXN);
        potential.resize(MAXN);
        adj.assign(MAXN, std::vector<int>());
    }

    void FordBellman() {
        for (int i = s; i <= t; i++)
            dist1[i] = INF;
        dist1[s] = 0;
        while (true) {
            bool was_changed = false;
            for (int i = 0; i < edge_num; i++) {
                int from = edges[i].from, to = edges[i].to;
                if (edges[i].flow == edges[i].c)
                    continue;
                if (dist1[from] == INF)
                    continue;
                if (dist1[to] > dist1[from] + edges[i].cost) {
                    dist1[to] = dist1[from] + edges[i].cost;
                    was_changed = true;
                }
            }
            if (!was_changed)
                break;
        }
    }

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
                auto& e = edges[index];
                if (e.flow == e.c) {
                    continue;
                }
                long long w = edges[index].cost + potential[v] - potential[e.to];
                if (dist1[e.to] > dist1[v] + w) {
                    Q.erase({dist1[e.to], e.to});
                    dist1[e.to] = dist1[v] + w;
                    Q.emplace(dist1[e.to], e.to);
                    matching[e.to] = index;
                }
            }
        }
    }

    long long fill_flow(long long flow) {
        long long result = 0;
        FordBellman();
        for (int i = s; i <= t; i++)
            potential[i] = dist1[i];
        while (true) {
            dijkstra();
            if (dist1[t] == INF)
                return result;
            for (int i = s; i <= t; i++)
                potential[i] = (int) std::min((long long) (potential[i]) + (dist1[i]), INF);
            long long push = flow;
            int cur = t;
            while (cur != s) {
                Edge tmp = edges[matching[cur]];
                int from = tmp.from;
                long long can_push = tmp.c - tmp.flow;
                push = std::min(push, can_push);
                cur = from;
            }
            flow -= push;
            cur = t;
            while (cur != s) {
                Edge tmp = edges[matching[cur]];
                int from = tmp.from;
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
        edges.emplace_back(to, from, c, c, -cost);
        adj[to].push_back(edge_num + 1);
        edge_num += 2;
    }

};

int main() {
    freopen("mincost.in", "r", stdin);
    freopen("mincost.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    ProblemDestination B(n);
    long long max_flow_from_s = 0;
    for (int i = 0; i < m; ++i) {
        int from, to, c, cost;
        std::cin >> from >> to >> c >> cost;
        if (from == 1) {
            max_flow_from_s += c;
        }
        B.add_edge(from, to, c, cost);
    }
    B.set_s(1);
    B.set_t(n);
    std::cout << B.fill_flow(max_flow_from_s) << std::endl;
    return 0;
}