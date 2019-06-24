#include <random>
#include <iostream>

std::mt19937 gen{0}; //NOLINT
std::uniform_int_distribution<> int_dist{0, std::numeric_limits<int>::max()}; //NOLINT

typedef long long ll;

namespace MillerTest
{
    ll mul(ll a, ll n, ll m)
    {
        ll r = 0;
        while (n > 0)
        {
            if (n % 2 == 1)
            {
                r = (r + a) % m;
            }
            a = (a + a) % m;
            n /= 2;
        }
        return r;
    }

    ll pow(ll x, ll y, ll p)
    {
        ll res = 1;
        x = x % p;
        while (y > 0)
        {
            if (y & 1)
            {
                res = mul(res, x, p);
            }
            y = y >> 1;
            x = mul(x, x, p);
        }
        return res;
    }

    bool miller_test(ll d, ll n)
    {
        ll a = 2 + int_dist(gen) % (n - 4);
        ll x = pow(a, d, n);
        if (x == 1 || x == n - 1)
        {
            return true;
        }
        while (d != n - 1)
        {
            x = mul(x, x, n);
            d = mul(d, d, std::numeric_limits<ll>::max());

            if (x == 1)
            {
                return false;
            }
            if (x == n - 1)
            {
                return true;
            }
        }
        return false;
    }


    bool is_prime(ll n, int k)
    {
        if (n <= 1 || n == 4)
        {
            return false;
        }
        if (n <= 3)
        {
            return true;
        }
        ll d = n - 1;
        while (d % 2 == 0)
        {
            d /= 2;
        }
        for (ll i = 0; i < k; i++)
        {
            if (!miller_test(d, n))
            {
                return false;
            }
        }
        return true;
    }
}

int main()
{
    int k = 2;
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        MillerTest::is_prime(val, k) ? std::cout << "YES\n" :
        std::cout << "NO\n";
    }
    return 0;
}
