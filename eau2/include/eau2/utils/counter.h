#pragma once
#include <atomic>

#include "object.h"

/** A simple thread-safe counter. */
class Counter : public Object {
   public:
    std::atomic<size_t> next_;

    Counter();

    size_t next();
    size_t prev();

    size_t current();
};
