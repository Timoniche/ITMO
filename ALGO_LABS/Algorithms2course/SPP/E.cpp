#include <iostream>
#include <vector>
#include <algorithm>

const long long MAXN = 2000;
const long long INF = std::numeric_limits<long long>::max() / 3;

std::vector<long long> d;

bool inNegativeCycle[MAXN]{};

typedef std::pair<int, int> pii;

struct edge {
    int x;
    int y;
    long long w;

    edge(int x, int y, long long w) : x(x), y(y), w(w) {}
};


std::vector<edge> edges;

int n, s;

std::vector<pii> adj[MAXN];

void dfs(int v) {
    inNegativeCycle[v] = true;
    for (auto u : adj[v]) {
        if (!inNegativeCycle[u.first]) {
            dfs(u.first);
        }
    }
}

bool isNegativeCycle() {
    bool ret = false;

    d.assign((size_t) n, INF);
    d[s] = 0;

    for (int i = 1; i < n; ++i) {
        for (edge e : edges) {
            if (d[e.x] != INF && d[e.y] > d[e.x] + e.w) {
                d[e.y] = std::max(-INF, d[e.x] + e.w);
            }
        }
    }

    for (edge e : edges) {
        if (d[e.x] != INF && d[e.y] > d[e.x] + e.w) {
            d[e.y] = std::max(-INF, d[e.x] + e.w);
            ret = true;
            dfs(e.x);
        }
    }

    return ret;

}



int main() {
    int m;
    std::cin >> n >> m >> s;
    s--;
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long w;
        std::cin >> a >> b >> w;
        edges.emplace_back(a - 1, b - 1, w);
        adj[a - 1].emplace_back(b - 1, w);
    }

    isNegativeCycle();
    //bellman();

    for (int i = 0; i < n; ++i) {
        if (inNegativeCycle[i]) {
            std::cout << "-" << std::endl;
            continue;
        }
        if (d[i] == INF) std::cout << '*' << std::endl;
        else std::cout << d[i] << std::endl;
    }

    return 0;
}