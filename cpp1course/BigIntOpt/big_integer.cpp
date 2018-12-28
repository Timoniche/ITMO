#include <iostream>
#include "big_integer.h"
#include <climits>

big_integer::big_integer() : isNegative(false) {}

big_integer::big_integer(big_integer const &other) : isNegative(other.isNegative), data_(other.data_) {}

big_integer::big_integer(int a) : isNegative(a < 0) {
    if (a) {
        data_.push_back(static_cast<uint32_t>(std::abs(static_cast<int64_t>(a))));
    }
}

big_integer::big_integer(uint32_t a) : isNegative(false) {
    if (a) {
        data_.push_back(static_cast<uint32_t>(std::abs(static_cast<int64_t>(a))));
    }
}

big_integer mul_long_int_unsigned(big_integer const &a, uint32_t const &b) {
    big_integer res;
    res.data_.resize(a.data_.size());

    uint32_t carry = 0;
    for (size_t i = 0; i < a.data_.size(); i++) {
        uint64_t tmp_res = static_cast<uint64_t>(a.data_[i]) * b + carry;
        res.data_[i] = static_cast<uint32_t>(tmp_res & UINT32_MAX);
        carry = static_cast<uint32_t>(tmp_res >> 32);
    }
    res.data_.push_back(carry);

    res.correct_size();
    return res;
}

big_integer::big_integer(std::string const &str) {
    data_.clear();
    data_.push_back(0);
    isNegative = false;
    for (char c : str) {
        if (c == '+') {
            isNegative = false;
            continue;
        }
        if (c == '-') {
            isNegative = true;
            continue;
        }
        if (data_.empty() && c != '0') isNegative = false;;
        mul(10);
        add((uint32_t) (c - '0'));
    }
    if (isNegative && !data_.back()) {
        isNegative = false;
    }
}

big_integer::~big_integer() {
    data_.~deque();
}
big_integer &big_integer::operator=(big_integer const &other) {
    big_integer tmp(other);
    isNegative = tmp.isNegative;
    deque::swap(data_, tmp.data_);
    return *this;
}

big_integer big_integer::abs(big_integer const &a) {
    big_integer res(a);
    res.isNegative = false;
    return res;
}

big_integer &big_integer::operator+=(big_integer const &rhs) {
    if (isNegative != rhs.isNegative) {
        *this -= -rhs;
        return *this;
    }
    deque res(std::max(data_.size(), rhs.data_.size()));
    uint64_t carry = 0;
    for (size_t i = 0; i < std::min(data_.size(), rhs.data_.size()); i++) {
        carry += static_cast<uint64_t>(data_[i]) + rhs.data_[i];
        res[i] = static_cast<uint32_t>(carry) & UINT32_MAX;
        carry >>= 32;
    }
    for (size_t i = data_.size(); i < rhs.data_.size(); i++) {
        carry += static_cast<uint64_t>(rhs.data_[i]);
        res[i] = static_cast<uint32_t>(carry) & UINT32_MAX;
        carry >>= 32;
    }
    for (size_t i = rhs.data_.size(); i < data_.size(); i++) {
        carry += static_cast<uint64_t>(data_[i]);
        res[i] = static_cast<uint32_t>(carry) & UINT32_MAX;
        carry >>= 32;
    }
    if (carry) {
        res.push_back(static_cast<uint32_t>(carry));
    }
    deque::swap(res, data_);
    correct_size();
    return *this;
}

big_integer &big_integer::operator-=(big_integer const &rhs) {
    if (isNegative != rhs.isNegative) {
        *this += -rhs;
        return *this;
    }
    const big_integer *min;
    const big_integer *max;
    if (abs(*this) <= abs(rhs)) {
        min = this;
        max = &rhs;
    } else {
        min = &rhs;
        max = this;
    }
    deque res(max->data_.size(), 0);
    bool borrow = false;
    for (size_t i = 0; i < res.size(); i++) {
        int64_t cur = max->data_[i];
        int64_t sub;
        if (i >= min->data_.size()) {
            sub = static_cast<int64_t>(borrow);
        } else {
            sub = static_cast<int64_t>(borrow) + min->data_[i];
        }
        cur -= sub;
        if (cur < 0) {
            cur += static_cast<uint64_t>(1) << 32;
            borrow = true;
        } else {
            borrow = false;
        }
        res[i] = static_cast<uint32_t>(cur);
    }
    isNegative = *this < rhs;
    deque::swap(res, data_);
    correct_size();
    return *this;
}

