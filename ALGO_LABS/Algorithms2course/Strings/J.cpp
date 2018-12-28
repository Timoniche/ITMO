#include <utility>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

typedef unsigned long long ull;
typedef long long ll;
typedef std::pair<ll, ll> pll;

struct SuffixArray {
    std::string s;
    ull n = 0;
    std::vector<ll> suffixArray;
    std::vector<ll> lcp;

    explicit SuffixArray(const std::string &s) : s(s), n(s.length()) {}

    void buildSuffixArr() {
        const ull alph = 256;
        suffixArray.resize(n);
        std::vector<ll> c(n);
        std::vector<ll> count(std::max(n, alph), 0);
        std::vector<ll> pn(n);
        std::vector<ll> cn(n);
        for (int i = 0; i < n; ++i) {
            count[s[i] - '$']++;
        }
        for (int i = 1; i < alph; ++i) {
            count[i] += count[i - 1];
        }
        for (ll i = 0; i < n; ++i) {
            suffixArray[--count[s[i] - '$']] = i;
        }
        c[suffixArray[0]] = 0;
        ll groupes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[suffixArray[i]] != s[suffixArray[i - 1]]) {
                groupes++;
            }
            c[suffixArray[i]] = groupes - 1;
        }
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = suffixArray[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            std::fill(count.begin(), count.begin() + groupes, 0);
            for (int i = 0; i < n; i++) {
                count[c[pn[i]]]++;
            }
            for (int i = 1; i < groupes; i++) {
                count[i] += count[i - 1];
            }
            for (ll i = n - 1; i >= 0; i--) {
                suffixArray[--count[c[pn[i]]]] = pn[i];
            }
            cn[suffixArray[0]] = 0;
            groupes = 1;
            for (int i = 1; i < n; i++) {
                pll cur = std::make_pair(c[suffixArray[i]],
                        c[(suffixArray[i] + (1 << h)) % n]);
                pll prev = std::make_pair(c[suffixArray[i - 1]],
                        c[(suffixArray[i - 1] + (1 << h)) % n]);
                if (cur != prev)
                    ++groupes;
                cn[suffixArray[i]] = groupes - 1;
            }
            c.swap(cn);
        }
    }

    void buildLCP() {
        std::vector<ll> sufR(n);
        for (ll i = 0; i < n; i++) {
            sufR[suffixArray[i]] = i;
        }
        lcp.resize(n);
        ll h = 0;
        for (int i = 0; i < n; ++i) {
            if (h > 0) {
                h--;
            }
            if (sufR[i] == n - 1) {
                lcp[n - 1] = -1;
                h = 0;
            } else {
                ll j = suffixArray[sufR[i] + 1];
                while ((std::max(i + h, j + h) < n) & (s[i + h] == s[j + h])) {
                    h++;
                }
                lcp[sufR[i]] = h;
            }
        }
    }
};

int main() {
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);

    std::string s;
    std::cin >> s;
    s += '$';
    SuffixArray SA(s);
    SA.buildSuffixArr();
    SA.buildLCP();
    for (int i = 1; i < SA.suffixArray.size(); i++) {
        std::cout << SA.suffixArray[i] + 1 << " ";
    }
    std::cout << std::endl;

    for (int i = 1; i < SA.lcp.size() - 1; i++) {
        std::cout << SA.lcp[i] << " ";
    }
}