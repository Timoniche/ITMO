#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

const unsigned int MAXN = 4001;

bool adjMatrix[MAXN][MAXN];

struct Graph {
    int n;
    std::deque<int> Q;
    Graph(unsigned int n) : n(n) {} //NOLINT

    void getCycle() {
        for (int i = 0; i < n; ++i) {
            Q.push_back(i);
        }
        for (int j = 0; j < n * (n - 1); ++j) {
            if (!adjMatrix[Q[0]][Q[1]]) {
                int i = 2;
                while(!adjMatrix[Q[0]][Q[i]] || !adjMatrix[Q[1]][Q[i + 1]]) {
                    i++;
                }
                std::reverse(Q.begin() + 1, Q.begin() + i + 1);
            }
            Q.push_back(Q[0]);
            Q.pop_front();
        }
    }
};

int main() {
    freopen("fullham.in", "r", stdin);
    freopen("fullham.out", "w", stdout);

    unsigned int n;
    std::cin >> n;
    Graph g(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            char isEdge;
            std::cin >> isEdge;
            bool ok = isEdge == '1';
            if (ok) {
                adjMatrix[i][j] = adjMatrix[j][i] = true;
            }
        }
    }

    g.getCycle();
    for (auto u : g.Q) {
        std::cout << u + 1 << " ";
    }
    return 0;
}

//Post: 1 2 3 4
