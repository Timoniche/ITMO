#ifndef BIGINT_DEQUE_H
#define BIGINT_DEQUE_H

#include <cassert>
#include <deque>
#include "CopyOnWrite.h"

struct deque {
    static const size_t STACK_SIZE = 30;
    bool isDequeCreated = false;
    size_t deque_size;
    union anyData {
        uint32_t smallData[STACK_SIZE];
        CopyOnWrite bigData;
        anyData() {};
        ~anyData() {};
    } _data;
    void toBig();
public:
    //constructors+destructors_____________________________
    deque();
    deque(const deque &other);
    deque(size_t size);
    deque(size_t size, uint32_t value);
    ~deque();
    //_____________________________________________________
    size_t size() const;
    bool empty() const;
    void push_back(uint32_t value);
    uint32_t pop_back();
    void push_front(uint32_t value);
    uint32_t &operator[](size_t index);
    const uint32_t &operator[](size_t index) const;
    uint32_t &back();
    static void swapBigSmall(deque::anyData &a, deque::anyData &b);
    static void swap(deque &a, deque &b);
    friend bool operator==(deque const &a, deque const &b);
    void resize(size_t capacity);
    void clear();
};


#endif //BIGINT_DEQUE_H
