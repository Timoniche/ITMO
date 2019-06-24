#include <iostream>
#include <vector>

std::vector<bool> prime;

bool check_prime(int n)
{
    prime.assign(size_t(n + 1), true);
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i * i <= n; ++i)
    {
        if (prime[i])
        {
            if (i * i <= n)
            {
                for (int j = i * i; j <= n; j += i)
                {
                    prime[j] = false;
                }
            }
        }
    }
    return prime[n];
}

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    check_prime(int(2e7));
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        prime[val] ? std::cout << "YES\n" :
        std::cout << "NO\n";
    }
    return 0;
}
