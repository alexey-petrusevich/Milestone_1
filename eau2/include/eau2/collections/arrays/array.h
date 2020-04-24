#pragma once

//#include <cassert>

#include "../../utils/object.h"
//#include "../../utils/string.h"

class String;

#define DEFAULT_ARRAY_SIZE 100

/**
 * @brief This file implements Array and its derivatives as ArrayLists.
 * @file array.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date February 15, 2020
 */
/**
 * Represents an array of Objects. Allows insertion of null pointers as values.
 */
class Array : public Object {
   public:
    Object** array;
    int elementsInserted;
    int capacity;
    int currentPosition;

    /**
     * Default constructor for the array.
     */
    Array();

    /**
     * Array with custom capacity.
     *
     * @param size the capacity of the array
     */
    Array(int size);

    /**
     * Appends the given element to the end of this array.
     *
     * @param input the element being appended to the end of this Array.
     */
    void append(Object* input);

    /**
     * Returns the element at the given index.
     *
     * @param index the index of the element in this Array.
     * @return the element at the given index
     */
    Object* get(int index);

    /**
     * Returns the size of this Array.
     *
     * @return the size of this Array
     */
    int size();

    /**
     * Returns the index of the first element with the given value. Returns
     * -1 if value is not found.
     *
     * @param input the value of the element being searched for
     * @return the index of the element in this Array
     */
    int index(Object* input);

    /**
     * Sets the value of the element at the given index with
     * the given value.
     *
     * @param index the index of the item being set
     * @param input new element being inserted at the given position
     * @return the element displaced by the given element
     */
    Object* set(int index, Object* input);

    bool equals(Object* o);

    /**
     * hash method
     *
     * @return size_t the hash value
     */
    size_t hash();

    /**
     * Checks whether the given capacity is larger than the capacity
     * of this Array. Increases the size if required capacity is larger
     * then the existing capacity.
     *
     * @param required the required capacity
     */
    void _ensure_size(int required);

    /**
     * The destructor of this Array.
     */
    ~Array();
};
