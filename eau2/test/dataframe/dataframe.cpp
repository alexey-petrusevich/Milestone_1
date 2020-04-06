#include <iostream>

void FAIL() { exit(1); }
void OK(const char* m) {
    const char* filename = "[test_serialization.cpp]";
    printf("%s %s: [passed]\n", filename, m);
}
void t_true(bool p) {
    if (!p) FAIL();
}
void t_false(bool p) {
    if (p) FAIL();
}


int main() {
    return 0;
}