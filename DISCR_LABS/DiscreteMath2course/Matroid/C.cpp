#include <stdio.h>

#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> pii;

struct bigraph {
    static const int MAXN = 1001;
    std::vector<int> curMatchingSet{}; //for right side, 0 if not in Set
    int n; //|left side| == |right side|
    std::vector<std::pair<int, int>> weights{}; //for left side: w + number
    std::vector<int> adj[MAXN]{}; //numbered from 1
    bool wasHere[MAXN]{};

    explicit bigraph(int n) : n(n) {}

    bool KuhnSearch(int v) {
        if (wasHere[v]) return false;
        wasHere[v] = true;
        for (auto u : adj[v]) {
            int tmp = curMatchingSet[u];
            if (KuhnSearch(tmp) || tmp == 0) {
                curMatchingSet[u] = v;
                return true;
            }
        }
        return false;
    }

    void clear() {
        std::fill(wasHere, wasHere + n, false);
    }
};

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);

    int n;
    std::cin >> n;
    bigraph G(n);

    for (int i = 1; i <= n; ++i) {
        int w;
        std::cin >> w;
        G.weights.emplace_back(w, i);
    }

    std::sort(G.weights.begin(), G.weights.end(), [](const pii &a, const pii &b) {
        return a.first > b.first;
    });

    for (int i = 1; i <= n; ++i) {
        int count;
        std::cin >> count;
        for (int j = 0; j < count; ++j) {
            int v;
            std::cin >> v;
            G.adj[i].push_back(v);
        }
    }
    G.curMatchingSet.assign(bigraph::MAXN, 0);
    for (int i = 0; i < n; ++i) {
        G.clear();
        G.KuhnSearch(G.weights[i].second);
    }
    std::vector<int> ans(n, 0);
    for (int i = 1; i <= n; ++i) {
        if (G.curMatchingSet[i] != 0) {
            ans[G.curMatchingSet[i] - 1] = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << " ";
    }
    return 0;
};

