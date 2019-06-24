#include <iostream>

int main() {
    long long x;
    int b, n, m;
    std::cin >> x >> b >> n >> m;
    while (x % m != b)
    {
        x += n;
    }
    std::cout << x;
    return 0;
}