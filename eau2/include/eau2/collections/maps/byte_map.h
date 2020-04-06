#pragma once
#include "../../utils/object.h"
#include "keyvalue_bytes.h"

#define LOAD_FACTOR 0.75
#define DEFAULT_MAP_SIZE 100

/**
 * @brief Represents a map that uses Key class as its keys and byte as values.
 * This map is to be used by KV-store with serialized objects to be stored as
 * values. Note: the destructor of this map does not delete stored elements.
 * @file map.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 23, 2020
 */
class ByteMap : public Object {
   public:
    KeyValueBytes** map;  // owned

    size_t tableSize;
    size_t elementsInserted;

    /**
     * Default constructor.
     */
    ByteMap();

    /**
     * Default destructor.
     */
    ~ByteMap();

    /**
     * Returns the number of elements inserted in this map.
     *
     * @return number of elements inserted in this map
     */
    size_t length();

    /**
     * Removes all entries from this map. Does not delete entries.
     */
    void clear();

    /**
     * Returns a value stored at the given key. If value is not found,
     * return nullptr.
     *
     * @param key the key used for searching the value
     * @return the value (serialized object) stored at the given key
     */
    byte* get(Key* key);

    /**
     * Sets the value at the given key. If value is not present,
     * adds the new value to the map.
     *
     * @param key the key used for searching the given vaue
     * @param value the value (serialized object) being inserted into this map
     */
    void set(Key* key, byte* value);

    /**
     * Removes the value from this map given the key associated
     * with the value. If the key is not found, returns null.
     *
     * @param key the key being used for searching
     * @return the value (serialized object) removed from this map
     */
    byte* remove(Key* key);

    /**
     * Returns a collection of all keys in this map.
     *
     * @return the array of keys of this map
     */
    Key** getKeys();

    /**
     * Returns all values (serialized objects) stored in this map as an array.
     *
     * @return the array of all values (serialized object) of this map
     */
    byte** getValues();

    /**
     * Returns all the items stored in this map as an array
     * of KeyValueBytes objects.
     *
     * @return an array of all KeyValueBytes objects stored in this array
     */
    KeyValueBytes** getItems();

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
    size_t findPosition(Key* key);

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
     * A helper function for rehash() that rehashes all the values (serialized
     * objects) in this map given the size of the new map.
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
    bool containsKey(Key* key);

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
    void initMap(KeyValueBytes** map, size_t tableSize);

    /**
     * Creates this map with the default capacity and all empty
     * entries set to nullptr.
     */
    void createMap();
};