big_integer &big_integer::operator*=(big_integer const &rhs) {
    isNegative ^= rhs.isNegative;
    deque res(data_.size() + rhs.data_.size(), 0);
    for (size_t i = 0; i < data_.size(); i++) {
        uint32_t carry = 0;
        for (size_t j = 0; j < rhs.data_.size(); j++) {
            uint64_t cur = static_cast<uint64_t>(data_[i]) * rhs.data_[j] + res[i + j] + carry;
            res[i + j] = static_cast<uint32_t> (cur & UINT32_MAX);
            carry = static_cast<uint32_t> (cur >> 32);
        }
        res[i + rhs.data_.size()] += carry;
    }
    deque::swap(res, data_);
    correct_size();
    return *this;
}

big_integer &big_integer::operator/=(big_integer const &rhs) {
    if (rhs == 0) {
        throw std::runtime_error("/0");
    }
    bool newSign = isNegative ^rhs.isNegative;
    if (*this == 0 || abs(rhs) > abs(*this)) {
        *this = 0;
    } else if (!(abs(rhs) == 1)) {
        if (rhs.data_.size() == 1) {
            uint64_t carry = 0;
            for (size_t i = data_.size(); i > 0; i--) {
                carry = (carry << 32) + data_[i - 1];
                data_[i - 1] = static_cast<uint32_t>(carry / rhs.data_[0]);
                carry %= rhs.data_[0];
            }
            correct_size();
        } else {
            *this = long_unsigned_division(*this, rhs);
        }
    }
    isNegative = newSign;
    return *this;
}

big_integer long_unsigned_division(big_integer const &l, big_integer const &r) {
    auto scaling_factor = static_cast<uint32_t>((static_cast<uint64_t> (UINT32_MAX) + 1) /
                                                (static_cast<uint64_t>(r.data_[r.data_.size() - 1]) + 1));
    big_integer a(mul_long_int_unsigned(l, scaling_factor));
    big_integer b(mul_long_int_unsigned(r,scaling_factor));
    deque result(a.data_.size() - b.data_.size() + 1);
    big_integer cur_prefix;
    cur_prefix.data_.resize(b.data_.size() - 1);
    for (size_t i = a.data_.size() - b.data_.size() + 1, index = 0; i < a.data_.size(); i++, index++) {
        cur_prefix.data_[index] = a.data_[i];
    }
    uint64_t b1 = b.data_[b.data_.size() - 1];
    for (size_t i = result.size(); i > 0; i--) {
        cur_prefix.data_.push_front(a.data_[i - 1]);
        uint64_t a2 = cur_prefix.data_[cur_prefix.data_.size() - 1];
        if (cur_prefix.data_.size() > b.data_.size()) {
            a2 = (a2 << 32) + cur_prefix.data_[cur_prefix.data_.size() - 2];
        }
        uint64_t quotient = a2 / b1;
        if (quotient >= UINT32_MAX) quotient = UINT32_MAX;
        big_integer mul_dq = b * static_cast<uint32_t>(quotient);
        while (cur_prefix < mul_dq) {
            quotient--;
            mul_dq -= b;
        }
        result[i - 1] = static_cast<uint32_t>(quotient & UINT32_MAX);
        cur_prefix -= mul_dq;
    }
    deque::swap(a.data_, result);
    a.correct_size();
    return a;
}

big_integer &big_integer::operator%=(big_integer const &rhs) {
    big_integer q = *this / rhs;
    return *this -= rhs * q;
}

void big_integer::toTwosComplement() {
    if (isNegative) {
        isNegative = false;
        for (size_t i = 0; i < data_.size(); i++) {
            data_[i] = ~data_[i];
        }
        *this += 1;
    }
}

