#include "../../../include/eau2/collections/arrays/column_array.h"
#include <cassert>

ColumnArray::ColumnArray() : Object() {
    this->array = new Column*[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

ColumnArray::ColumnArray(int size) : Object() {
    assert(size > 0);
    this->array = new Column*[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void ColumnArray::append(Column* input) {
    assert(input != nullptr);
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

Column* ColumnArray::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int ColumnArray::size() { return this->elementsInserted; }

int ColumnArray::index(Column* input) {
    assert(input != nullptr);
    for (int index = 0; index < this->elementsInserted; index++) {
        if (this->array[index] == input) {
            return index;
        }
    }
    return -1;
}

Column* ColumnArray::set(int index, Column* input) {
    assert(index < this->elementsInserted);
    assert(input != nullptr);
    Column* temp = this->array[index];
    this->array[index] = input;
    return temp;
}

bool ColumnArray::equals(Object* o) {
    assert(o != nullptr);
    ColumnArray* otherArray = dynamic_cast<ColumnArray*>(o);
    if (otherArray == nullptr) {
        return false;
    }
    // check if sizes are the same
    if (this->size() != otherArray->size()) {
        return false;
    }
    // check every element
    for (int index = 0; index < this->size(); index++) {
        if (!(this->array[index]->equals(otherArray->array[index]))) {
            return false;
        }
    }
    return true;
}

size_t ColumnArray::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        thisHash += this->array[i]->hash();
    }
    return thisHash;
}

void ColumnArray::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        Column** newArray = new Column*[newCapacity];
        Column** oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;
        delete[] oldArray;
    }
}

Schema* ColumnArray::getSchema() {
    Schema* schema = new Schema();
    for (int colIndex = 0; colIndex < this->elementsInserted; colIndex++) {
        schema->add_col_type(this->array[colIndex]->colType);
    }
    return schema;
}

ColumnArray::~ColumnArray() {
    for (int i = 0; i < this->elementsInserted; i++) {
        delete this->array[i];
    }
    delete[] this->array;
}