#include "../../include/eau2/dataframe/columns/bool_column.h"

#include <iostream>

BoolColumn::BoolColumn() : Column(ColType::BOOLEAN) {
    this->array = new BoolArray();
}

BoolColumn::BoolColumn(bool* array, size_t size) : Column(ColType::BOOLEAN) {
    this->array = new BoolArray();
    for (size_t i = 0; i < size; i++) {
        this->array->append(array[i]);
        this->numElements++;
    }
}

Object* BoolColumn::clone() {
    return new BoolColumn(this->array->array, this->numElements);
}

void BoolColumn::set_bool(size_t idx, bool val) {
    assert(idx < this->numElements);
    this->array->set(idx, val);
}

bool BoolColumn::get_bool(size_t idx) {
    assert(idx < this->numElements);
    return this->array->get(idx);
}

void BoolColumn::push_back(bool val) {
    this->array->append(val);
    this->numElements++;
}

void BoolColumn::push_nullptr() { this->array->append(null_bool); }

void BoolColumn::push_back(char* c) {
    if (c == nullptr) {
        this->push_nullptr();
    }
    bool b;
    if (*c == '0') {
        b = false;
    } else {
        b = true;
    }
    this->push_back(b);
}

char* BoolColumn::get_char(size_t index) {
    if (index >= this->numElements) {
        return const_cast<char*>("0");
    }
    char* ret = new char[512];
    sprintf(ret, "%d", this->array->get(index));
    return ret;
}

void BoolColumn::acceptVisitor(IVisitor* visitor) {
    assert(visitor != nullptr);
    visitor->visitBoolColumn(this);
}

void BoolColumn::accept(Fielder* f) {
    assert(f != nullptr);
    f->accept(this->array->get(f->rowIndex));
}

BoolColumn* BoolColumn::as_bool() { return this; }

BoolColumn::~BoolColumn() { delete this->array; }