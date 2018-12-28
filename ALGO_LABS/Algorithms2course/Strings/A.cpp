#include <iostream>
#include <vector>
#include <math.h>

typedef unsigned long long ull;
const ull p = 7;

void fillPows(std::vector<ull>& v) {
    v[0] = 1;
    for (int i = 1; i < v.size(); ++i) {
        v[i] = v[i - 1] * p;
    }
}

std::vector<ull> countHash(const std::string &s, std::vector<ull>& pows) {
    std::vector<ull> ret(s.length());
    ret[0] = (unsigned long long int) s[0];
    for (int i = 1; i < s.length(); ++i) {
        ret[i] = pows[i] * s[i] + ret[i - 1];
    }
    return ret;
}

int main() {
    std::string s;
    std::cin >> s;
    std::vector<ull> pows(s.length() + 1);
    fillPows(pows);
    std::vector<ull> hash = countHash(s, pows);
    ull M;
    std::cin >> M;
    for (int i = 0; i < M; ++i) {
        ull a, b, c, d;
        std::cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        //compare [a, b] & [c, d]
        if ((hash[b] - (a == 0 ? 0 : hash[a - 1])) * pows[c]
            == (hash[d] - (c == 0 ? 0 : hash[c - 1])) * pows[a]) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}