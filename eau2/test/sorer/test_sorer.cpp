#include <cassert>
#include <cstring>
#include <iostream>

#include "../../include/eau2/sorer/sorer.h"
#include "../../include/eau2/utils/helper.h"

#define FILE_INT_COL "test/sorer/input/test_int_col.sor"
#define FILE_DOUBLE_COL "test/sorer/input/test_double_col.sor"
#define FILE_BOOL_COL "test/sorer/input/test_bool_col.sor"
#define FILE_STRING_COL "test/sorer/input/test_string_col.sor"
#define FILE_MIXED_COL "test/sorer/input/test_mixed_col.sor"

void FAIL() { exit(1); }
void OK(const char* m) {
    const char* filename = "[test_sorer.cpp]";
    printf("%s %s: [passed]\n", filename, m);
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
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::DOUBLE);
    DoubleColumn* column = dynamic_cast<DoubleColumn*>(col);
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert((column->get_double(rowIndex) -
                static_cast<double>(1 + 0.1 * (rowIndex % 10))) < 1E-14);
    }
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
    delete sor;
    delete df;
    fclose(file);
    OK("test_bool_col");
}

void testStringColumn() {
    SOR* sor = new SOR();
    // TODO change this filename??
    FILE* file = fopen(FILE_STRING_COL, "r");
    if (file == nullptr) {
        printf("failed to open %s\n", FILE_STRING_COL);
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 1);
    assert(df->schema->numRows == 100);
    Column* col = df->columns->get(0);
    assert(col->colType == ColType::STRING);
    StringColumn* column = dynamic_cast<StringColumn*>(col);
    char buffer[16];
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        sprintf(
            buffer, "%c",
            static_cast<char>(rowIndex % 10 + 0x61));  // 0x61 is ASCII for 'a'
        assert(strcmp(column->get_string(rowIndex)->cstr_, buffer) == 0);
    }
    delete sor;
    delete df;
    fclose(file);
    OK("test_string_col");
}

void testMixedColumns() {
    SOR* sor = new SOR();
    // TODO change this filename??
    FILE* file = fopen(FILE_MIXED_COL, "r");
    if (file == nullptr) {
        printf("failed to open %s\n", FILE_MIXED_COL);
        FAIL();
    }
    sor->read(file, 0, 100);
    DataFrame* df = sor->get_dataframe();
    assert(df->schema->numCols == 4);
    assert(df->schema->numRows == 100);
    Column* col_0 = df->columns->get(0);
    Column* col_1 = df->columns->get(1);
    Column* col_2 = df->columns->get(2);
    Column* col_3 = df->columns->get(3);
    assert(col_0->colType == ColType::INTEGER);
    assert(col_1->colType == ColType::DOUBLE);
    assert(col_2->colType == ColType::BOOLEAN);
    assert(col_3->colType == ColType::STRING);
    IntColumn* int_col = dynamic_cast<IntColumn*>(col_0);
    DoubleColumn* double_col = dynamic_cast<DoubleColumn*>(col_1);
    BoolColumn* bool_col = dynamic_cast<BoolColumn*>(col_2);
    StringColumn* string_col = dynamic_cast<StringColumn*>(col_3);

    char buffer[16];
    for (size_t rowIndex = 0; rowIndex < df->schema->numRows; rowIndex++) {
        assert(int_col->get_int(rowIndex) ==
               static_cast<int>(rowIndex % 10 + 1));
        assert((double_col->get_double(rowIndex) -
                static_cast<double>(1 + 0.1 * (rowIndex % 10))) < 1E-14);
        assert(bool_col->get_bool(rowIndex) ==
               static_cast<bool>((rowIndex + 1) % 2));
        sprintf(
            buffer, "%c",
            static_cast<char>(rowIndex % 10 + 0x61));  // 0x61 is ASCII for 'a'
        assert(strcmp(string_col->get_string(rowIndex)->cstr_, buffer) == 0);
    }

    delete sor;
    delete df;
    fclose(file);
    OK("test_mixed_col");
}

int main() {
    testIntColumn();
    testDoubleColumn();
    testBoolColumn();
    testStringColumn();
    testMixedColumns();
    return 0;
}
