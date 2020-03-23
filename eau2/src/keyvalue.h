// A1: Part 2
// lang: CwC

#pragma once
#include <assert.h>

#include "object.h"

/**
 * Represents a key value pair for a map.
 */
class KeyValue : public Object {
   public:
    Object *key;
    Object *value;

    KeyValue(Object *k, Object *v) : Object() {
        // Constructor for KeyValue pair
        this->key = k;
        this->value = v;
    }

    ~KeyValue() {
        // Destructor for KeyValue pair
    }

    // Gets the key of the pair
    Object *getKey() { return this->key; }

    // Gets the value of the pair
    Object *getValue() { return this->value; }

    bool equals(Object *o) {
        assert(o != nullptr);
        KeyValue *otherKV = dynamic_cast<KeyValue *>(o);
        if (otherKV == nullptr) {
            return false;
        }
        return this->key->equals(otherKV->getKey()) &&
               this->value->equals(otherKV->getValue());
    }

    size_t hash() { return this->key->hash() + this->value->hash(); }
};

// represents a map that stores
class KeyValueBytes : public Object {
   public:
    Key *key;
    byte *value;

    KeyValueBytes(Key *key, byte *value) : Object() {
        this->key = key;
        this->value = value;
    }

    ~KeyValueBytes() {}

    Key *getKey() { return this->key; }

    byte *getValue() { return this->value; }

    bool equals(Object *o) {
        assert(o != nullptr);
        KeyValueBytes *otherKV = dynamic_cast<KeyValueBytes *>(o);
        if (otherKV == nullptr) {
            return false;
        }
        return this->key->equals(otherKV->getKey()) &&
               memcmp(this->value, otherKV->getValue(), sizeof(value));
    }

    size_t hash() { return this->key->hash() + reinterpret_cast<size_t>(this->value); }
};