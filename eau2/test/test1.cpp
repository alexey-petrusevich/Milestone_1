#include <iostream>

#include <cstring>

typedef unsigned char byte;

int main() {

    int* x = new int[2];
    x[0] = 5;
    x[1] = 10;
    byte* y = new byte[2 * sizeof(int)];
    memcpy(y, x, 2 * sizeof(int));

    int* z = new int[2];
    memcpy(z, y, 2 * sizeof(int));

    printf("z[%zu]: %d\n", 0, z[0]);
    printf("z[%zu]: %d\n", 1, z[1]);

    return 0;
}