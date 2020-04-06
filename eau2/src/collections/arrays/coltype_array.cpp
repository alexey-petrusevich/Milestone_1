#include "../../../include/eau2/collections/arrays/coltype_array.h"

ColTypeArray::ColTypeArray() : Object() {
    this->array = new ColType[DEFAULT_ARRAY_SIZE];
    this->capacity = DEFAULT_ARRAY_SIZE;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

ColTypeArray::ColTypeArray(int size) : Object() {
    assert(size > 0);
    this->array = new ColType[size];
    this->capacity = size;
    this->elementsInserted = 0;
    this->currentPosition = 0;
}

void ColTypeArray::append(ColType input) {
    this->_ensure_size(this->elementsInserted + 1);
    this->array[currentPosition] = input;
    this->currentPosition++;
    this->elementsInserted++;
}

void ColTypeArray::append(char input) {
    this->_ensure_size(this->elementsInserted + 1);
    switch (static_cast<ColType>(input)) {
        case ColType::INTEGER:
            this->append(ColType::INTEGER);
            break;
        case ColType::DOUBLE:
            this->append(ColType::DOUBLE);
            break;
        case ColType::BOOLEAN:
            this->append(ColType::BOOLEAN);
            break;
        case ColType::STRING:
            this->append(ColType::STRING);
            break;
        default:
            // unknown type
            assert(false);
    }
}

ColType ColTypeArray::get(int index) {
    assert(index < this->elementsInserted);
    return this->array[index];
}

int ColTypeArray::size() { return this->elementsInserted; }

int ColTypeArray::index(ColType input) {
    for (int index = 0; index < this->elementsInserted; index++) {
        if (this->array[index] == input) {
            return index;
        }
    }
    return -1;
}

int ColTypeArray::index(char input) {
    switch (static_cast<ColType>(input)) {
        case ColType::INTEGER:
            return this->index(ColType::INTEGER);
        case ColType::DOUBLE:
            return this->index(ColType::DOUBLE);
        case ColType::BOOLEAN:
            return this->index(ColType::BOOLEAN);
        case ColType::STRING:
            return this->index(ColType::STRING);
        default:
            // unknown type
            return -1;
    }
}

ColType ColTypeArray::set(int index, ColType input) {
    assert(index < this->elementsInserted);
    ColType colType = this->get(index);
    this->array[index] = input;
    return colType;
}

bool ColTypeArray::equals(Object* o) {
    assert(o != nullptr);
    ColTypeArray* otherArray = dynamic_cast<ColTypeArray*>(o);
    if (otherArray == nullptr) {
        return false;
    }
    // check if sizes are the same
    if (this->size() != otherArray->size()) {
        return false;
    }
    // check every element
    for (int index = 0; index < this->size(); index++) {
        if (!(this->array[index] == otherArray->array[index])) {
            return false;
        }
    }
    return true;
}

size_t ColTypeArray::hash() {
    size_t thisHash = 0;
    for (int i = 0; i < this->elementsInserted; i++) {
        thisHash += static_cast<size_t>(this->array[i]);
    }
    return thisHash;
}

void ColTypeArray::_ensure_size(int required) {
    assert(required > 0);
    if (required > this->capacity) {
        int newCapacity = required * 2;
        ColType* newArray = new ColType[newCapacity];
        ColType* oldArray = this->array;
        // copy array
        for (int index = 0; index < this->capacity; index++) {
            newArray[index] = oldArray[index];
        }
        this->array = newArray;
        this->capacity = newCapacity;
        delete[] oldArray;
    }
}

ColTypeArray::~ColTypeArray() { delete[] this->array; }
