#ifndef OPTIONAL_OPTIONAL_H
#define OPTIONAL_OPTIONAL_H

#include <type_traits>
#include <cassert>

template<typename T>
struct optional {

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_;
    bool isInitialised;

public:
    optional() : isInitialised(false) {}

    ~optional() {
        clear();
    }

    optional(optional const &rhs) : isInitialised(rhs.isInitialised) {
        if (isInitialised) {
           new(&data_) T(*rhs);
        }
    }

    //can't be explicit
    optional(T const &rhs) { //NOLINT
        new(&data_) T(rhs);
        isInitialised = true;
    }

    optional &operator=(const optional &rhs) {
        optional tmpRhs(rhs);
        swap(*this, tmpRhs);
        return *this;
    }


    void clear() {
        if (isInitialised) {
           reinterpret_cast<T &>(data_).~T();
           isInitialised = false;
        }
    }

    explicit operator bool() const {
        return isInitialised;
    }

    T &operator*() {
        assert(isInitialised);
        return *reinterpret_cast<T *>(&data_);
    }

    T const &operator*() const {
        assert(isInitialised);
        return *reinterpret_cast<T const  *>(&data_);
    }

    T *operator->() {
        assert(isInitialised);
        return reinterpret_cast<T*>(&data_);
    }

    T const *operator->() const {
        assert(isInitialised);
        return reinterpret_cast<T const *>(&data_);
    }


    //Public_interface___________________________________________________________________________________________
    friend void swap(optional &a, optional &b) {
        if (!a.isInitialised && !b.isInitialised) {
            //do nothing
        }
        if (a.isInitialised && b.isInitialised) {
            std::swap(*reinterpret_cast<T *>(&a.data_), *reinterpret_cast<T *>(&b.data_));
        }
        else if (a.isInitialised) {
            new(reinterpret_cast<T *>(&b.data_)) T(*a);
            a.clear();
            b.isInitialised = true;
        }
        else if (b.isInitialised){
            swap(b, a);
        }
    }

    friend bool operator==(optional<T> const &l_opt, optional<T> const &r_opt) {
        return (!l_opt.isInitialised && !r_opt.isInitialised) || (l_opt.isInitialised && r_opt.isInitialised &&
                                                                  *l_opt == *r_opt);
    }

    friend bool operator!=(optional<T> const &l_opt, optional<T> const &r_opt) {
        return !(l_opt == r_opt);
    }

    friend bool operator<(optional<T> const &l_opt, optional<T> const &r_opt) {
        if (l_opt == r_opt) return false;
        if (!r_opt.isInitialised) return false;
        return !l_opt.isInitialised || *l_opt < *r_opt;
    }

    friend bool operator>(optional<T> const &l_opt, optional<T> const &r_opt) {
        return r_opt < l_opt;
    }

    friend bool operator<=(optional<T> const &l_opt, optional<T> const &r_opt) {
        return (l_opt < r_opt) || (l_opt == r_opt);
    }

    friend bool operator>=(optional<T> const &l_opt, optional<T> const &r_opt) {
        return (l_opt > r_opt) || (l_opt == r_opt);
    }

};

#endif //OPTIONAL_OPTIONAL_H
