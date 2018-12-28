#include <utility>

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

/*
aba#bac#

         lcp:  suf:  num:
#         0     7     0
#bac#     1     3     1
a#bac#    0     2     2
aba#bac#  1     0     3
ac#       1     5     4
ba#bac#   0     1     5
bac#      2     4     6
c#        0     6     7

lcp: 0 1 0 1 1 0 2 0
suf: 7 3 2 0 5 1 4 6
 */

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
    freopen("common.in", "r", stdin);
    freopen("common.out", "w", stdout);

    std::string s1, s2, s;
    std::cin >> s1 >> s2;
    s = s1 + '$' + s2 + '%';
    SuffixArray SA(s);
    SA.buildSuffixArr();
    SA.buildLCP();
//    for (auto u : SA.suffixArray) {
//        std::cout << u << " ";
//    }
//    std::cout << std::endl;

    SA.lcp.erase(SA.lcp.end() - 1);
    SA.lcp.insert(SA.lcp.begin(), 0);
//    for (auto u : SA.lcp) {
//        std::cout << u << " ";
//    }
//    std::cout << std::endl;

    ull gap_point = s1.length();
    ll curMax = 0;
    std::string LCP;
    for (ull i = SA.lcp.size() - 1; i > 1; i--) {
        ll suf1 = SA.suffixArray[i];
        ll suf2 = SA.suffixArray[i - 1];
        ll lcp = SA.lcp[i];
        if ((suf2 > gap_point && suf1 < gap_point) ||
            (suf1 > gap_point && suf2 < gap_point)) {
            if (lcp >= curMax) {
                curMax = lcp;
                LCP = s.substr(suf1, curMax);
            }
        }
    }
    //std::cout << curMax << std::endl;
    std::cout << LCP;

}
