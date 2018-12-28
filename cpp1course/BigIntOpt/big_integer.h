#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <cstddef>
#include <iosfwd>
#include <cstdint>
#include <functional>
#include <vector>
#include <deque/deque.h>

struct big_integer {
    //constructors+destructors_____________________________________________________
    big_integer();
    big_integer(big_integer const &other);
    big_integer(int a);
    big_integer(uint32_t a);
    explicit big_integer(std::string const &str);
    ~big_integer();

    //operators____________________________________________________________________
    big_integer &operator=(big_integer const &other);
    big_integer &operator+=(big_integer const &rhs);
    big_integer &operator-=(big_integer const &rhs);
    big_integer &operator*=(big_integer const &rhs);
    big_integer &operator/=(big_integer const &rhs);
    big_integer &operator%=(big_integer const &rhs);
    big_integer &operator&=(big_integer const &rhs);
    big_integer &operator|=(big_integer const &rhs);
    big_integer &operator^=(big_integer const &rhs);
    big_integer &operator<<=(int rhs);
    big_integer &operator>>=(int rhs);
    big_integer &operator++();
    big_integer &operator--();
    big_integer operator++(int);
    big_integer operator--(int);

    //unary________________________________________________________________________
    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    //compare_operators____________________________________________________________
    friend bool operator==(big_integer const &a, big_integer const &b);
    friend bool operator!=(big_integer const &a, big_integer const &b);
    friend bool operator<(big_integer const &a, big_integer const &b);
    friend bool operator>(big_integer const &a, big_integer const &b);
    friend bool operator<=(big_integer const &a, big_integer const &b);
    friend bool operator>=(big_integer const &a, big_integer const &b);
    //friend bool operator!(big_integer const &x);

    //between_operators____________________________________________________________
    friend big_integer operator+(big_integer a, big_integer const &b);
    friend big_integer operator-(big_integer a, big_integer const &b);
    friend big_integer operator*(big_integer a, big_integer const &b);
    friend big_integer operator/(big_integer a, big_integer const &b);
    friend big_integer operator%(big_integer a, big_integer const &b);
    friend big_integer operator&(big_integer a, big_integer const &b);
    friend big_integer operator|(big_integer a, big_integer const &b);
    friend big_integer operator^(big_integer a, big_integer const &b);
    friend big_integer operator<<(big_integer a, int b);
    friend big_integer operator>>(big_integer a, int b);

    //out__________________________________________________________________________
    friend std::ostream &operator<<(std::ostream &s, big_integer const &a);
    friend std::string to_string(big_integer const &a);

private:
    bool isNegative;
    deque data_;
    //std::deque<uint32_t> data_;

    //redefine_operators___________________________________________________________
    uint32_t &operator[](size_t i);
    const uint32_t &operator[](size_t i) const;

    //_____________________________________________________________________________
    void toSignedForm();
    void toTwosComplement();
    friend big_integer long_unsigned_division(big_integer const &l, big_integer const &r);
    void correct_size();
    //void invert();
    void mul(uint32_t val);
    void add(uint32_t val);
    friend big_integer mul_long_int_unsigned(big_integer const &a, uint32_t const &b);
    big_integer abs(big_integer const &a);
//    big_integer any_binary(big_integer const &a,
//                           big_integer const &b,
//                           std::function<uint32_t(uint32_t, uint32_t)> f);
    //_____________________________________________________________________________
};


#endif // BIG_INTEGER_H
