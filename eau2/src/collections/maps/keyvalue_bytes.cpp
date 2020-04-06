#include "../../../include/eau2/collections/maps/keyvalue_bytes.h"

#include <cassert>
#include <cstring>

#include "../../serialization/deserializer.h"

KeyValueBytes::KeyValueBytes(Key *key, byte *value) : Object() {
    this->key = key;
    this->value = value;
}

KeyValueBytes::~KeyValueBytes() {}

Key *KeyValueBytes::getKey() { return this->key; }

byte *KeyValueBytes::getValue() { return this->value; }

bool KeyValueBytes::equals(Object *o) {
    assert(o != nullptr);
    KeyValueBytes *otherKV = dynamic_cast<KeyValueBytes *>(o);
    if (otherKV == nullptr) {
        return false;
    }
    return this->key->equals(otherKV->getKey()) &&
           Deserializer::num_bytes(this->value) ==
               Deserializer::num_bytes(otherKV->value) &&
           memcmp(this->value, otherKV->getValue(),
                  Deserializer::num_bytes(this->value)) == 0;
}

size_t KeyValueBytes::hash() {
    return this->key->hash() + reinterpret_cast<size_t>(this->value);
}
