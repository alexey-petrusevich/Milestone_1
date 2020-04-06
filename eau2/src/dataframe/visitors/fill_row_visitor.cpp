#include "../../include/eau2/dataframe/visitors/fill_row_visitor.h"

FillRowVisitor::FillRowVisitor(Row* row) : IVisitor() {
    assert(row != nullptr);
    this->row = row;
    this->colIndex = 0;
}

void FillRowVisitor::visitIntColumn(IntColumn* intColumn) {
    assert(intColumn != nullptr);
    intColumn->set_int(colIndex, row->get_int(colIndex));
    colIndex++;
}

void FillRowVisitor::visitDoubleColumn(DoubleColumn* doubleColumn) {
    assert(doubleColumn != nullptr);
    doubleColumn->set_double(colIndex, row->get_double(colIndex));
    colIndex++;
}

void FillRowVisitor::visitBoolColumn(BoolColumn* booleanColumn) {
    assert(booleanColumn != nullptr);
    booleanColumn->set_bool(colIndex, row->get_bool(colIndex));
    colIndex++;
}

void FillRowVisitor::visitStringColumn(StringColumn* stringColumn) {
    assert(stringColumn != nullptr);
    stringColumn->set_string(colIndex, row->get_string(colIndex));
    colIndex++;
}
