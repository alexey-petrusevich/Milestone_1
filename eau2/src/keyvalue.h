#pragma once
#include <cassert>

#include "deserializer.h"
#include "object.h"

/**
 * @brief Represents a file that stores various KeyValue classes.
 * KeyValue is represented by a pair of Object-Object for key and value
 * respectively, whereas KeyValueBytes is represented by Key and byte as its key
 * and value.
 * @file keyvalue.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * @brief Represents Key class to be used in KV-store.
 * @file kvstore.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Key : public Object {
   public:
    const char *key;
    size_t nodeId;

    /**
     * Constructor of this Key object.
     *
     * @param key the key represented as const char (cstring) type
     * @param nodeId the id of the node this key is associated with
     */
    Key(const char *key, size_t nodeId) : Object() {
        this->key = key;
        this->nodeId = nodeId;
    }

    /**
     * Desturctor of this Key object.
     */
    ~Key() {}
};

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

    /**
     * Checks equality of two objects 
     * 
     * @param Object - object to be checked for equality
     * @return bool - true or false
     */ 
    bool equals(Object *o) {
        assert(o != nullptr);
        KeyValue *otherKV = dynamic_cast<KeyValue *>(o);
        if (otherKV == nullptr) {
            return false;
        }
        return this->key->equals(otherKV->getKey()) &&
               this->value->equals(otherKV->getValue());
    }

    //hash method
    size_t hash() { return this->key->hash() + this->value->hash(); }
};

/**
 * @brief Represents a key-value pair for a ByteMap. The key should be of Key
 * class whereas value is represented as a serialized object of byte (unsigned
 * char) type.
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
     * Returs the value (serialized object) component of this KeyValueBytes
     * pair.
     *
     * @return the value (serialized object) component of this KeyValueBytes
     * pair
     */
    byte *getValue() { return this->value; }

    /**
     * Method that checks for equality of two objects
     * 
     * @param Object - object to be checked for equality 
     * @return bool - true or false
     */
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

    //hash method
    size_t hash() {
        return this->key->hash() + reinterpret_cast<size_t>(this->value);
    }
};
