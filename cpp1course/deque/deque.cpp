#include "deque.h"
#include <cstring>

//constructors+destructors________________________________________________________________
deque::deque() : deque_size(0) {}

deque::deque(const deque &other) : deque_size(other.deque_size), isDequeCreated(other.isDequeCreated) {
    if (other.isDequeCreated) {
        new (&_data.bigData) std::shared_ptr<std::deque<uint32_t>>(other._data.bigData.dequePtr);
    } else {
        std::copy(other._data.smallData, other._data.smallData + STACK_SIZE, _data.smallData);
    }
}

deque::deque(size_t size) : deque_size(size) {
    if (deque_size > STACK_SIZE) {
        isDequeCreated = true;
        new (&_data.bigData) std::shared_ptr<std::deque<uint32_t>>(new std::deque<uint32_t>(size));
    }
}

deque::deque(size_t size, uint32_t value) : deque_size(size) {
    if (deque_size > STACK_SIZE) {
        isDequeCreated = true;
        new (&_data.bigData) std::shared_ptr<std::deque<uint32_t>>(new std::deque<uint32_t>(size, value));
    } else {
        std::fill(_data.smallData, _data.smallData + STACK_SIZE, value);
    }
}

deque::~deque() {
    if (isDequeCreated) {
        _data.bigData.dequePtr.reset();
    }
}
//________________________________________________________________________________________
size_t deque::size() const {
    return deque_size;
}

bool deque::empty() const {
    return deque_size == 0;
}

void deque::push_back(uint32_t value) {
    if (!isDequeCreated && deque_size < STACK_SIZE) {
        _data.smallData[deque_size] = value;
    } else {
        if (!isDequeCreated) {
            toBig();
        }
        _data.bigData.get().push_back(value);
    }
    deque_size++;
}

uint32_t deque::pop_back() {
    assert(deque_size != 0);
    if (!isDequeCreated) {
        return _data.smallData[--deque_size];
    } else {
        uint32_t t = _data.bigData.get().back();
        _data.bigData.get().pop_back();
        deque_size--;
        return t;
    }
}

void deque::push_front(uint32_t value) {
    if (!isDequeCreated && deque_size < STACK_SIZE) {
        for (size_t i = deque_size; i > 0; --i) {
            _data.smallData[i] = _data.smallData[i - 1];
        }
        _data.smallData[0] = value;
    } else {
        if (!isDequeCreated) {
            toBig();
        }
        _data.bigData.get().push_front(value);
    }
    deque_size++;
}

uint32_t &deque::operator[](size_t index) {
    assert(index < deque_size);
    if (isDequeCreated) {
        return _data.bigData.get().at(index);
    } else {
        return _data.smallData[index];
    }
}

const uint32_t &deque::operator[](size_t index) const {
    assert(index < deque_size);
    if (isDequeCreated) {
        return _data.bigData.get().at(index);
    } else {
        return _data.smallData[index];
    }
}

uint32_t &deque::back() {
    assert(deque_size > 0);
    if (isDequeCreated) {
        return _data.bigData.get().back();
    } else {
        return _data.smallData[deque_size - 1];
    }
}

void deque::swapBigSmall(deque::anyData &big, deque::anyData &small) {
    uint32_t tmp[STACK_SIZE];
    std::copy(small.smallData, small.smallData + STACK_SIZE, tmp);
    new(&small.bigData) std::shared_ptr<std::deque<uint32_t>>(big.bigData.dequePtr);
    big.bigData.dequePtr.reset();
    std::copy(tmp, tmp + STACK_SIZE, big.smallData);
}

void deque::swap(deque &a, deque &b) {
    if (!a.isDequeCreated && !b.isDequeCreated) {
        for (size_t i = 0; i < STACK_SIZE; i++) {
            std::swap(a._data.smallData[i], b._data.smallData[i]);
        }
    } else if (a.isDequeCreated && b.isDequeCreated) {
        std::swap(a._data.bigData, b._data.bigData);
    } else if (a.isDequeCreated) {
        swapBigSmall(a._data, b._data);
    } else {
        swapBigSmall(b._data, a._data);
    }
    std::swap(a.isDequeCreated, b.isDequeCreated);
    std::swap(a.deque_size, b.deque_size);
}

bool operator==(deque const &a, deque const &b) {
    if (a.deque_size != b.deque_size) {
        return false;
    } else {
        for (size_t i = 0; i < a.deque_size; ++i) {
            if (a[i] != b[i]) {
                return false;
            }
        }
    }
    return true;
}

void deque::resize(size_t capacity) {
    if (capacity > STACK_SIZE) {
        if (!isDequeCreated) {
            toBig();
        }
        _data.bigData.get().resize(capacity);
    }
    deque_size = capacity;
}
void deque::clear() {
    if (isDequeCreated) {
        _data.bigData.get().clear();
    }
    deque_size = 0;
}

void deque::toBig() {
    isDequeCreated = true;
    uint32_t tmp[STACK_SIZE];
    std::copy(_data.smallData, _data.smallData + STACK_SIZE, tmp);
    new (&_data.bigData) std::shared_ptr<std::deque<uint32_t>>(new std::deque<uint32_t>());
    for (size_t i = 0; i < deque_size; ++i) {
        _data.bigData.get().push_back(tmp[i]);
    }
}
