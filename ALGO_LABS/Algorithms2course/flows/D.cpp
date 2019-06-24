#include <iostream>
#include <vector>

/*
 2 2
 1 2 0
 2 0
 ------
 2
 1 1
 2 2
 */

struct Kuhn
{
private:
    const static int MAX = 2 * 260;
    int n, m;
    std::vector<int> adj[MAX];
    std::vector<int> matching;
    std::vector<bool> used;
public:
    Kuhn(int n, int m) : n(n), m(m) {
        matching.assign(MAX, -1);
        used.assign(MAX, false);
    }

    void add(int to, int val) {
        adj[to].push_back(val);
        adj[val].push_back(to);
    }

    void find_matching() {
        for (int i = 1; i <= n; ++i) {
            used.assign(MAX, false);
            dfs(i);
        }
    }

    bool dfs(int v) {
        if (used[v]) { return false; }
        used[v] = true;
        for (auto &u : adj[v]) {
            if (matching[u] == -1 ||
                dfs(matching[u])) {
                matching[v] = u;
                matching[u] = v;
                return true;
            }
        }
        return false;
    }

    void cout_matching() {
        int l = 0;
        for (int i = 1; i <= n; ++i) {
            if (matching[i] != -1) { l++; }
        }
        std::cout << l << std::endl;
        for (int i = 1; i <= n; ++i) {
            if (matching[i] != -1) {
                std::cout << i << " " << (matching[i] - n) << std::endl;
            }

        }
    }

};

int main() {
    int n, m;
    std::cin >> n >> m;
    Kuhn K(n, m);
    for (int i = 1; i <= n; ++i) {
        int in;
        std::cin >> in;
        while (in != 0) {
            K.add(i, n + in);
            std::cin >> in;
        }
    }
    K.find_matching();
    K.cout_matching();
    return 0;
}