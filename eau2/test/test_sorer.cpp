#include <iostream>

#include "../src/sorer.h"

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

void testSingleValue() {
    SOR* sor = new SOR();
    FILE* file = fopen("/home/alexey/NEU/CS_4500/Project/eau2/test/test.sor", "r");
    if (file == nullptr) {
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    printf("num rows: %d\n", df->get_schema().numRows);
    printf("num cols: %d\n", df->get_schema().numCols);
    printf("sorer col array size: %d\n", sor->columnArray->size());
    printf("sorer col array 0 size: %d\n", sor->columnArray->get(0)->size());
    printf("sorer col array 0 type: %c\n", sor->columnArray->get(0)->get_type_char());
    
    df->print();
}

int main() {
    testSingleValue();
    return 0;
}
