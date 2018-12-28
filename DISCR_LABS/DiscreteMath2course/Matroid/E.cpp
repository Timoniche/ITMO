#include <stdio.h>
#include <iostream>

#include<vector>
#include <algorithm>

struct element {
    long long weight;
    long long number;

    element(long long weight, long long number) : weight(weight), number(number) {}

    static bool comp(const element &a, const element &b) {
        return a.weight > b.weight;
    }
};

struct Matroid {
    long long n; //|X|
    long long m; //|S| - cycles
    std::vector<element> elements;
    std::vector<bool> cycles;
    std::vector<bool> wasHere;


    Matroid(long long n, long long m) : n(n), m(m) {}

    void dfs(long long index) {
        wasHere[index] = true;
        for (int i = 0; i < n; ++i) {
            if ((index & (1 << i)) == 0) {
                long long newIndex = index | (1 << i);
                cycles[newIndex] = true;
                if (!wasHere[newIndex]) {
                    dfs(newIndex);
                }
            }
        }
    }

};

int main() {
    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);

    long long n, m;
    std::cin >> n >> m;
    Matroid M(n, m);
    for (int i = 1; i <= n; ++i) {
        long long w;
        std::cin >> w;
        M.elements.emplace_back(w, i);
    }
    std::sort(M.elements.begin(), M.elements.end(), element::comp);

    M.cycles.assign(1ul << n, false);
    M.wasHere.assign(1ul << n, false);
    for (int i = 0; i < m; ++i) {
        long long count;
        std::cin >> count;
        long long index = 0;
        for (int j = 0; j < count; ++j) {
            long long v;
            std::cin >> v;
            index |= (1 << (v - 1));
        }
        M.cycles[index] = true;
        //fill undercycle
        if (!M.wasHere[index]) {
            M.dfs(index);
        }
    }

    long long ans = 0;
    long long curIndex = 0;
    for (auto u : M.elements) {
        long long tmp = curIndex | (1 << (u.number - 1));
        if (M.cycles[tmp]) {
            continue;
        } else {
            curIndex |= (1 << (u.number - 1));
            ans += u.weight;
        }
    }

    std::cout << ans;
    return 0;
}

