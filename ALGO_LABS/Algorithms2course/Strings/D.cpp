#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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
    std::string p;
    std::string t;
    std::cin >> p >> t;
    //find p#t
    std::string pattern = p + '#' + t;
    std::vector Z = std::move(buildZ(pattern));
    std::vector<size_t > ans;
    for (size_t i = p.length(); i < t.length() + p.length(); ++i) {
        if (Z[i] == p.length()) {
            ans.push_back(i + 1);
        }
    }
    std::cout << ans.size() << std::endl;
    std::sort(ans.begin(), ans.end());
    for (auto u : ans) {
        std::cout << u - p.length() - 1 << " ";
    }
    return 0;
}

