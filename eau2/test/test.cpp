#include <iostream>

enum class Alpha {
    A = 'a',
    B = 'b'
};

int main() {
    Alpha val_enum;
    char val_char = static_cast<char>(Alpha::A);
    printf("value of char: %c\n", val_char);
    val_enum = static_cast<Alpha>('a');
    printf("enums equals: %s\n", Alpha::A == val_enum ? "true" : "false");
    return 0;
}