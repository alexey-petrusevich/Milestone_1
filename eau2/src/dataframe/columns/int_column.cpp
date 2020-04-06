#include "../../../include/eau2/dataframe/columns/int_column.h"

#include <iostream>

IntColumn::IntColumn() : Column(ColType::INTEGER) {
    this->array = new IntArray();
}

IntColumn::IntColumn(int* array, size_t size) : Column(ColType::INTEGER) {
    this->array = new IntArray();
    for (size_t i = 0; i < size; i++) {
        this->array->append(array[i]);
        this->numElements++;
    }
}

Object* IntColumn::clone() {
    return new IntColumn(this->array->array, this->numElements);
}

void IntColumn::set_int(size_t index, int val) {
    assert(index < this->numElements);
    this->array->set(index, val);
}

int IntColumn::get_int(size_t idx) {
    assert(idx < this->numElements);
    return this->array->get(idx);
}

void IntColumn::push_back(int val) {
    this->array->append(val);
    this->numElements++;
}

void IntColumn::push_nullptr() { this->array->append(null_int); }

void IntColumn::push_back(char* c) {
    if (c == nullptr) {
        this->push_nullptr();
    }
    this->push_back(atoi(c));
}

char* IntColumn::get_char(size_t index) {
    if (index >= this->numElements) {
        return const_cast<char*>("0");
    }
    char* ret = new char[512];
    sprintf(ret, "%d", this->array->get(index));
    return ret;
}

void IntColumn::acceptVisitor(IVisitor* visitor) {
    assert(visitor != nullptr);
    visitor->visitIntColumn(this);
}

void IntColumn::accept(Fielder* f) {
    assert(f != nullptr);
    f->accept(this->array->get(f->rowIndex));
}


IntColumn::~IntColumn() { delete this->array; }
