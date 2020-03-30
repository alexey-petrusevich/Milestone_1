#include <iostream>
#include <cassert>
#include "../src/sorer.h"

#define FILE_INT_COL "test/test_int_col.sor"
#define FILE_DOUBLE_COL "test/test_double_col.sor"
#define FILE_BOOL_COL "test/test_bool_col.sor"
#define FILE_STRING_COL "test/test_string_col.sor"
#define FILE_MIXED_COL "test/test_mixed_col.sor"

void FAIL() { exit(1); }
void OK(const char* m) {
    printf("%s: [passed]\n", m);
}
void t_true(bool p) {
    if (!p) FAIL();
}
void t_false(bool p) {
    if (p) FAIL();
}

void testIntColumn() {
    SOR* sor = new SOR();
    // TODO change this filename??
    FILE* file = fopen(FILE_INT_COL, "r");
    if (file == nullptr) {
        printf("failed to open file\n");
        
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::INTEGER);
    IntColumn* int_col = dynamic_cast<IntColumn*>(col);
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert(int_col->get_int(rowIndex) == static_cast<int>(rowIndex % 10 + 1));
    }
    printf("deleting\n");
    delete df;
    delete sor;
    OK("test_int_col");
}

void testDoubleColumn() {

}

void testBoolColumn() {

}

void testStringColumn() {

}

void testMixedColumns() {

}

int main() {
    testIntColumn();
    /*
    testDoubleColumn();
    testBoolColumn();
    testStringColumn();
    testMixedColumns();
    */
    return 0;
}
