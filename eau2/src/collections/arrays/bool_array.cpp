#include "../../include/eau2/collections/arrays/bool_array.h"

BoolArray::BoolArray() : Object() {
    this->array = new bool[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

BoolArray::BoolArray(int size) : Object() {
    assert(size > 0);
    this->array = new bool[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void BoolArray::append(bool input) {
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

bool BoolArray::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int BoolArray::size() { return this->elementsInserted; }

int BoolArray::index(bool input) {
    for (int index = 0; index < this->elementsInserted; index++) {
        if (this->array[index] == input && index < this->currentPosition) {
            return index;
        }
    }
    return -1;
}

bool BoolArray::set(int index, bool input) {
    assert(index < this->elementsInserted);
    bool current = this->array[index];
    this->array[index] = input;
    return current;
}

bool BoolArray::equals(Object* o) {
    BoolArray* otherArray = dynamic_cast<BoolArray*>(o);
    if (otherArray == nullptr) {
        return false;
    }
    // check if sizes are the same
    if (this->size() != otherArray->size()) {
        return false;
    }
    // check every element
    for (int index = 0; index < this->size(); index++) {
        if (this->array[index] != otherArray->array[index]) {
            return false;
        }
    }
    return true;
}

size_t BoolArray::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        thisHash += this->array[i] ? 1 : 0;
    }
    return thisHash;
}

void BoolArray::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        bool* newArray = new bool[newCapacity];
        bool* oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;
        delete[] oldArray;
    }
}

BoolArray::~BoolArray() { delete[] this->array; }
