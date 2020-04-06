#include "../../include/eau2/collections/maps/map.h"

#include <cassert>

Map::Map() { this->createMap(); }

Map::~Map() {
    this->clear();
    delete[] this->map;
}

size_t Map::length() { return this->elementsInserted; }

void Map::clear() {
    for (size_t index = 0; index < tableSize; index++) {
        if (this->map[index] != nullptr) {
            delete this->map[index];
            this->map[index] = nullptr;
        }
    }
    this->elementsInserted = 0;
}

Object* Map::get(Object* key) {
    assert(key != nullptr);
    size_t position = this->findPosition(key);
    KeyValue* kv = this->map[position];
    return kv == nullptr ? kv : kv->getValue();
}

void Map::set(Object* key, Object* value) {
    assert(key != nullptr);
    assert(value != nullptr);
    size_t position = this->findPosition(key);
    if (!this->containsKey(key)) {
        this->map[position] = new KeyValue(key, value);
        this->elementsInserted++;
        // check if rehashing required
        if (this->getLoadFactor() > LOAD_FACTOR) {
            this->rehash();
        }
    } else {
        this->map[position]->value = value;
    }
}

Object* Map::remove(Object* key) {
    assert(key != nullptr);
    if (this->containsKey(key)) {
        size_t position = this->findPosition(key);
        Object* value = this->map[position]->getValue();
        delete this->map[position];
        this->map[position] = nullptr;
        this->elementsInserted--;
        return value;
    }
    return nullptr;
}

Object** Map::getKeys() {
    Object** keys = new Object*[this->elementsInserted];
    for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            keys[keyIndex] = this->map[index]->getKey();
            keyIndex++;
        }
    }
    return keys;
}

Object** Map::getValues() {
    Object** values = new Object*[this->elementsInserted];
    for (size_t index = 0, valueIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            values[valueIndex] = this->map[index]->getValue();
            valueIndex++;
        }
    }
    return values;
}

KeyValue** Map::getItems() {
    KeyValue** items = new KeyValue*[elementsInserted];
    for (size_t index = 0, keyIndex = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            items[keyIndex] = this->map[index];
            keyIndex++;
        }
    }
    return items;
}

bool Map::equals(Object* o) {
    assert(o != nullptr);
    Map* otherMap = dynamic_cast<Map*>(o);
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
            Object* otherValue = otherMap->get(this->map[index]->getKey());
            if (!otherValue) {
                return false;
            }
            result = this->map[index]->getValue()->equals(otherValue);
            if (!result) {
                return false;
            }
        }
    }
    return true;
}

size_t Map::hash() {
    size_t hashValue = 0;
    for (size_t index = 0; index < this->tableSize; index++) {
        if (!this->isEmpty(index)) {
            hashValue += this->map[index]->hash();
        }
    }
    return hashValue;
}

size_t Map::findPosition(Object* key) {
    assert(key != nullptr);
    size_t currentPosition = key->hash() % this->tableSize;
    return currentPosition;
}

double Map::getLoadFactor() {
    return static_cast<double>(this->elementsInserted) / this->tableSize;
}

void Map::rehash() {
    double loadFactor = this->getLoadFactor();
    if (loadFactor > LOAD_FACTOR) {
        // double the size
        this->rehashHelp(this->tableSize * 2);
    }
}

void Map::rehashHelp(size_t newSize) {
    KeyValue** newKV = new KeyValue*[newSize];
    initMap(newKV, newSize);
    KeyValue** oldKV = this->map;
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

bool Map::containsKey(Object* key) {
    assert(key != nullptr);
    size_t position = this->findPosition(key);
    return this->map[position] != nullptr;
}

bool Map::isEmpty(size_t pos) {
    assert(pos < this->tableSize);
    return this->map[pos] == nullptr;
}

void Map::initMap(KeyValue** map, size_t tableSize) {
    assert(map != nullptr);
    for (size_t index = 0; index < tableSize; index++) {
        map[index] = nullptr;
    }
}

void Map::createMap() {
    this->map = new KeyValue*[DEFAULT_MAP_SIZE];
    this->tableSize = DEFAULT_MAP_SIZE;
    this->initMap(this->map, this->tableSize);
    this->elementsInserted = 0;
}
