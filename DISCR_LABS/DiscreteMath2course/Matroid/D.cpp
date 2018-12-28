#include <iostream>

#include <map>
#include <vector>


/**faster implementation*/
/*Pre:
2 4
0
1 1
1 2
2 1 2
Post: YES*/

/*Pre:
2 3
0
1 1
2 1 2
Post: NO*/

typedef std::pair<int, std::vector<int>> piv;

struct ICheck {
    int n;
    unsigned long MAXN = 0;
    std::vector<piv> Masks;
    std::vector<bool> hasMask;
    //elements numbered from 0
    //int - 1101101 ("1" - used element in vector)
    //vector - elements

    explicit ICheck(int n) : n(n) {
        MAXN = 1ul << n;
    }

    //if A in I & B in A => B in I
    bool ok_second() {
        //0 is checked
        bool subset[MAXN];
        for (int i = 0; i < MAXN; ++i) {
            subset[i] = true;
        }
        for (int i = 1; i < MAXN; i++) {
            if (hasMask[i]) {
                int max_pow = 0;
                while (i >= (1 << max_pow)) {
                    int mask = ~(1 << max_pow);
                    subset[i] = subset[i & mask] & subset[i];
                    max_pow++;
                }
            } else {
                subset[i] = false;
            }

        }

        for (auto u : Masks)
            if (!subset[u.first]) {
                return false;
            }
        return true;
    }

    //if A, B in I, if |A| > |B| then exist x (A\B): B + x in I
    //in code consider a > b
    bool ok_third() {
        for (auto a = Masks.begin(); a != Masks.end(); ++a) {
            for (auto b = a; b != Masks.end(); ++b) {
                if (a->second.size() != b->second.size()) {
                    std::vector<bool> a_b = checkAB(a->second, b->second);
                    bool check = false;
                    for (int i = 0; i < n; i++) {
                        if (a_b[i]) {
                            int mask = 1 << i;
                            int bitset = 0;
                            if (a->second.size() > b->second.size()) {
                                bitset = b->first | mask;
                            } else {
                                bitset = a->first | mask;
                            }
                            check |= hasMask[bitset];
                        }
                    }
                    if (!check) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    std::vector<bool> checkAB(std::vector<int> a, std::vector<int> b) {
        std::vector<bool> ret(static_cast<unsigned long>(n));
        if (a.size() < b.size()) std::swap(a, b);
        for (int i : a)
            ret[i] = true;
        for (int i : b)
            ret[i] = false;
        return ret;
    }
};
int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;
    ICheck I(n);

    I.hasMask.assign(1ul << n, false);
    bool wasZeroElement = false;
    for (int i = 0; i < m; ++i) {
        int size_elements;
        std::cin >> size_elements;
        if (size_elements == 0) {
            wasZeroElement = true;
        } else {
            int keyMerge = 0;
            std::vector<int> tmp;
            for (int j = 0; j < size_elements; ++j) {
                int element;
                std::cin >> element;
                element--;
                keyMerge |= 1 << element;
                tmp.push_back(element);
            }
            I.Masks.emplace_back(keyMerge, std::move(tmp));
            I.hasMask[keyMerge] = true;
        }
    }

    //Theorem
    //0 in I
    if (!wasZeroElement) {
        std::cout << "NO";
        exit(0);
    }
    //if A in I & B in A => B in I
    bool ret2 = I.ok_second();
    if (!ret2) {
        std::cout << "NO";
        exit(0);
    }
    //if A, B in I, if |A| > |B| then exist x (A\B): B + x in I
    bool ret3 = I.ok_third();
    if (!ret3) {
        std::cout << "NO";
        exit(0);
    }

    std::cout << "YES";

    return 0;
}


