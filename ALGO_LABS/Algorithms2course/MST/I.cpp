#include <vector>
#include <limits>
#include <iostream>
#include <cmath>

#define FOR(i, n) for (int (i) = 0; (i) < (n); ++(i))

const int MAXN = 200'005;
const int INF = std::numeric_limits<int>::max();

double X[MAXN];
double Y[MAXN];

struct Graph {
    unsigned int k;
    double min_weight = 0;
    bool wasHere[MAXN]{};
    double weight_min_edge[MAXN]{};
    double distances[MAXN][MAXN];

    Graph(unsigned int n) : n(n) {}

    double count_dist(double x1, double x2, double y1, double y2) {
        return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
    }

    void countDistances() {
        FOR(i, n) {
            FOR(j, n) {
                distances[i][j] = count_dist(X[i], X[j], Y[i], Y[j]);
            }
        }
    }

    void findMST() {
        weight_min_edge[0] = 0;
        FOR(i, n) {
            int v = -1;
            FOR(j, n) {
                if (!wasHere[j] && (v == -1 || weight_min_edge[j] < weight_min_edge[v])) {
                    v = j;
                }
            }
            wasHere[v] = true;
            min_weight += weight_min_edge[v];
            FOR(j, n) {
                if (distances[v][j] < weight_min_edge[j]) {
                    weight_min_edge[j] = distances[v][j];
                }
            }
        }

    }
};

int main() {
    unsigned int n;
    std::cin >> n;
    FOR(i, n) {
        double x, y;
        std::cin >> x >> y;
        X[i] = x;
        Y[i] = y;
    }

    Graph g(n);

    FOR(i, n) {
        g.weight_min_edge[i] = INF;
    }

    g.countDistances();
    g.findMST();

    printf("%.16f", g.min_weight);
    return 0;
};
