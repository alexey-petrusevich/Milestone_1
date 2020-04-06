#pragma once

#include "../utils/object.h"
#include "keyvalue.h"

#define LOAD_FACTOR 0.75
#define DEFAULT_MAP_SIZE 100

/**
 * @brief This file represents a collection of maps holding different types of
 * KeyValue that could be found in keyvalue.h
 * @file map.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

/**
 * @brief Represents a map with keys and values. Both key and value have to
 * extend from Object class. Note: this map does not delete stored elements upon
 * calling the destructor.
 * @file map.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class Map : public Object {
   public:
    KeyValue** map;  // owned

    size_t tableSize;
    size_t elementsInserted;

    /**
     * Default constructor.
     */
    Map();

    /**
     * Default destructor.
     */
    ~Map();

    /**
     * Returns the number of elements inserted in this map.
     *
     * @return number of elements inserted in this map
     */
    size_t length();

    /**
     * Removes all entries from this map.
     */
    void clear();

    /**
     * Returns a value stored at the given key. If value is not found,
     * return null.
     *
     * @param key the key used for searching the value
     * @return the value stored at the given key
     */
    Object* get(Object* key);

    /**
     * Sets the value at the given key. If value is not present,
     * adds the new value to the map.
     *
     * @param key the key used for searching the given vaue
     * @param value the value being inserted into this map
     */
    void set(Object* key, Object* value);

    /**
     * Removes the value from this map given the key associated
     * with the value. If the key is not found, returns null.
     *
     * @param key the key being used for searching
     * @return the value removed from this map
     */
    Object* remove(Object* key);

    /**
     * Returns a collection of all keys in this map.
     *
     * @return the array of keys of this map
     */
    Object** getKeys();

    /**
     * Returns all values stored in this map as an array.
     *
     * @return the array of all values of this map
     */
    Object** getValues();

    /**
     * Returns all the items stored in this map as an array
     * of KeyValue objects.
     *
     * @return an array of all KeyValue objects stored in this array
     */
    KeyValue** getItems();

    /**
     * Method that checks two objects for equality
     *
     * @param Object - object to be checked for equality
     * @return bool - true or false
     */
    bool equals(Object* o);

    // hash method
    size_t hash();

    /**
     * Returns a position of the given key in this map.
     *
     * @param the key being used for calculating the position in this map
     * @return the position in this map
     */
    size_t findPosition(Object* key);

    /**
     * Returns a load factor of this map.
     *
     * @return the load factor of this map
     */
    double getLoadFactor();

    /**
     * Rehashes this map if the load factor gets over threshold.
     */
    void rehash();

    /**
     * A helper function for rehash() that rehashes all the values in
     * this map given the size of the new map.
     *
     * @param newSize the size of the new map
     */
    void rehashHelp(size_t newSize);

    /**
     * Returns if the given key is present in this map.
     *
     * @param key the key being checked
     * @return bool true if the key is in this map and false otherwise
     */
    bool containsKey(Object* key);

    /**
     * Returns true if the element at the given position is empty
     * and false otherwise.
     *
     * @param the position in this map
     * @return true if the position doesn't have an entry and false otherwise
     */
    bool isEmpty(size_t pos);

    /**
     * Sets all the values of the given map to nullptr.
     *
     * @param map the given map
     * @param tableSize the size of the given map
     */
    void initMap(KeyValue** map, size_t tableSize);

    /**
     * Creates this map with the default capacity and all empty
     * entries set to nullptr. Utility method - shall not be used explicitly by
     * the user.
     */
    void createMap();
};
