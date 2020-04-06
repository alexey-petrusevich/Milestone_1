#include "../../include/eau2/collections/maps/keyvalue.h"

#include <cassert>

KeyValue::KeyValue(Object *key, Object *value) : Object() {
    this->key = key;
    this->value = value;
}

KeyValue::~KeyValue() {}

Object *KeyValue::getKey() { return this->key; }

Object *KeyValue::getValue() { return this->value; }

bool KeyValue::equals(Object *o) {
    assert(o != nullptr);
    KeyValue *otherKV = dynamic_cast<KeyValue *>(o);
    if (otherKV == nullptr) {
        return false;
    }
    return this->key->equals(otherKV->getKey()) &&
           this->value->equals(otherKV->getValue());
}

size_t KeyValue::hash() { return this->key->hash() + this->value->hash(); }
