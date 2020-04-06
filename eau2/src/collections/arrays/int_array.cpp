#include "../../include/eau2/collections/arrays/int_array.h"

IntArray::IntArray() : Object() {
    this->array = new int[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

IntArray::IntArray(int size) : Object() {
    assert(size > 0);
    this->array = new int[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void IntArray::append(int& input) {
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

int IntArray::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int IntArray::size() { return this->elementsInserted; }

int IntArray::index(int& input) {
    for (int index = 0; index < this->elementsInserted; index++) {
        if (this->array[index] == input) {
            return index;
        }
    }
    return -1;
}

int IntArray::set(int index, int& input) {
    assert(index < this->elementsInserted);
    int current = this->array[index];
    this->array[index] = input;
    return current;
}

bool IntArray::equals(Object* o) {
    IntArray* otherArray = dynamic_cast<IntArray*>(o);
    if (otherArray == nullptr) {
        return false;
    }
    if (this->size() != otherArray->size()) {
        return false;
    }
    for (int index = 0; index < this->size(); index++) {
        if (this->array[index] != otherArray->array[index]) {
            return false;
        }
    }
    return true;
}

size_t IntArray::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        thisHash += this->array[i];
    }
    return thisHash;
}

void IntArray::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        int* newArray = new int[newCapacity];
        int* oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;

        delete[] oldArray;
    }
}

IntArray::~IntArray() { delete[] this->array; }
