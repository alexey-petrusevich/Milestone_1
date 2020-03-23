#include <iostream>

#include <cstring>

typedef unsigned char byte;

int main() {

    int* x = new int[2];
    x[0] = 5;
    x[1] = 10;
    byte* y = new byte[3 * sizeof(int)];
    memcpy(y, x, 3 * sizeof(int));

    return 0;
}