#include "../../include/eau2/utils/helper.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

Sys& Sys::p(char* c) {
    std::cout << c;
    return *this;
}
Sys& Sys::p(bool c) {
    std::cout << c;
    return *this;
}
Sys& Sys::p(float c) {
    std::cout << c;
    return *this;
}
Sys& Sys::p(int i) {
    std::cout << i;
    return *this;
}
Sys& Sys::p(size_t i) {
    std::cout << i;
    return *this;
}
Sys& Sys::p(const char* c) {
    std::cout << c;
    return *this;
}
Sys& Sys::p(char c) {
    std::cout << c;
    return *this;
}
Sys& Sys::pln() {
    std::cout << "\n";
    return *this;
}
Sys& Sys::pln(int i) {
    std::cout << i << "\n";
    return *this;
}
Sys& Sys::pln(char* c) {
    std::cout << c << "\n";
    return *this;
}
Sys& Sys::pln(bool c) {
    std::cout << c << "\n";
    return *this;
}
Sys& Sys::pln(char c) {
    std::cout << c << "\n";
    return *this;
}
Sys& Sys::pln(float x) {
    std::cout << x << "\n";
    return *this;
}
Sys& Sys::pln(size_t x) {
    std::cout << x << "\n";
    return *this;
}
Sys& Sys::pln(const char* c) {
    std::cout << c << "\n";
    return *this;
}

char* Sys::duplicate(const char* s) {
    char* res = new char[strlen(s) + 1];
    strcpy(res, s);
    return res;
}
char* Sys::duplicate(char* s) {
    char* res = new char[strlen(s) + 1];
    strcpy(res, s);
    return res;
}

void Sys::exit_if_not(bool b, char* c) {
    if (b) return;
    p("Exit message: ").pln(c);
    exit(-1);
}

void Sys::myfail() {
    pln("Failing");
    exit(1);
}

void Sys::OK(const char* m) { pln(m); }
void Sys::t_true(bool p) {
    if (!p) myfail();
}
void Sys::t_false(bool p) {
    if (p) myfail();
}