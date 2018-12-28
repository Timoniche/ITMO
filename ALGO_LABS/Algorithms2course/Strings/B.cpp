#include <iostream>
#include <string>
#include <vector>

std::vector<int>& prefix(std::string& s) {
    int n = static_cast<int>(s.length());
    auto* ret = new std::vector<int>(static_cast<unsigned long>(n));
    for (int i = 1; i < n; ++i) {
        int j = ret->operator[](static_cast<unsigned long>(i - 1));
        while (j > 0 && s[i] != s[j]) {
            j = ret->operator[](static_cast<unsigned long>(j - 1));
        }
        if (s[i] == s[j]) {
            j++;
        }
        ret->operator[](static_cast<unsigned long>(i)) = j;
    }
    return *ret;
}
int main() {
    std::string s;
    std::cin >> s;
    std::vector ans = std::move(prefix(s));
    for (auto u : ans) {
        std::cout << u << " ";
    }
    return 0;
}
