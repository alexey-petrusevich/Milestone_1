#include "../../../include/eau2/collections/maps/byte_map.h"

#include <cassert>
#include <cstring>

#include "../../serialization/deserializer.h"

ByteMap::ByteMap() { this->createMap(); }

ByteMap::~ByteMap() {
    this->clear();
    delete[] this->map;
}

size_t ByteMap::length() { return this->elementsInserted; }

void ByteMap::clear() {
    for (size_t index = 0; index < tableSize; index++) {
        if (this->map[index] != nullptr) {
            delete this->map[index];
            this->map[index] = nullptr;
        }
    }
    this->elementsInserted = 0;
}

byte* ByteMap::get(Key* key) {
    assert(key != nullptr);
    size_t position = this->findPosition(key);
    KeyValueBytes* kv = this->map[position];
    return kv == nullptr ? nullptr : kv->getValue();
}

void ByteMap::set(Key* key, byte* value) {
    assert(key != nullptr);
    assert(value != nullptr);
    size_t position = this->findPosition(key);
    if (!this->containsKey(key)) {
        this->map[position] = new KeyValueBytes(key, value);
        this->elementsInserted++;
        // check if rehashing required
        if (this->getLoadFactor() > LOAD_FACTOR) {
            this->rehash();
        }
    } else {
        this->map[position]->value = value;
    }
}

byte* ByteMap::remove(Key* key) {
    assert(key != nullptr);
    if (this->containsKey(key)) {
        size_t position = this->findPosition(key);
        byte* value = this->map[position]->getValue();
        delete this->map[position];
        this->map[position] = nullptr;
        this->elementsInserted--;
        return value;
    }
    return nullptr;
}

Key** ByteMap::getKeys() {
    Key** keys = new Key*[this->elementsInserted];
    for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            keys[keyIndex] = this->map[index]->getKey();
            keyIndex++;
        }
    }
    return keys;
}

byte** ByteMap::getValues() {
    byte** values = new byte*[this->elementsInserted];
    for (size_t index = 0, valueIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            values[valueIndex] = this->map[index]->getValue();
            valueIndex++;
        }
    }
    return values;
}

KeyValueBytes** ByteMap::getItems() {
    KeyValueBytes** items = new KeyValueBytes*[elementsInserted];
    for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            items[keyIndex] = this->map[index];
            keyIndex++;
        }
    }
    return items;
}

bool ByteMap::equals(Object* o) {
    assert(o != nullptr);
    ByteMap* otherMap = dynamic_cast<ByteMap*>(o);
    if (otherMap == nullptr) {
        return false;
    }
    // if number of elements is different, maps are not equal
    bool result = this->length() == otherMap->length();
    if (!result) {
        return false;
    }
    // compare each non-empty element in the map
    for (size_t index = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            byte* otherValue = otherMap->get(this->map[index]->getKey());
            if (!otherValue) {
                return false;
            }
            byte* value = this->map[index]->getValue();
            size_t numBytes = Deserializer::num_bytes(value);
            result &= (numBytes == Deserializer::num_bytes(otherValue));
            result = memcmp(value, otherValue, numBytes) == 0;
            if (!result) {
                return false;
            }
        }
    }
    return true;
}

size_t ByteMap::hash() {
    size_t hashValue = 0;
    for (size_t index = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            hashValue += this->map[index]->hash();
        }
    }
    return hashValue;
}

size_t ByteMap::findPosition(Key* key) {
    assert(key != nullptr);
    size_t currentPosition = key->hash() % this->tableSize;
    return currentPosition;
}

double ByteMap::getLoadFactor() {
    return static_cast<double>(this->elementsInserted) / this->tableSize;
}

void ByteMap::rehash() {
    double loadFactor = this->getLoadFactor();
    if (loadFactor > LOAD_FACTOR) {
        // double the size
        this->rehashHelp(this->tableSize * 2);
    }
}

void ByteMap::rehashHelp(size_t newSize) {
    KeyValueBytes** newKV = new KeyValueBytes*[newSize];
    initMap(newKV, newSize);
    KeyValueBytes** oldKV = this->map;
    size_t oldSize = this->tableSize;
    this->map = newKV;
    this->tableSize = newSize;
    // rehash indices of the elements
    for (size_t index = 0; index < oldSize; index++) {
        if (oldKV[index] != nullptr) {
            size_t newPosition = this->findPosition(oldKV[index]->getKey());
            this->map[newPosition] = oldKV[index];
        }
    }
    delete[] oldKV;
}

bool ByteMap::containsKey(Key* key) {
    assert(key != nullptr);
    size_t position = this->findPosition(key);
    return this->map[position] != nullptr;
}

bool ByteMap::isEmpty(size_t pos) {
    assert(pos < this->tableSize);
    return this->map[pos] == nullptr;
}

void ByteMap::initMap(KeyValueBytes** map, size_t tableSize) {
    assert(map != nullptr);
    for (size_t index = 0; index < tableSize; index++) {
        map[index] = nullptr;
    }
}

void ByteMap::createMap() {
    this->map = new KeyValueBytes*[DEFAULT_MAP_SIZE];
    this->tableSize = DEFAULT_MAP_SIZE;
    this->initMap(this->map, this->tableSize);
    this->elementsInserted = 0;
}
