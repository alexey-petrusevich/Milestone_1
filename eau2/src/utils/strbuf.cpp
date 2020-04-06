#include "../../include/eau2/utils/strbuf.h"
#include <cstring>
#include <cassert>
#include <iostream>

StrBuff::StrBuff() {
    val_ = new char[capacity_ = 10];
    size_ = 0;
}

void StrBuff::grow_by_(size_t step) {
    if (step + size_ < capacity_) return;
    capacity_ *= 2;
    if (step + size_ >= capacity_) capacity_ += step;
    char* oldV = val_;
    val_ = new char[capacity_];
    memcpy(val_, oldV, size_);
    delete[] oldV;
}

StrBuff& StrBuff::c(const char* str) {
    size_t step = strlen(str);
    grow_by_(step);
    memcpy(val_ + size_, str, step);
    size_ += step;
    return *this;
}

StrBuff& StrBuff::c(String& s) { return c(s.c_str()); }

StrBuff& StrBuff::c(size_t v) { return c(std::to_string(v).c_str()); }  // Cpp

String* StrBuff::get() {
    assert(val_ != nullptr);  // can be called only once
    grow_by_(1);              // ensure space for terminator
    val_[size_] = 0;          // terminate
    String* res = new String(true, val_, size_);
    val_ = nullptr;  // val_ was consumed above
    return res;
}