#include "../../include/eau2/utils/counter.h"

Counter::Counter() { next_ = 0; }

size_t Counter::next() {
    size_t r = next_++;
    return r;
}

size_t Counter::prev() {
    size_t r = next_--;
    return r;
}

size_t Counter::current() { return next_; }
