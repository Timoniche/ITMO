//
// Created by Timoniche on 4/14/2019.
//

/*
3 5
1 2 3
4 5 6
 */
#include <iostream>
#include <vector>

const long long MOD = 104857601;

//____________________________________________
void input(std::vector<long long> &A, std::vector<long long> &C, long long k) {
    for (long long i = 1; i <= k; ++i) {
        long long a_i;
        std::cin >> a_i;
        A[i] = a_i;
    }
    for (long long i = 1; i <= k; ++i) {
        long long c_i;
        std::cin >> c_i;
        C[i] = c_i;
    }
}

long long mod(long long a) {
    return (MOD + (a % MOD)) % MOD;
}

std::vector<long long> do_mul(std::vector<long long> &A, std::vector<long long> &Q, long long k) {
    std::vector<long long> res(k + 1, 0);
    for (long long i = 0; i <= k; ++i) {
        long long c_n = 0;
        for (long long conv = 0; conv <= i; ++conv) {
            c_n += A[conv] * Q[i - conv];
        }
        res[i] = c_n;
    }
    return res;
}

long long div_get_an(std::vector<long long> &P, std::vector<long long> &Q, long long n) {
    std::vector<long long> res_coef(n + 1, 0);
    P.resize(static_cast<unsigned long long>(n + 1), 0);
    Q.resize(static_cast<unsigned long long>(n + 1), 0);

    for (long long i = 0; i <= n; ++i) {
        long long convolution = 0;
        for (long long k = 0; k < i; ++k) {
            convolution += res_coef[k] * Q[i - k];
        }
        long long c_n = mod(P[i] - convolution);
        res_coef[i] = c_n;
    }
    return res_coef[n];
}

long long pow_with_mod(long long a, long long p) {
    long long res = a;
    if (p == 0) {
        return 1;
    }
    for (long long i = 0; i < p; ++i) {
        res = mod(res * a);
    }
    return res;
}
//____________________________________________

int main() {
    long long k, n;
    std::cin >> k >> n;
    std::vector<long long> A(k + 1, 0);
    std::vector<long long> C(k + 1, 0);
    input(A, C, k);
    //A(t) = P(t) / Q(t)
    //Q(t) = 1 - C(t)
    //C(t) = sum(i = 1..k)c(i)t^i -- the same as C
    //P(t) = Fk(t) * Q(t) mod t^k
    //Fk(t) = sum(i = 0..k-1)f(i)t^i;

    //_________________________________________
    std::vector<long long> Q(k + 1, 0);
    Q[0] = 1;
    for (long long i = 1; i <= k; ++i) {
        Q[i] = -C[i];
    }
    //_________________________________________
    std::vector<long long> Fk(k + 1, 0);
    for (long long i = 0; i < k; ++i) {
        Fk[i] = A[i + 1];
    }
    std::vector<long long> P = do_mul(Fk, Q, k);
    P[k] = 0;
    std::cout << div_get_an(P, Q, n - 1);
    return 0;
}