// A1: Part 2
// lang: CwC

#pragma once
#include <assert.h>

#include "object.h"

/**
 * @brief Represents a key-value pair for a Map. Both Key and Value have to
 * extend from the Object class.
 * @file keyvalue.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class KeyValue : public Object {
   public:
    Object *key;
    Object *value;

    /**
     * Constructor for KeyValue pair.
     * 
     * @param key the key component for this KeyValue pair
     * @param value the value component for this KeyValue pair
     */
    KeyValue(Object *key, Object *value) : Object() {
        
        this->key = key;
        this->value = value;
    }

    /**
     * Destructor for KeyValue pair.
     */
    ~KeyValue() {}

    /**
     * Returns the key of this KeyValue pair.
     * 
     * @return the key of this KeyValue pair
     */
    Object *getKey() { return this->key; }

    /**
     * Returns the value of this KeyValue pair.
     * 
     * @return the value of this KeyValue pair
     */
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

/**
 * @brief Represents a key-value pair for a ByteMap. The key should be of Key class
 * whereas value is represented as a serialized object of byte (unsigned char) type.
 * @file keyvalue.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class KeyValueBytes : public Object {
   public:
    Key *key;
    byte *value;

    /**
     * Constructor for KeyValueBytes pair.
     * 
     * @param key the key component for this KeyValue pair
     * @param value the value component for this KeyValue pair
     */
    KeyValueBytes(Key *key, byte *value) : Object() {
        this->key = key;
        this->value = value;
    }

    /**
     * Destructor of this KeyValueBytes pair.
     */
    ~KeyValueBytes() {}


    /**
     * Returns the key component of this KeyValueBytes pair.
     * 
     * @return the key component of this KeyValueBytes pair
     */
    Key *getKey() { return this->key; }

    /**
     * Returs the value (serialized object) component of this KeyValueBytes pair.
     * 
     * @return the value (serialized object) component of this KeyValueBytes pair
     */
    byte *getValue() { return this->value; }

    bool equals(Object *o) {
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

    size_t hash() {
        return this->key->hash() + reinterpret_cast<size_t>(this->value);
    }
};
