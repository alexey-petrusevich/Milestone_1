#include <cassert>
#include <iostream>

#include "../src/sorer.h"

#define FILE_INT_COL "test/test_int_col.sor"
#define FILE_DOUBLE_COL "test/test_double_col.sor"
#define FILE_BOOL_COL "test/test_bool_col.sor"
#define FILE_STRING_COL "test/test_string_col.sor"
#define FILE_MIXED_COL "test/test_mixed_col.sor"

void FAIL() { exit(1); }
void OK(const char* m) { printf("%s: [passed]\n", m); }
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
        printf("failed to open %s\n", FILE_INT_COL);
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::INTEGER);
    IntColumn* column = dynamic_cast<IntColumn*>(col);
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert(column->get_int(rowIndex) ==
               static_cast<int>(rowIndex % 10 + 1));
    }
    delete sor;
    delete df;
    fclose(file);
    OK("test_int_col");
}

void testDoubleColumn() {
    SOR* sor = new SOR();
    // TODO change this filename??
    FILE* file = fopen(FILE_DOUBLE_COL, "r");
    if (file == nullptr) {
        printf("failed to open %s\n", FILE_DOUBLE_COL);
        FAIL();
    }
    printf("reading from file\n");
    sor->read(file, 0, 100);
    printf("completed reading from file\n");
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    printf("passed assert schema\n");
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::DOUBLE);
    printf("passed assert before for loop\n");
    DoubleColumn* column = dynamic_cast<DoubleColumn*>(col);
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert((column->get_double(rowIndex) - static_cast<double>(1 + 0.1 * (rowIndex % 10))) < 1E-14);
    }
    printf("deleting\n");
    delete sor;
    delete df;
    fclose(file);
    OK("test_double_col");
}

void testBoolColumn() {
    SOR* sor = new SOR();
    // TODO change this filename??
    FILE* file = fopen(FILE_BOOL_COL, "r");
    if (file == nullptr) {
        printf("failed to open %s\n", FILE_BOOL_COL);
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::BOOLEAN);
    BoolColumn* column = dynamic_cast<BoolColumn*>(col);
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert(column->get_bool(rowIndex) ==
               static_cast<bool>((rowIndex + 1) % 2));
    }
    printf("deleting\n");
    delete sor;
    delete df;
    fclose(file);
    OK("test_bool_col");
}

void testStringColumn() {}

void testMixedColumns() {}

int main() {
    testIntColumn();

    testDoubleColumn();
    testBoolColumn();
    /*
    testStringColumn();
    testMixedColumns();
    */
    return 0;
}
