#include "../../include/eau2/dataframe/columns/double_column.h"

DoubleColumn::DoubleColumn() : Column(ColType::DOUBLE) {
    this->array = new DoubleArray();
}

DoubleColumn::DoubleColumn(double* array, size_t size)
    : Column(ColType::DOUBLE) {
    this->array = new DoubleArray();
    for (size_t i = 0; i < size; i++) {
        this->array->append(array[i]);
        this->numElements++;
    }
}

Object* DoubleColumn::clone() {
    return new DoubleColumn(this->array->array, this->numElements);
}

void DoubleColumn::set_double(size_t idx, double val) {
    assert(idx < this->numElements);
    this->array->set(idx, val);
}

double DoubleColumn::get_double(size_t idx) {
    assert(idx < this->numElements);
    return this->array->get(idx);
}

void DoubleColumn::push_back(double val) {
    this->array->append(val);
    this->numElements++;
}

void DoubleColumn::push_nullptr() { this->array->append(null_double); }

void DoubleColumn::push_back(char* c) {
    if (c == nullptr) {
        this->push_nullptr();
    }
    this->push_back(atof(c));
}

char* DoubleColumn::get_char(size_t index) {
    if (index >= this->numElements) {
        return const_cast<char*>("0");
    }
    char* ret = new char[512];
    sprintf(ret, "%f", this->array->get(index));
    return ret;
}

void DoubleColumn::acceptVisitor(IVisitor* visitor) {
    assert(visitor != nullptr);
    visitor->visitDoubleColumn(this);
}

void DoubleColumn::accept(Fielder* f) {
    assert(f != nullptr);
    f->accept(this->array->get(f->rowIndex));
}

DoubleColumn* DoubleColumn::as_double() { return this; }

DoubleColumn::~DoubleColumn() { delete this->array; }
