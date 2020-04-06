#include "../../include/eau2/dataframe/visitors/add_row_visitor.h"

AddRowVisitor::AddRowVisitor(Row* row) : IVisitor() {
    assert(row != nullptr);
    this->row = row;
    this->colIndex = 0;
}

void AddRowVisitor::visitIntColumn(IntColumn* intColumn) {
    assert(intColumn != nullptr);
    intColumn->push_back(row->get_int(colIndex));
    colIndex++;
}

void AddRowVisitor::visitDoubleColumn(DoubleColumn* doubleColumn) {
    assert(doubleColumn != nullptr);
    doubleColumn->push_back(row->get_double(colIndex));
    colIndex++;
}

void AddRowVisitor::visitBoolColumn(BoolColumn* booleanColumn) {
    assert(booleanColumn != nullptr);
    booleanColumn->push_back(row->get_bool(colIndex));
    colIndex++;
}

void AddRowVisitor::visitStringColumn(StringColumn* stringColumn) {
    assert(stringColumn != nullptr);
    stringColumn->push_back(row->get_string(colIndex));
    colIndex++;
}
