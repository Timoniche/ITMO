//
// Created by Timoniche on 3/22/2019.
//

#include <iostream>
#include <vector>
#include <cmath>

/*
4
78 520 5
827 239 5
620 200 7
809 269 7
986 496
754 745
772 375
44 223
 ------
68.45242650102003
 */

struct Kuhn
{
private:
    const static int MAX = 2 * 51;
    constexpr static double eps = 1e-5;
    constexpr static double max_time = 1000 * 2;
    //_____________________________________________________
    int n;
    std::vector<int> adj[MAX];
    std::vector<double> v_obj;
    std::vector<std::pair<double, double>> coordinates;
    std::vector<int> matching;
    std::vector<bool> used;
public:
    explicit Kuhn(int n) : n(n) {
        matching.assign(MAX, -1);
        v_obj.assign(MAX, -1);
        coordinates.resize(MAX);
        used.assign(MAX, false);
    }

    void init(int num, double x, double y, double v = -1) {
        if (v != -1) {
            v_obj[num] = v;
        }
        coordinates[num] = {x, y};
    }

    void add(int to, int val) {
        adj[to].push_back(val);
        adj[val].push_back(to);
    }

    bool find_perfect_matching() {
        int vertexes_in_mt = 0;
        for (int i = 1; i <= n; ++i) {
            used.assign(MAX, false);
            if (dfs(i)) {
                vertexes_in_mt++;
            }
        }
        return vertexes_in_mt == n;
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

    double count_time(int from, int to) {
        double x = coordinates[from].first - coordinates[to].first;
        double y = coordinates[from].second - coordinates[to].second;
        return std::sqrt(x * x + y * y) / v_obj[from];
    }

    bool check_time(double time) {
        matching.assign(MAX, -1);
        used.assign(MAX, false);
        for (int i = 1; i <= 2 * n; ++i) {
            adj[i].resize(0);
        }
        //__________________________________
        for (int i = 1; i <= n; ++i) {
            for (int j = n + 1; j <= 2 * n; ++j) {
                if (count_time(i, j) <= time) {
                    add(i, j);
                }
            }
        }
        return find_perfect_matching();
    }

    double bin_time_search(double l = 0, double r = max_time) {
        while (r - l > eps) {
            double m = l + (r - l) / 2;
            if (check_time(m)) {
                r = m;
            } else {
                l = m;
            }
        }
        return l;
    }

};

int main() {
    int n;
    std::cin >> n;
    Kuhn K(n);
    for (int i = 1; i <= n; ++i) {
        double x, y, v;
        std::cin >> x >> y >> v;
        K.init(i, x, y, v);
    }
    for (int i = n + 1; i <= n + n; ++i) {
        double x, y;
        std::cin >> x >> y;
        K.init(i, x, y);
    }
    std::cout << K.bin_time_search();
    return 0;
}