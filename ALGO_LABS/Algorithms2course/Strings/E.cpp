#include <iostream>
#include <vector>

std::vector<long long> buildZ(std::string& s) {
    unsigned long n = s.length();
    std::vector<long long> ret(n);
    long long l = 0, r = 0;
    for (size_t i = 1; i < n; ++i) {
        ret[i] = std::max(std::min((long long)(r - i), (long long) ret[i - l]), 0ll);
        while (i + ret[i] < n && s[ret[i]] == s[i + ret[i]]) ret[i]++;
        if (ret[i] + i > r) {
            r = static_cast<long long int>(i + ret[i]);
            l = static_cast<long long int>(i);
        }
    }
    return std::move(ret);

}

int main() {
    std::string s;
    std::cin >> s;
    std::vector Z = std::move(buildZ(s));
    Z[0] = s.length();
    for (int i = 1; i <= s.length(); ++i) {
        bool ok = true;
        for (int j = 0; j < s.length();) {
            if (Z[j] >= i) {
                j += i;
            } else {
                ok = false;
                break;
            }
        }
        if (ok) {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}

