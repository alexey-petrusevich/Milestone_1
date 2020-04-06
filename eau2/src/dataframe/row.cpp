#include "../../include/eau2/dataframe/row.h"

Row::Row(Schema &scm) {
    this->schema = new Schema(scm);
    this->initColumnArray();
}

void Row::initColumnArray() {
    this->columnArray = new ColumnArray(this->schema->numCols);
    for (size_t colIndex = 0; colIndex < this->schema->numCols; colIndex++) {
        switch (static_cast<ColType>(this->schema->col_type(colIndex))) {
            case ColType::INTEGER:
                this->columnArray->append(new IntColumn());
                this->columnArray->get(colIndex)->push_back(0);
                break;
            case ColType::DOUBLE:
                this->columnArray->append(new DoubleColumn());
                this->columnArray->get(colIndex)->push_back(0);
                break;
            case ColType::BOOLEAN:
                this->columnArray->append(new BoolColumn());
                this->columnArray->get(colIndex)->push_back(false);
                break;
            case ColType::STRING: {
                this->columnArray->append(new StringColumn());
                String *str = nullptr;
                this->columnArray->get(colIndex)->push_back(str);
                break;
            }
            default:
                assert(false);
        }
    }
}

Row::Row(ColumnArray *columnArray, size_t rowIndex) {
    assert(columnArray != nullptr);
    assert(rowIndex < columnArray->get(0)->size());
    this->columnArray = columnArray;
    Schema *schema = columnArray->getSchema();
    this->schema = new Schema(*schema);
    this->rowIndex = rowIndex;
    delete schema;
}

void Row::set(size_t col, int val) {
    assert(col < this->schema->numCols);
    assert(this->columnArray != nullptr);
    IntColumn *intColumn = this->columnArray->get(col)->as_int();
    intColumn->set_int(0, val);
}

void Row::set(size_t col, double val) {
    assert(col < this->schema->numCols);
    assert(this->columnArray != nullptr);
    DoubleColumn *doubleColumn = this->columnArray->get(col)->as_double();
    doubleColumn->set_double(0, val);
}

void Row::set(size_t col, bool val) {
    assert(col < this->schema->numCols);
    assert(this->columnArray != nullptr);
    BoolColumn *boolColumn = this->columnArray->get(col)->as_bool();
    boolColumn->set_bool(0, val);
}

void Row::set(size_t col, String *val) {
    assert(col < this->schema->numCols);
    assert(this->columnArray != nullptr);
    StringColumn *stringColumn = this->columnArray->get(col)->as_string();
    stringColumn->set_string(0, val);
}

void Row::set_idx(size_t idx) {
    assert(idx < this->schema->numRows);
    this->rowIndex = idx;
}

size_t Row::get_idx() { return this->rowIndex; }

int Row::get_int(size_t col) {
    assert(col < this->schema->numCols);
    IntColumn *intColumn = this->columnArray->get(col)->as_int();
    return intColumn->get_int(0);
}

bool Row::get_bool(size_t col) {
    assert(col < this->schema->numCols);
    BoolColumn *boolColumn = this->columnArray->get(col)->as_bool();
    return boolColumn->get_bool(0);
}

double Row::get_double(size_t col) {
    assert(col < this->schema->numCols);
    DoubleColumn *doubleColumn = this->columnArray->get(col)->as_double();
    return doubleColumn->get_double(0);
}

String *Row::get_string(size_t col) {
    assert(col < this->schema->numCols);
    StringColumn *stringColumn = this->columnArray->get(col)->as_string();
    return stringColumn->get_string(0);
}

size_t Row::width() { return this->schema->width(); }

char Row::col_type(size_t idx) {
    // idx is the index of the column
    assert(idx < this->schema->numCols);
    return this->schema->col_type(idx);
}

void Row::visit(size_t idx, Fielder &f) {
    assert(idx == this->rowIndex);
    assert(this->columnArray != nullptr);

    f.start(idx);

    for (size_t colIndex = 0; colIndex < this->schema->numCols; colIndex++) {
        this->columnArray->get(colIndex)->accept(&f);
    }
    // all fields have been seen
    f.done();
}

Row::~Row() { delete this->schema; }