void big_integer::toSignedForm() {
    if (data_[data_.size() - 1] >> 31) {
        for (size_t i = 0; i < data_.size(); i++) {
            data_[i] = ~data_[i];
        }
        isNegative = false;
        *this += 1;
        isNegative = true;
    }
}

void big_integer::correct_size() {
    while (!data_.empty() && data_.back() == 0) {
        data_.pop_back();
    }
    if (data_.empty()) {
        isNegative = false;
    }
}

big_integer &big_integer::operator&=(big_integer const &rhs) {
    deque res(std::max(data_.size(), rhs.data_.size()));
    toTwosComplement();
    big_integer rhsCopy = rhs;
    rhsCopy.toTwosComplement();
    for (size_t i = 0; i < std::min(data_.size(), rhs.data_.size()); i++) {
        res[i] = data_[i] & rhsCopy.data_[i];
    }
    for (size_t i = data_.size(); i < rhs.data_.size(); i++) {
        res[i] = data_[i];
    }
    for (size_t i = rhs.data_.size(); i < data_.size(); i++) {
        res[i] = rhsCopy.data_[i];
    }
    deque::swap(res, data_);
    toSignedForm();
    correct_size();
    return *this;
}

big_integer &big_integer::operator|=(big_integer const &rhs) {
    toTwosComplement();
    big_integer rhsCopy = rhs;
    rhsCopy.toTwosComplement();
    data_.resize(std::min(data_.size(), rhsCopy.data_.size()));
    for (size_t i = 0; i < std::min(data_.size(), rhsCopy.data_.size()); i++) {
        data_[i] |= rhsCopy.data_[i];
    }
    toSignedForm();
    correct_size();
    return *this;
}

big_integer &big_integer::operator^=(big_integer const &rhs) {
    deque res(std::max(data_.size(), rhs.data_.size()));
    toTwosComplement();
    big_integer rhsCopy = rhs;
    rhsCopy.toTwosComplement();
    for (size_t i = 0; i < std::min(data_.size(), rhs.data_.size()); i++) {
        res[i] = data_[i] ^ rhsCopy.data_[i];
    }
    for (size_t i = data_.size(); i < rhs.data_.size(); i++) {
        res[i] = data_[i];
    }
    for (size_t i = rhs.data_.size(); i < data_.size(); i++) {
        res[i] = rhsCopy.data_[i];
    }
    deque::swap(res, data_);
    toSignedForm();
    correct_size();
    return *this;
}

big_integer &big_integer::operator<<=(int rhs) {
    if (rhs < 0) {
        return *this >>= -rhs;
    }
    uint32_t bigShift = static_cast<uint32_t>(rhs) / 32;
    uint32_t smallShift = static_cast<uint32_t>(rhs) % 32;
    bool wasNegative = isNegative;
    toTwosComplement();
    deque res(data_.size());
    uint32_t carry = 0;
    for (size_t i = 0; i < res.size(); i++) {
        uint64_t cur = (static_cast<uint64_t>(data_[i]) << smallShift) + carry;
        res[i] = static_cast<uint32_t>(cur & UINT32_MAX);
        carry = static_cast<uint32_t>(cur >> 32);
    }
    data_.clear();
    for (size_t i = 0; i < bigShift; i++) {
        data_.push_back(0);
    }
    for (size_t i = 0; i < res.size(); i++) {
        data_.push_back(res[i]);
    }
    data_.push_back(0);
    toSignedForm();
    correct_size();
    if (wasNegative) {
        big_integer a(*this);
        for (size_t i = 0; i < data_.size(); i++) {
            a.data_[i] = ~a.data_[i];
        }
        *this = -a - 1;
    }
    return *this;
}

big_integer &big_integer::operator>>=(int rhs) {
    if (rhs < 0) {
        return *this <<= -rhs;
    }
    uint32_t bigShift = static_cast<uint32_t>(rhs) / 32;
    uint32_t smallShift = static_cast<uint32_t>(rhs) % 32;
    deque res(data_.size() - bigShift);
    uint64_t carry = 0;
    for (size_t i = res.size(); i > 0; i--) {
        uint64_t tmp = static_cast<uint64_t >(data_[i - 1]) << (32 - smallShift);
        res[i - 1] = static_cast<uint32_t>((tmp >> 32) + carry);
        carry = tmp & UINT32_MAX;
    }
    deque::swap(res, data_);
    correct_size();
    if (isNegative) {
        *this -= 1;
    }
    return *this;
}

