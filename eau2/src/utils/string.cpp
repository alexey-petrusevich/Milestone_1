#include "../../include/eau2/utils/string.h"

#include <cassert>
#include <cstring>
#include <string>

String::String(char const* cstr, size_t len) {
    size_ = len;
    cstr_ = new char[size_ + 1];
    memcpy(cstr_, cstr, size_ + 1);
    cstr_[size_] = 0;  // terminate
}

String::String(bool steal, char* cstr, size_t len) {
    assert(steal && cstr[len] == 0);
    size_ = len;
    cstr_ = cstr;
}

String::String(char const* cstr) : String(cstr, strlen(cstr)) {}

String::String(String& from) : Object(from) {
    size_ = from.size_;
    cstr_ = new char[size_ + 1];  // ensure that we copy the terminator
    memcpy(cstr_, from.cstr_, size_ + 1);
}

String::~String() { delete[] cstr_; }

size_t String::size() { return size_; }

char* String::c_str() { return cstr_; }

char String::at(size_t index) {
    assert(index < size_);
    return cstr_[index];
}

bool String::equals(Object* other) {
    if (other == this) return true;
    String* x = dynamic_cast<String*>(other);
    if (x == nullptr) return false;
    if (size_ != x->size_) return false;
    return strncmp(cstr_, x->cstr_, size_) == 0;
}

String* String::clone() { return new String(*this); }

char* String::steal() {
    char* res = cstr_;
    cstr_ = nullptr;
    return res;
}

size_t String::hash_me() {
    size_t hash = 0;
    for (size_t i = 0; i < size_; ++i)
        hash = cstr_[i] + (hash << 6) + (hash << 16) - hash;
    return hash;
}
