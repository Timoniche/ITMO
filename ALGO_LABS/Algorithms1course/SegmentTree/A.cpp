#include <iostream>
#include <fstream>
#include <vector>
 
const int s16 = 1 << 16;
const int s30 = 1 << 30;
 
int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("sum0.in", "r", stdin);
    freopen("sum0.out", "w", stdout);
    long long sum = 0;
    int n, x, y;
    long long a0;
    std::cin >> n >> x >> y >> a0;
    int pred;
    std::vector<long long> asum(0);
    asum.reserve(s30);
    pred = a0;
    //asum[0] = a0;
    asum.push_back(a0);
    for (int i = 1; i < n; i++) {
        int tmp = (x * pred + y);
        pred = (tmp + s16) & (s16 - 1);
        asum.push_back(pred + asum[i - 1]);
        //asum[i] = pred + asum[i - 1];
    }
    int m, z, t, b0;
    std::cin >> m >> z >> t >> b0;
    int b2 = (z * b0 + t + s30) & (s30 - 1);
    for (int i = 0; i < m; i++) {
        int min = (b0 + n) % n;
        int max = (b2 + n) % n;
        if (min > max) {
            int temp = min;
            min = max;
            max = temp;
        }
        if (min >= 1) {
            sum += asum[max] - asum[min - 1];
        } else {
            sum += asum[max];
        }
        int tmp0 = z * b2 + t;
        b0 = (tmp0 + s30) & (s30 - 1);
        int tmp2 = z * b0 + t;
        b2 = (tmp2 + s30) & (s30 - 1);
    }
    std::cout << sum;
    return 0;
}