big_integer big_integer::operator+() const {
    big_integer res = *this;
    return res;
}

big_integer big_integer::operator-() const {
    big_integer res = *this;
    res.isNegative = !isNegative;
    return res;
}

big_integer big_integer::operator~() const {
    return -(*this) - 1;
}

big_integer &big_integer::operator++() {
    *this += 1;
    return *this;
}

big_integer big_integer::operator++(int) {
    big_integer r = *this;
    ++*this;
    return r;
}

big_integer &big_integer::operator--() {
    *this -= 1;
    return *this;
}

big_integer big_integer::operator--(int) {
    big_integer r = *this;
    --*this;
    return r;
}

bool operator==(big_integer const &a, big_integer const &b) {
    return ((a.isNegative == b.isNegative) && (a.data_ == b.data_)) || (a.data_.empty() && b.data_.empty());
}

bool operator!=(big_integer const &a, big_integer const &b) {
    return !(a == b);
}

bool operator>(big_integer const &a, big_integer const &b) {
    if (a == b) { return false; }
    if (a.isNegative) {
        if (b.isNegative) {
            if (a.data_.size() > b.data_.size()) {
                return false;
            } else if (a.data_.size() < b.data_.size()) {
                return true;
            }
        } else {
            return false;
        }
    } else {
        if (b.isNegative) {
            return true;
        } else {
            if (a.data_.size() < b.data_.size()) {
                return false;
            } else if (a.data_.size() > b.data_.size()) {
                return true;
            }
        }
    }
    for (size_t i = a.data_.size() - 1;; i--) {
        if (a.data_[i] != b.data_[i]) {
            return (a.data_[i] > b.data_[i]) ^ a.isNegative;
        }
    }
    return false;
}

bool operator<(big_integer const &a, big_integer const &b) {
    return (a != b) && !(a > b);
}

bool operator<=(big_integer const &a, big_integer const &b) {
    return a == b || a < b;
}

bool operator>=(big_integer const &a, big_integer const &b) {
    return a == b || a > b;
}

big_integer operator+(big_integer a, big_integer const &b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const &b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const &b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const &b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const &b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const &b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const &b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const &b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int bits) {
    return a <<= bits;
}

big_integer operator>>(big_integer a, int bits) {
    return a >>= bits;
}

std::string to_string(big_integer const &a) {
    if (a.data_.empty()) {
        return "0";
    }
    big_integer b(a);
    std::string res;
    while (b != 0) {
        big_integer c = b % 10;
        if (c.data_.empty()) {
            std::string tmp = '0' + res;
            res = tmp;
        } else {
            std::string tmp_string = std::to_string(c[0]) + res;
            res = tmp_string;
        }
        b /= 10;
    }
    if (a.isNegative) {
        res = '-' + res;
    }
    return res;
}

void big_integer::add(uint32_t val)
{
    uint64_t tmp = val;
    for (size_t i = 0; i < data_.size(); i++) {
        tmp += (uint64_t) data_[i];
        data_[i] = (uint32_t) (tmp & UINT_MAX);
        tmp >>= 32;
        if (!tmp)
            break;
    }
    if (tmp) {
        data_.push_back((uint32_t) tmp);
    }
}

void big_integer::mul(uint32_t val)
{
    uint64_t tmp = 0;
    for (size_t i = 0; i < data_.size(); i++) {
        tmp += (uint64_t) data_[i] * (uint64_t) val;
        data_[i] = (uint32_t) (tmp & UINT_MAX);
        tmp >>= 32;
    }
    while (tmp) {
        data_.push_back((uint32_t) (tmp & UINT_MAX));
        tmp >>= 32;
    }
}

//redefine_operators___________________________________________________________
uint32_t &big_integer::operator[](size_t i) { return data_[i]; }

const uint32_t &big_integer::operator[](size_t i) const { return data_[i]; }

std::ostream &operator<<(std::ostream &s, big_integer const &a) {
    return s << to_string(a);
}
