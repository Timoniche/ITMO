#include <random>

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

const unsigned int MAXN = 1001;

bool adjMatrix[MAXN][MAXN];

struct Graph {
    int n;
    std::vector<int> path;
    std::vector<int> rand;

    Graph(unsigned int n) : n(n) {} //NOLINT

    int binSearch(int i) {
        int l = -1;
        int r = (int) path.size();
        int m;
        while (r > l + 1) {
            m = l + (r - l) / 2;
            if (adjMatrix[m][i]) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    }

    void findPath() {
        path.clear();
        path.push_back(0);
        std::shuffle(rand.begin() + 1, rand.end(), std::mt19937(std::random_device()()));
        int k = 1;
        while (path.size() < n) {
            int p = binSearch(rand[k]);
            path.insert(path.begin() + p, rand[k]);
            k++;
        }
    }

    void getCycle() {
        while (!adjMatrix[path[path.size() - 1]][path[0]]) {
            findPath();
        }
    }
};

int main() {
    freopen("guyaury.in", "r", stdin);
    freopen("guyaury.out", "w", stdout);

    unsigned int n;
    std::cin >> n;
    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            char isEdge;
            std::cin >> isEdge;
            bool ok = isEdge == '1';
            if (ok) {
                adjMatrix[i][j] = true;
            }
            bool ok2 = isEdge == '0';
            if (ok2) {
                adjMatrix[j][i] = true;
            }
        }
    }


    for (int i = 0; i < n; ++i) {
        g.rand.push_back(i);
    }

    g.findPath();
    g.getCycle();

    for (auto u : g.path) {
        std::cout << u + 1 << " ";
    }

    return 0;
}

//Post: 1 3 2
