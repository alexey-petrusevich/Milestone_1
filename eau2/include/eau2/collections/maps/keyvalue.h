#pragma once

#include "../../utils/object.h"

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
    KeyValue(Object *key, Object *value);

    /**
     * Destructor for KeyValue pair.
     */
    ~KeyValue();

    /**
     * Returns the key of this KeyValue pair.
     *
     * @return the key of this KeyValue pair
     */
    Object *getKey();

    /**
     * Returns the value of this KeyValue pair.
     *
     * @return the value of this KeyValue pair
     */
    Object *getValue();

    /**
     * Checks equality of two objects 
     * 
     * @param Object - object to be checked for equality
     * @return bool - true or false
     */ 
    bool equals(Object *o);

    //hash method
    size_t hash();
};

