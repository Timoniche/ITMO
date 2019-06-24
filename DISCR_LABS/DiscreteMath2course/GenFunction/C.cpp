//
// Created by Timoniche on 4/14/2019.
//

#include <iostream>
#include <vector>

const long long MOD = static_cast<long long>(1e9 + 7);

long long mod(long long a) {
    return (MOD + (a % MOD)) % MOD;
}

void validate_SQR(std::vector<long long>* A, std::vector<long long>* A2, long long w) {
    for (long long k = 0; k <= w; ++k) {
        (*A2)[w] = mod((*A2)[w] + (*A)[k] * (*A)[w - k]);
    }
}
//_________________________________________________________________________

int main()
{
    long long k, m;
    std::cin >> k >> m;
    std::vector<long long> C(2002, 0);
    for (long long i = 0; i < k; ++i) {
        long long c_k;
        std::cin >> c_k;
        C[c_k]++;
    }
    std::vector<long long> tree_count(2002, 0);
    std::vector<long long> tree_count_SQR(2002, 0);
    tree_count[0] = tree_count_SQR[0] = 1;
    //    root
    //   /    \
    //  A      B   T*T - give all combinations of A-B
    for (long long w = 1; w <= m; ++w) {
        for (long long r = 1; r <= w; ++r) {
            if (C[r] > 0) { 
                tree_count[w] = mod(tree_count[w] + tree_count_SQR[w - r]); 
            }
        }
        validate_SQR(&tree_count, &tree_count_SQR, w);
    }
    for (long long i = 1; i <= m; ++i) {
        std::cout << tree_count[i] << " ";
    }
    return 0;
}