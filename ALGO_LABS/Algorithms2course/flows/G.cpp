//
// Created by Timoniche on 3/18/2019.
//

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <memory>
#include <set>

const int MAXN = 6000;
const int INF = 50 * 50;

char map[100][100]{};

//i: 0..m-1
//j: 0..n-1
bool is_neighbours(int i1, int y1, int i2, int y2) {
    return (std::abs(i1 - i2) == 1 && std::abs(y1 - y2) == 0) ||
           (std::abs(i1 - i2) == 0 && std::abs(y1 - y2) == 1);
}

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
    int A_out = -1;
    int B_in = -1;
    //________________________
    int A_in = -1;
    int B_out = -1;
    //________________________
    std::vector<Edge> adj[MAXN];
    std::vector<int> start_from{};
    std::vector<bool> used{};
    std::vector<bool> attainable;
    std::vector<int> deletedV;
    //________________________
public:
    void set_A_out(int new_A_out) {
        A_out = new_A_out;
    }

    void set_A_in(int new_A_in) {
        A_in = new_A_in;
    }

    void set_B_in(int new_B_in) {
        B_in = new_B_in;
    }

    void set_B_out(int new_B_out) {
        B_out = new_B_out;
    }

    //________________________
    int get_A_out() {
        return A_out;
    }

    int get_A_in() {
        return A_in;
    }

    int get_B_in() {
        return B_in;
    }

    int get_B_out() {
        return B_out;
    }
    //________________________

    explicit Network(int N) : N(N) {}

    void add_oriented_edge(int from, int to, int c) {
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

    int dinic() {
        int total = 0;
        while (bfs_and_flow_check(A_in, B_in)) {
            start_from.assign(N + 1, 0);
            while (int flow = add_flow(A_in, INF, B_in)) {
                total += flow;
            }
        }
        return total;
    }

    void dfs_fill_attainable(int s) {
        attainable[s] = true;
        for (auto& e : adj[s]) {
            if (!attainable[e.to] && e.c > e.f) {
                dfs_fill_attainable(e.to);
            }
        }
    }

    void dfs_attainable(int s) {
        used[s] = true;
        for (auto& e : adj[s]) {
            if (e.c != 0 && !attainable[e.to] && e.c == e.f) {
                deletedV.push_back(s);
            }
        }

        for (auto& e : adj[s]) {
            if (!used[e.to] && e.c > e.f) {
                dfs_attainable(e.to);
            }
        }
//        used[s] = true;
//        attainable[s] = true;
//        for (auto &p : adj[s]) {
//            if (p.c - std::abs(p.f) > 0) {
//                if (!used[p.to]) {
//                    dfs_attainable(p.to);
//                }
//            }
//        }
    }

    void mark_attainable() {
        used.assign((unsigned int) N + 1, false);
        attainable.assign(N + 1, false);
        dfs_fill_attainable(A_out);
        dfs_attainable(A_out);
    }

    void fill_map(int m, int n) {
        for (auto& v : deletedV) {
            int x = v / n;
            int y = v % n;
            map[x][y] = '+';
        }
//        for (int i = 0; i < n * m; ++i) {
//            if (attainable[i] != attainable[i + n * m]
//                && i != A_in && i != B_in) {
//                int x = i / n;
//                int y = i % n;
//                map[x][y] = '+';
//            }
//        }
    }
};

int main() {
    int m, n;
    std::cin >> m >> n;
    Network Net(n * m * 2);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int v_in = n * i + j;
            int v_out = n * m + v_in;
            char ch;
            std::cin >> ch;
            map[i][j] = ch;
            if (ch == 'A') {
                Net.set_A_out(v_out);
                Net.set_A_in(v_in);
            } else if (ch == 'B') {
                Net.set_B_in(v_in);
                Net.set_B_out(v_out);
            }
        }
    }

    //0..n*m - 1 | vertexes incoming
    //n*m + 0..n*m - 1 | vertexes outgoing
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int v_in = n * i + j;
            int v_out = n * m + v_in;
            std::vector<int> neighbours = {v_in - 1,
                                           v_in + 1,
                                           v_in - n,
                                           v_in + n};
            for (int k = 0; k < 4; ++k) {
                if (!(neighbours[k] >= 0 && neighbours[k] <= n * m - 1) ||
                    neighbours[k] == Net.get_A_in() ||
                    v_in == Net.get_B_in() ||
                    !is_neighbours(i, j, neighbours[k] / n, neighbours[k] % n) ||
                    map[neighbours[k] / n][neighbours[k] % n] == '#') {
                    neighbours[k] = -1;
                }
            }
            //_____________________________________________________________
            char ch = map[i][j];
            switch (ch) {
                //mountain
                case '#':
                    //do nothing
                    break;
                    //can be Wall
                case '.':
                    Net.add_oriented_edge(v_in, v_out, 1);
                    for (int k = 0; k < 4; ++k) {
                        if (neighbours[k] != -1) {
                            Net.add_oriented_edge(v_out, neighbours[k], INF);
                        }
                    }
                    break;
                    //can't be Wall
                case '-':
                case 'A':
                case 'B':
                    Net.add_oriented_edge(v_in, v_out, INF);
                    for (int k = 0; k < 4; ++k) {
                        if (neighbours[k] != -1) {
                            Net.add_oriented_edge(v_out, neighbours[k], INF);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    //______________________________________________
    int max_f = Net.dinic();
    if (max_f == 0) {
        std::cout << max_f << std::endl;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
    } else if (max_f > 0 && max_f <= 50 * 50 - 2) {
        Net.mark_attainable();
        Net.fill_map(m, n);
        std::cout << max_f << std::endl;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << -1 << std::endl;
    }

    return 0;
}