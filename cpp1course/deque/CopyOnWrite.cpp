#include "CopyOnWrite.h"

void CopyOnWrite::ensure_unique() const {
    if (!dequePtr.unique()) {
        auto ptr = new std::deque<uint32_t>(*(dequePtr));
        dequePtr.reset(ptr);
    }
}

CopyOnWrite::CopyOnWrite(const CopyOnWrite &other) : dequePtr(other.dequePtr) {}

std::deque<uint32_t> const &CopyOnWrite::get() const {
    return *(dequePtr.get());
}

std::deque<uint32_t> & CopyOnWrite::get() {
    ensure_unique();
    return *(dequePtr.get());
}