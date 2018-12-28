#include <iostream>
#include <vector>
#include <algorithm>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

static unsigned int n, m;
const unsigned int MAXN = static_cast<int>(2e4);
static std::vector<int> adj[MAXN];
int marked[MAXN];
std::vector<int> topsort;

void dfs(int v) {
    if (marked[v] == 1) {
        std::cout << -1;
        exit(0);
    }
    if (marked[v] == 2) return;
    marked[v] = 1;
    for (auto u : adj[v]) {
        dfs(u);
    }
    marked[v] = 2;
    topsort.push_back(v);
}

int main() {
    FOR(i, MAXN) { marked[i] = 0; }
    std::cin >> n >> m;
    FOR(i, m) {
        int u, v;
        std::cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }
    FOR(i, n) {
        dfs(i);
    }
    std::reverse(topsort.begin(), topsort.end());
    FOR(i, topsort.size()) { std::cout << (topsort[i] + 1) << " "; }

    return 0;
}

//6 6
//1 2
//3 2
//4 2
//2 5
//6 5
//4 6
