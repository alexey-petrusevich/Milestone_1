#pragma once
#include "../../utils/object.h"
#include "../../kvstore/key.h"

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
    KeyValueBytes(Key *key, byte *value);

    /**
     * Destructor of this KeyValueBytes pair.
     */
    ~KeyValueBytes();

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
    byte *getValue();

    /**
     * Method that checks for equality of two objects
     * 
     * @param Object - object to be checked for equality 
     * @return bool - true or false
     */
    bool equals(Object *o);

    //hash method
    size_t hash();
};
