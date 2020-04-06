#include "../../include/eau2/collections/arrays/double_array.h"

DoubleArray::DoubleArray() : Object() {
    this->array = new double[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

DoubleArray::DoubleArray(int size) : Object() {
    assert(size > 0);
    this->array = new double[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void DoubleArray::append(double input) {
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

double DoubleArray::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int DoubleArray::size() { return this->elementsInserted; }

int DoubleArray::index(double input) {
    for (int index = 0; index < this->elementsInserted; index++) {
        if (std::abs(this->array[index] - input) < 1E-14) {
            return index;
        }
    }
    return -1;
}

double DoubleArray::set(int index, double input) {
    assert(index < this->elementsInserted);
    double current = this->array[index];
    this->array[index] = input;
    return current;
}

bool DoubleArray::equals(Object* o) {
    // dynamic casting
    DoubleArray* otherArray = dynamic_cast<DoubleArray*>(o);
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

size_t DoubleArray::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        thisHash += static_cast<size_t>(this->array[i]);
    }
    return thisHash;
}

void DoubleArray::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        double* newArray = new double[newCapacity];
        double* oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;
        this->capacity *= 2;
        delete[] oldArray;
    }
}

DoubleArray::~DoubleArray() { delete[] this->array; }
