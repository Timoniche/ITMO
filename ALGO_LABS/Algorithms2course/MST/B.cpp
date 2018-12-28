#include <iostream>
#include <vector>
#include <algorithm>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

static int timer{};
static int countEdges{};
std::vector<int> ans{};

static unsigned int n, m;
const unsigned int MAXN = static_cast<int>(2e4);
static std::vector<std::pair<int, int>> adj[MAXN];

int timeIn[MAXN];
int f[MAXN];
bool wasHere[MAXN]{};


void dfs(int v, int from) {
    wasHere[v] = true;
    f[v] = timeIn[v] = timer++;
    for (auto u : adj[v]) {
        int tmp = u.second;
        if (u.first == from) continue;
        //isReverseEdge?
        if (wasHere[u.first]) {
            f[v] = std::min(f[v], timeIn[u.first]);
        } else {
            dfs(u.first, v);
            f[v] = std::min(f[v], f[u.first]);
            if (f[u.first] > timeIn[v]) {
                //uv - bridge
                countEdges++;
                ans.push_back(tmp);
            }
        }
    }

}

int main() {
    std::cin >> n >> m;
    int k = 0;
    FOR(i, m) {
        int u, v;
        std::cin >> u >> v;
        k++;
        adj[u - 1].emplace_back(v - 1, k);
        adj[v - 1].emplace_back(u - 1, k);
    }
    FOR(i, n) {
        if (!wasHere[i]) dfs(i, -1);
    }
    std::cout << countEdges << std::endl;
    std::sort(ans.begin(), ans.end());
    for (int u : ans) std::cout << u << " ";
    return 0;
}

/*
6 7
1 2
2 3
3 4
1 3
4 5
4 6
5 6
Post: 1, 3
 */