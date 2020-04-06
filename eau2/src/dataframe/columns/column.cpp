#include "../../../include/eau2/dataframe/columns/column.h"

Column::Column(ColType colType) : Object() {
    this->colType = colType;
    this->numElements = 0;
}


void Column::push_back(int val) { assert(false); }

void Column::push_back(double val) { assert(false); }

void Column::push_back(bool val) { assert(false); }

void Column::push_back(String* val) { assert(false); }

void Column::push_back(char* val) { assert(false); }

void Column::push_nullptr() { assert(false); }

size_t Column::size() { return this->numElements; }

void Column::set_int(size_t index, int value) { assert(false); }

void Column::set_double(size_t index, double value) { assert(false); }

void Column::set_bool(size_t index, bool value) { assert(false); }

void Column::set_string(size_t index, String* value) { assert(false); }

int Column::get_int(size_t index) { assert(false); }

double Column::get_double(size_t index) { assert(false); }

bool Column::get_bool(size_t index) { assert(false); }

String* Column::get_string(size_t index) { assert(false); }

bool Column::can_add(char* c) {
    if (c == nullptr || *c == '\0') {
        return true;
    }
    return infer_type(c) <= get_type();
}

char Column::get_type_char() { return static_cast<char>(this->colType); }

ColType Column::get_type() { return this->colType; }

char* Column::get_char(size_t i) { return nullptr; }

Column::~Column() {}
