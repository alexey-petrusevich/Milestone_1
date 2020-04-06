#include "../../include/eau2/dataframe/columns/string_column.h"

StringColumn::StringColumn() : Column(ColType::STRING) {
    this->array = new Array();
}

StringColumn::StringColumn(String** array, size_t size)
    : Column(ColType::STRING) {
    this->array = new Array();
    for (size_t i = 0; i < size; i++) {
        this->array->append(array[i]);
        this->numElements++;
    }
}

Object* StringColumn::clone() {
    StringColumn* newCol = new StringColumn();
    for (size_t index = 0; index < this->numElements; index++) {
        newCol->push_back(
            dynamic_cast<String*>(this->array->array[index]->clone()));
    }
    return newCol;
}

void StringColumn::set_string(size_t idx, String* val) {
    assert(idx < this->numElements);
    this->array->set(idx, val);
}

String* StringColumn::get_string(size_t idx) {
    assert(idx < this->numElements);
    return dynamic_cast<String*>(this->array->get(idx));
}

void StringColumn::push_back(String* val) {
    this->array->append(val);
    this->numElements++;
}

void StringColumn::push_nullptr() { this->array->append(nullptr); }

void StringColumn::push_back(char* c) {
    if (c == nullptr) {
        this->push_nullptr();
    }
    this->push_back(new String(c));
}

char* StringColumn::get_char(size_t index) {
    if (index >= this->numElements || this->array->get(index) == nullptr) {
        return nullptr;
    }
    String* str = dynamic_cast<String*>(this->array->get(index));
    size_t str_len = str->size();
    char* ret = new char[str_len + 3];
    ret[0] = '"';
    for (size_t j = 0; j < str_len; j++) {
        ret[j + 1] = str->cstr_[j];
    }
    ret[str_len + 1] = '"';
    ret[str_len + 2] = '\0';
    return ret;
}

void StringColumn::acceptVisitor(IVisitor* visitor) {
    assert(visitor != nullptr);
    visitor->visitStringColumn(this);
}

void StringColumn::accept(Fielder* f) {
    assert(f != nullptr);
    f->accept(this->array->get(f->rowIndex));
}

StringColumn* StringColumn::as_string() { return this; }

StringColumn::~StringColumn() { delete this->array; }

