//
// Created by Timoniche on 3/26/2019.
//

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

const int MAXN = 10000;
const int INF = std::numeric_limits<int>::max();

char ans[MAXN][MAXN];

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
public:
    int N;
    int s;
    int t;
    int m;
    int level[MAXN]{};
    std::vector<std::vector<Edge>> adj{MAXN, std::vector<Edge>()};
    std::vector<int> start_from{};
    //________________________
public:
    explicit Network(int N) : N(N) {
        m = 0;
    }

    void add_vertex(int to1, int to2, int c = 3) {
        m++;
        int index = N - 1 + m;

        int vertex_size = adj[index].size();
        int to1_size = adj[to1].size();
        int to2_size = adj[to2].size();

        adj[index].emplace_back(to1, 0, c, to1_size);
        adj[index].emplace_back(to2, 0, c, to2_size);
        adj[to1].emplace_back(index, 0, c, vertex_size);
        adj[to2].emplace_back(index, 0, c, vertex_size + 1);
    }
    void add_edge(int from, int to, int c = 3) {
        int from_size = adj[from].size();
        int to_size = adj[to].size();
        adj[from].emplace_back(to, 0, c, to_size);
        adj[to].emplace_back(from, 0, c, from_size);
    }

    void add_oriented(int from, int to, int c = 3) {
        int from_size = adj[from].size();
        int to_size = adj[to].size();
        adj[from].emplace_back(to, 0, c, to_size);
        adj[to].emplace_back(from, 0, 0, from_size);
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

    void fill_ans() {
        for (int i = N - m - 2; i < N - 2; ++i) {
            int flow = adj[i][0].f;
            int to1 = adj[i][0].to;
            int to2 = adj[i][1].to;
            switch (flow) {
                case 0:
                    ans[to1][to2] = 'L';
                    ans[to2][to1] = 'W';
                    break;
                case 1:
                    ans[to1][to2] = 'l';
                    ans[to2][to1] = 'w';
                    break;
                case 2:
                    ans[to1][to2] = 'w';
                    ans[to2][to1] = 'l';
                    break;
                case 3:
                    ans[to1][to2] = 'W';
                    ans[to2][to1] = 'L';
                    break;
                default:
                    break;
            }
        }
    }
};


int main() {
    int n;
    std::cin >> n;
    Network Net(n);
    std::vector<int> curr_flow((unsigned int) n, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char ch;
            std::cin >> ch;
            ans[i][j] = ch;
            if (j > i) {
                switch (ch) {
                    case 'W':
                        curr_flow[i] += 3;
                        break;
                    case 'w':
                        curr_flow[i] += 2;
                        curr_flow[j] += 1;
                        break;
                    case 'L':
                        curr_flow[j] += 3;
                        break;
                    case 'l':
                        curr_flow[i] += 1;
                        curr_flow[j] += 2;
                        break;
                    case '.':
                        Net.add_vertex(i, j);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    Net.s = Net.N + Net.m;
    Net.t = Net.s + 1;
    for (int i = 0; i < Net.m; ++i) {
        int index = Net.N + i;
        Net.add_oriented(Net.s, index);
    }


    for (int i = 0; i < n; ++i) {
        int need_flow;
        std::cin >> need_flow;
        Net.add_oriented(i, Net.t, need_flow - curr_flow[i]);
    }

    Net.N += Net.m;
    Net.N += 2;
    Net.dinic(Net.s, Net.t);
    Net.fill_ans();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << ans[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}
