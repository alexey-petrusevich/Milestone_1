#include "../../include/eau2/collections/arrays/array.h"

Array::Array() : Object() {
    this->array = new Object*[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

Array::Array(int size) : Object() {
    assert(size > 0);
    this->array = new Object*[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void Array::append(Object* input) {
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

Object* Array::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int Array::size() { return this->elementsInserted; }

int Array::index(Object* input) {
    for (int index = 0; index < this->elementsInserted; index++) {
        // if both are null pointers
        if (this->array[index] == nullptr && input == nullptr) {
            return index;
        }  // if neither are null pointers and they are equal
        if (this->array[index] != nullptr && input != nullptr &&
            this->array[index]->equals(input)) {
            return index;
        }
    }
    return -1;
}

Object* Array::set(int index, Object* input) {
    assert(index < this->elementsInserted);
    Object* current = this->array[index];
    this->array[index] = input;
    return current;
}

bool Array::equals(Object* o) {
    Array* otherArray = dynamic_cast<Array*>(o);
    if (otherArray == nullptr) {
        return false;
    }
    // check if sizes are the same
    if (this->size() != otherArray->size()) {
        return false;
    }
    // check every element
    for (int index = 0; index < this->size(); index++) {
        // if any of elements is null but not both (XOR), elements are not
        // the same
        if ((this->array[index] != nullptr) !=
            (otherArray->array[index] != nullptr)) {
            return false;
        }
        // if both are not null pointers and are equal
        if (this->array[index] != nullptr &&
            otherArray->array[index] != nullptr &&
            !(this->array[index]->equals(otherArray->array[index]))) {
            return false;
        }
        // otherwise both are whether null pointers or equal
    }
    return true;
}

size_t Array::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        if (this->array[i] != nullptr) {
            thisHash += this->array[i]->hash();
        }
    }
    return thisHash;
}

void Array::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        Object** newArray = new Object*[newCapacity];
        Object** oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;
        delete[] oldArray;
    }
}

Array::~Array() {
    for (int index = 0; index < this->elementsInserted; index++) {
        delete this->array[index];
    }
    delete[] this->array;
}
