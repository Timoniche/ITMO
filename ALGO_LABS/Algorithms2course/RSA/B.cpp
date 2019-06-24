#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

typedef long long ll;

//______________________________________________________________________________________________________________________
struct FactoringOut
{
private:
    static const unsigned long MAX_VALUE = static_cast<const unsigned long>(1e6 + 1);
    std::vector<int> m_small_prime;
public:
    FactoringOut()
    {
        m_small_prime.resize(MAX_VALUE);
        fill_primes();
    }

public:
    inline void fill_primes();

    inline void cout_factoring(int x);
};
//______________________________________________________________________________________________________________________

inline void FactoringOut::fill_primes()
{
    std::iota(m_small_prime.begin(), m_small_prime.end(), 0);
    for (long i = 2; i <= MAX_VALUE; ++i) {
        if (m_small_prime[i] == i) {
            ll sqr = i * 1ll * i;
            for (ll j = sqr; j <= MAX_VALUE; j += i) {
                m_small_prime[j] = i;
            }
        }
    }
}

inline void FactoringOut::cout_factoring(int x)
{
    std::vector<int> output;
    while (x != 1) {
        output.push_back(m_small_prime[x]);
        x = x / m_small_prime[x];
    }
    std::sort(output.begin(), output.end());
    //std::ostream_iterator<int> out_it(std::cout, " ");
    //std::copy(output.begin(), output.end(), out_it);
    for (auto& val : output) {
        printf("%d ", val);
    }
}

//______________________________________________________________________________________________________________________
int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    FactoringOut factoring_utils;
    long val;
    for (long i = 0; i < n; ++i) {
        std::cin >> val;
        factoring_utils.cout_factoring(val);
        //std::cout << std::endl;
        printf("\n");
    }
    return 0;
}