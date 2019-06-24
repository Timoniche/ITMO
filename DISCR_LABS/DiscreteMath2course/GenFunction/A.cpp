//
// Created by Timoniche on 4/13/2019.
//

#include <iostream>
#include <vector>

/*
3 2
0 1 2 3
1 2 3
 */
/*
1 3
1 2
1 4 5 2
 */

long long n;
long long m;
std::vector<long long> p_coef;
std::vector<long long> q_coef;
std::vector<long long> res_coef;

const long long MOD = 998244353;

long long mod(long long a) {
    return (MOD + (a % MOD)) % MOD;
}
//________________________________________________________
void do_sum() {
    res_coef.assign(static_cast<unsigned int>(std::max(n + 1, m + 1)), 0);
    p_coef.resize(static_cast<unsigned int>(std::max(n + 1, m + 1)), 0);
    q_coef.resize(static_cast<unsigned int>(std::max(n + 1, m + 1)), 0);
    long long non_zero_index = 0;
    for (long long i = 0; i < std::max(n + 1, m + 1); ++i) {
        res_coef[i] = mod(p_coef[i] + q_coef[i]);
        if (res_coef[i] != 0) {
            non_zero_index = i;
        }
    }
    std::cout << non_zero_index << std::endl;
    for (long long i = 0; i <= non_zero_index; ++i) {
        std::cout << res_coef[i] << " ";
    }
    std::cout << std::endl;
}

void do_mul() {
    res_coef.assign(static_cast<unsigned int>(n + m + 1), 0);
    p_coef.resize(static_cast<unsigned int>(n + m + 1), 0);
    q_coef.resize(static_cast<unsigned int>(n + m + 1), 0);
    long long non_zero_index = 0;
    for (long long i = 0; i < n + m + 1; ++i) {
        long long c_n = 0;
        for (long long k = 0; k <= i; ++k) {
            c_n = mod(c_n + mod(p_coef[k] * q_coef[i - k]));
        }
        res_coef[i] = c_n;
        if (res_coef[i] != 0) {
            non_zero_index = i;
        }
    }
    std::cout << non_zero_index << std::endl;
    for (long long i = 0; i <= non_zero_index; ++i) {
        std::cout << res_coef[i] << " ";
    }
    std::cout << std::endl;
}

void do_div() {
    res_coef.assign(2000, 0);
    p_coef.resize(2000, 0);
    q_coef.resize(2000, 0);

    for (long long i = 0; i < 1000; ++i) {
        long long convolution = 0;
        for (long long k = 0; k < i; ++k) {
            convolution = mod(convolution + mod(res_coef[k] * q_coef[i - k]));
        }
        long long c_n = mod(p_coef[i] - convolution);
        res_coef[i] = c_n;
        std::cout << res_coef[i] << " ";
    }
}
//________________________________________________________

int main() {
    std::cin >> n >> m;
    for (long long i = 0; i < n + 1; ++i) {
        long long p;
        std::cin >> p;
        p_coef.push_back(p);
    }
    for (long long i = 0; i < m + 1; ++i) {
        long long q;
        std::cin >> q;
        q_coef.push_back(q);
    }
    do_sum();
    do_mul();
    do_div();

    return 0;
}