#ifndef BIGINTOPT_COPYONWRITE_H
#define BIGINTOPT_COPYONWRITE_H


#include <memory>
#include <deque>

struct CopyOnWrite {
    mutable std::shared_ptr<std::deque<uint32_t> > dequePtr;
    void ensure_unique() const;

public:
    CopyOnWrite() = default;
    CopyOnWrite(const CopyOnWrite &other);
    std::deque<uint32_t > &get();
    std::deque<uint32_t > const &get() const;
};



#endif //BIGINTOPT_COPYONWRITE_H
