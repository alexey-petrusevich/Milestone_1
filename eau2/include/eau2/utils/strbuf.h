#pragma once
#include "object.h"
#include "string.h"

/** A string buffer builds a string from various pieces.
 *  author: jv */
class StrBuff : public Object {
   public:
    char* val_;  // owned; consumed by get()
    size_t capacity_;
    size_t size_;

    StrBuff();

    // how much the buffer should grow by
    void grow_by_(size_t step);

    StrBuff& c(const char* str);

    StrBuff& c(String& s);

    StrBuff& c(size_t v);

    String* get();
};

