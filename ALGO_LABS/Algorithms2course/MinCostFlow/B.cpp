#include <vector>
#include <limits>
#include <iostream>
#include <set>

const int MAXN = 300 * 3;
const long long INF = std::numeric_limits<int>::max();

std::vector<std::vector<int>> cost;

struct Edge
{
    int from;
    int to;
    int flow;
    int c;
    long long cost;

    Edge() = default;

    Edge(int from, int to, int flow, int c, long long cost) : from(from), to(to), flow(flow), c(c),
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

    void cout_ans() {
        for (auto& e : edges) {
            if (e.c == 1) {
                if (e.flow == e.c) {
                    if (e.from != s && e.to != t) {
                        std::cout << e.from << " " << e.to - n << std::endl;
                    }
                }
            }
        }
    }

};

int main() {
    freopen("assignment.in", "r", stdin);
    freopen("assignment.out", "w", stdout);
    int n;
    std::cin >> n;
    ProblemDestination B(n);

    cost.assign(n + 1, std::vector<int>(n + 1, 0));
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= n; j++) {
            std::cin >> cost[i][j];
        }
    }
    B.set_s(0);
    B.set_t(2 * n + 1);
    for (long long i = 1; i <= n; i++) {
        B.add_edge(B.s, i, 1, 0);
    }
    for (long long i = n + 1; i <= 2 * n; i++) {
        B.add_edge(i, B.t, 1, 0);
    }
    for (long long i = 1; i <= n; i++) {
        for (long long j = 1; j <= n; j++) {
            B.add_edge(i, n + j, 1, cost[i][j]);
        }
    }
    std::cout << B.fill_flow(n) << std::endl;
    B.cout_ans();
    return 0;
}

//int main() {
//    freopen("assignment.in", "r", stdin);
//    freopen("assignment.out", "w", stdout);
//    long long n;
//    std::cin >> n;
//    ProblemDestination B(n);
//    for (long long i = 1; i <= n; i++) {
//        for (long long j = 1; j <= n; j++) {
//            std::cin >> B.cost[i][j];
//        }
//    }
//    B.set_s(0);
//    B.set_t(2 * n + 1);
//
//    for (long long i = 1; i <= n; i++) {
//        B.add_edge(B.s, i, 1, 0);
//    }
//    for (long long i = n + 1; i <= 2 * n; i++) {
//        B.add_edge(i, B.t, 1, 0);
//    }
//    for (long long i = 1; i <= n; i++) {
//        for (long long j = 1; j <= n; j++) {
//            B.add_edge(i, n + j, 1, B.cost[i][j]);
//        }
//    }
//    std::cout << B.fill_flow(n) << std::endl;
//    for (long long i = 1; i <= n; ++i) {
//        if (ans[i] != -1) {
//            std::cout << i << " " << ans[i] << std::endl;
//        }
//    }
//    return 0;
//}
