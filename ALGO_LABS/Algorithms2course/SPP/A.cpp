#include <limits>
#include <iostream>

int d[101][101];
const int MAX = std::numeric_limits<int>::max();

int main() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int in;
            std::cin >> in;
            d[i][j] = in;
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << d[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;


}

/* Pre:
4
0 5 9 100
100 0 2 8
100 100 0 7
4 100 100 0
 */

/* Post:
0 5 7 13
12 0 2 8
11 16 0 7
4 9 11 0
 */

