#include <utility>

#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <cmath>
#include <queue>

const int MAXN = 100'000;
const long long INF = (long long) 2e15;

std::vector<long long> mark;

int a, b, c;

unsigned int n, m;

std::vector<std::pair<int, int>> adj[MAXN];
std::set<std::pair<int, int>> Q;

void findMST(int from) {
    Q.emplace(0, from);
    while (!Q.empty()) {
        int v = (*Q.begin()).second;
        Q.erase(Q.begin());
        for (auto u : adj[v]) {
            if (mark[u.first] > mark[v] + u.second) {
                Q.erase({mark[u.first], u.first});
                mark[u.first] = mark[v] + u.second;
                Q.emplace(mark[u.first], u.first);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    mark.resize(n, INF);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
        adj[v - 1].emplace_back(u - 1, w);
    }
    std::cin >> a >> b >> c;
    a--; b--; c--;
    long long ed_ab, ed_ac, ed_bc;
    mark[a] = 0;
    findMST(a);
    ed_ab = mark[b];
    ed_ac = mark[c];

    mark.assign(n, INF);
    mark[b] = 0;
    findMST(b);
    ed_bc = mark[c];
    long long ans = std::min(std::min(ed_ab + ed_ac,
                                ed_ab + ed_bc),
                                ed_ac + ed_bc);
    if (ans >= INF) std::cout << -1;
    else std::cout << ans;
    return 0;
};
