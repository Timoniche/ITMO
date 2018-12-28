#ifndef EXAM_FIXED_VECTOR_H
#define EXAM_FIXED_VECTOR_H

#include <cstddef>
#include <iterator>
#include <cassert>

template<class T, std::size_t N>

class fixed_vector {

    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

private:
    typename std::aligned_storage<sizeof(T), alignof(T)>::type data_[N];
    std::size_t size_;

    void clear_index(size_t index) {
        reinterpret_cast<T const *>(data_ + index)->~T();
    }

public:
    friend void swap(fixed_vector &a, fixed_vector &b) {
        std::swap(a.size_, b.size_);
        std::swap(a.data_, b.data_);
    }

    fixed_vector() : size_(0) {};

    fixed_vector(const fixed_vector &rhs) {
        size_ = rhs.size_;
        for (size_t i = 0; i < size_; ++i) {
            push_back(rhs[i]);
        }
    }

    fixed_vector &operator=(const fixed_vector &rhs) {
        fixed_vector tmpRhs(rhs);
        swap(*this, tmpRhs);
        tmpRhs.~fixed_vector();
        return *this;
    }

    ~fixed_vector() {
        for (size_t i = 0; i < size_; ++i) {
            clear_index(i);
        }
        size_ = 0;
    }

    T &operator[](size_t index) {
        return *(reinterpret_cast<T *>(&data_[index]));
    }

    T const &operator[](size_t index) const {
        return *(reinterpret_cast<T const *>(&data_[index]));
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return N;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_back(T const &val) {
        new(&data_[size_++]) T(val);
    }

    void pop_back() {
        clear_index(size_ - 1);
        size_--;
    }

    T &back() {
        return operator[](size_ - 1);
    }

    T const &back() const {
        return operator[](size_ - 1);
    }

    T &front() {
        assert(!empty());
        return operator[](0);
    }

    T const &front() const {
        assert(!empty());
        return operator[](0);
    }

    void clear() {
        while (!empty()) { pop_back(); }
    }

    //Post: move reference to next value
    iterator erase(const_iterator pos) {
        auto index = static_cast<size_t>(std::distance(cbegin(), pos));
        for (size_t i = index; i < size_ - 1; ++i) {
            operator[](i) = operator[](i + 1);
        }
        pop_back();
        return iterator(pos);
    }

    iterator erase(const_iterator begin, const_iterator end) {
        for (const_iterator ci = begin; ci != end; end--) {
            ci = erase(ci);
        }
        return iterator(end);
    }

    iterator insert(const_iterator pos, T const &value) {
        auto index = static_cast<size_t>(std::distance(cbegin(), pos));
        push_back(back());
        for (size_t i = size_ - 1; i > index; --i) {
            operator[](i) = operator[](i - 1);
        }
        operator[](index) = value;
        return iterator(pos);
    }

    //Iterators___________________________________________________________________________

    iterator begin() {
        return reinterpret_cast<T *>(data_);
    }

    iterator end() {
        return begin() + size_;
    }

    const_iterator begin() const {
        return reinterpret_cast<T const *>(data_);
    }

    const_iterator end() const {
        return begin() + size_;
    }

    const_iterator cend() const {
        return end();
    }

    const_iterator cbegin() const {
        return begin();
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
};


#endif //EXAM_FIXED_VECTOR_H
