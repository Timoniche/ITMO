#include <iostream>

typedef long long ll;

ll n, e, C;

ll gcd_extended(ll a, ll b, ll &x, ll &y)
{
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1;
    ll y1;
    ll d = gcd_extended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

struct BreakRSA
{
public:
    ll p = 0;
    ll q = 0;
    ll fi = 0;
    ll d = 0;
    ll M = 1;
public:
    void get_p_q(ll n)
    {
        p = 2;
        for (;; ++p) {
            if (n % p == 0) {
                q = n / p;
                break;
            }
        }
    }

    inline void count_fi()
    {
        fi = (p - 1) * (q - 1);
    }

    ll get_M()
    {
        ll ignored;
        gcd_extended(e, fi, d, ignored);
        while (d < 0) {
            d += fi;
        }
        for (;;) {
            if (d % 2 == 0) {
                C *= C;
                C %= n;
                d /= 2;
            } else {
                M *= C;
                M %= n;
                d--;
                if (d == 0) {
                    break;
                }
            }
        }
        return M;
    }

};

/**
 * n = p * q
 * e * d = 1 ± od{(p - 1)(q - 1)}
 * {(p - 1)(q - 1) = fi}
 * n, e - open keys
 * C = M^e (mod n) encryption
 * C = M^d (mod n) decryption
 */
int main()
{
    std::cin >> n >> e >> C;
    BreakRSA breaker;
    breaker.get_p_q(n);
    breaker.count_fi();
    std::cout << breaker.get_M();
    return 0;
}